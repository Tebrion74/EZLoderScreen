// EZ holographic name tags - shared state + PlayerBase hooks (server decides, clients draw).
// Tag types: 0 none, 1 player in sanctuary (green), 2 admin in admin-mode (pink, map-wide), 3 InvincibleGuards defender (blue), 4 bandit eAI (red)
const int EZ_RPC_HOLO_CFG    = 82341001; // server -> client  Param1<string> (json, admin IDs stripped)
const int EZ_RPC_HOLO_ADMINS = 82341002; // server -> client  Param2<array<string>, array<vector>>
const int EZ_RPC_HOLO_TOGGLE = 82341003; // client -> server  Param1<bool>

class EZHolo
{
	static ref EZHoloConfig s_ServerCfg;
	static ref EZHoloConfig s_ClientCfg;
	static ref TStringArray s_AdminOn;
	static ref array<PlayerBase> s_Tracked;
	static ref TStringArray s_AdminNames;
	static ref array<vector> s_AdminPos;

	static EZHoloConfig ServerCfg()
	{
		if (!s_ServerCfg)
			s_ServerCfg = EZHoloConfig.LoadOrCreate();
		return s_ServerCfg;
	}

	static TStringArray AdminOn()
	{
		if (!s_AdminOn)
			s_AdminOn = new TStringArray;
		return s_AdminOn;
	}

	static array<PlayerBase> Tracked()
	{
		if (!s_Tracked)
			s_Tracked = new array<PlayerBase>;
		// drop entries whose player object was deleted (disconnect/despawn)
		for (int i = s_Tracked.Count() - 1; i >= 0; i--)
		{
			if (!s_Tracked[i])
				s_Tracked.Remove(i);
		}
		return s_Tracked;
	}

	// Built-in owners: always admins, even if HoloTags.json has an empty AdminSteamIDs list.
	static const string EZ_OWNER_ID = "76561198854071221"; // Robert

	static bool IsAdmin(string steamId)
	{
		if (steamId == "")
			return false;
		if (steamId == EZ_OWNER_ID)
			return true;
		return ServerCfg().AdminSteamIDs.Find(steamId) != -1;
	}

	static bool IsAdminOn(string steamId)
	{
		return IsAdmin(steamId) && AdminOn().Find(steamId) != -1;
	}

	static void Track(PlayerBase p, bool on)
	{
		int i = Tracked().Find(p);
		if (on && i == -1)
			Tracked().Insert(p);
		else if (!on && i != -1)
			Tracked().Remove(i);
	}

	static string ClientJson()
	{
		EZHoloConfig cfg = ServerCfg();
		ref array<string> keep = cfg.AdminSteamIDs;
		cfg.AdminSteamIDs = new array<string>; // never send admin IDs to clients
		string json;
		JsonSerializer js = new JsonSerializer();
		js.WriteToString(cfg, false, json);
		cfg.AdminSteamIDs = keep;
		return json;
	}

	static void SendConfig(PlayerBase player)
	{
		if (!player || !player.GetIdentity())
			return;
		player.RPCSingleParam(EZ_RPC_HOLO_CFG, new Param1<string>(ClientJson()), true, player.GetIdentity());
	}
}

modded class PlayerBase
{
	int m_EZHoloType;

	void PlayerBase()
	{
		RegisterNetSyncVariableInt("m_EZHoloType", 0, 4);
		if (GetGame() && GetGame().IsServer())
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(EZ_HoloServerTick, 2000 + Math.RandomInt(0, 1000), true);
	}

	void ~PlayerBase()
	{
		if (GetGame())
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(EZ_HoloServerTick);
		EZHolo.Track(this, false);
	}

	int EZ_GetHoloType()
	{
		return m_EZHoloType;
	}

	// 3 = InvincibleGuards defender, 4 = bandit (any other eAI faction), 0 = unknown
	int EZ_AIHoloType()
	{
	#ifdef EXPANSIONMODAI
		if (!IsInherited(eAIBase))
			return 0; // not an AI (e.g. disconnected player body)
		eAIGroup g = GetGroup();
		if (!g || !g.GetFaction())
			return 3; // ungrouped / factionless AI -> treat as sanctuary defender
		eAIFaction f = g.GetFaction();
		// eAIFactionGuards also covers eAIFactionInvincibleGuards (subclass)
		if (f.IsInherited(eAIFactionGuards) || f.IsInherited(eAIFactionPassive))
			return 3;
		return 4;
	#else
		return 0;
	#endif
	}

	void EZ_HoloServerTick()
	{
		int t = 0;
		EZHoloConfig cfg = EZHolo.ServerCfg();
		if (cfg.Enabled && IsAlive())
		{
			bool inZone = cfg.InZone(GetPosition());
			PlayerIdentity id = GetIdentity();
			if (id)
			{
				if (EZHolo.IsAdminOn(id.GetPlainId()))
					t = 2;
				else if (inZone)
					t = 1;
			}
			else
			{
				int ai = EZ_AIHoloType();
				if (ai == 3 && inZone)
					t = 3;
				else if (ai == 4 && (inZone || cfg.BanditTagsEverywhere))
					t = 4;
			}
		}
		if (t != m_EZHoloType)
		{
			string who = GetType();
			if (GetIdentity())
				who = GetIdentity().GetName();
			Print("[EZHolo] " + who + " holo type " + m_EZHoloType.ToString() + " -> " + t.ToString() + " @ " + GetPosition().ToString());
			m_EZHoloType = t;
			SetSynchDirty();
		}
	}

	override void OnVariablesSynchronized()
	{
		super.OnVariablesSynchronized();
		if (!GetGame().IsDedicatedServer())
			EZHolo.Track(this, m_EZHoloType != 0);
	}

	override void EEKilled(Object killer)
	{
		super.EEKilled(killer);
		if (GetGame().IsServer())
			EZ_HoloServerTick();
	}

	override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
	{
		super.OnRPC(sender, rpc_type, ctx);
		switch (rpc_type)
		{
			case EZ_RPC_HOLO_CFG:
			{
				if (GetGame().IsDedicatedServer())
					return;
				Param1<string> pc = new Param1<string>("");
				if (!ctx.Read(pc))
					return;
				EZHoloConfig c = new EZHoloConfig();
				string err;
				JsonSerializer js = new JsonSerializer();
				if (js.ReadFromString(c, pc.param1, err))
					EZHolo.s_ClientCfg = c;
				break;
			}
			case EZ_RPC_HOLO_ADMINS:
			{
				if (GetGame().IsDedicatedServer())
					return;
				Param2<ref TStringArray, ref array<vector>> pa = new Param2<ref TStringArray, ref array<vector>>(new TStringArray, new array<vector>);
				if (!ctx.Read(pa))
					return;
				EZHolo.s_AdminNames = pa.param1;
				EZHolo.s_AdminPos = pa.param2;
				break;
			}
			case EZ_RPC_HOLO_TOGGLE:
			{
				if (!GetGame().IsServer() || !sender || !GetIdentity() || sender.GetPlainId() != GetIdentity().GetPlainId())
					return;
				string sid = sender.GetPlainId();
				if (!EZHolo.IsAdmin(sid))
				{
					NotificationSystem.SendNotificationToPlayerExtended(this, 4, "EchelonZ", "Admin holo-tag is for server admins only.", "set:dayz_gui image:icon_info");
					return;
				}
				int idx = EZHolo.AdminOn().Find(sid);
				string msg;
				if (idx == -1)
				{
					EZHolo.AdminOn().Insert(sid);
					msg = "Admin holo-tag ON (visible map-wide).";
				}
				else
				{
					EZHolo.AdminOn().Remove(idx);
					msg = "Admin holo-tag OFF (you are a normal player).";
				}
				NotificationSystem.SendNotificationToPlayerExtended(this, 5, "EchelonZ Admin", msg, "set:dayz_gui image:icon_info");
				EZ_HoloServerTick();
				break;
			}
		}
	}
}

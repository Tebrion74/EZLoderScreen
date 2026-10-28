// Server side of holo tags: config push on connect + map-wide admin broadcast every 2 s.
modded class MissionServer
{
	float m_EZHoloTimer;

	override void OnInit()
	{
		super.OnInit();
		EZHolo.ServerCfg(); // creates $profile:EZLoderScreen/HoloTags.json on first start
	}

	override void InvokeOnConnect(PlayerBase player, PlayerIdentity identity)
	{
		super.InvokeOnConnect(player, identity);
		EZHolo.SendConfig(player);
	}

	override void OnUpdate(float timeslice)
	{
		super.OnUpdate(timeslice);
		m_EZHoloTimer += timeslice;
		if (m_EZHoloTimer < 2.0)
			return;
		m_EZHoloTimer = 0;
		if (!EZHolo.ServerCfg().Enabled)
			return;

		array<Man> players = new array<Man>;
		GetGame().GetPlayers(players);
		TStringArray names = new TStringArray;
		array<vector> pos = new array<vector>;
		foreach (Man m : players)
		{
			PlayerBase p = PlayerBase.Cast(m);
			if (p && p.IsAlive() && p.EZ_GetHoloType() == 2 && p.GetIdentity())
			{
				names.Insert(p.GetIdentity().GetName());
				pos.Insert(p.GetPosition() + "0 2 0");
			}
		}
		Param2<ref TStringArray, ref array<vector>> data = new Param2<ref TStringArray, ref array<vector>>(names, pos);
		foreach (Man r : players)
		{
			if (r && r.GetIdentity())
				r.RPCSingleParam(EZ_RPC_HOLO_ADMINS, data, true, r.GetIdentity());
		}
	}
}

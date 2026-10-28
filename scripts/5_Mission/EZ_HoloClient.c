// Client renderer for holographic name tags: faux-3D extruded text on a projected holo plate
// (beam + emitter ring, scanlines, corner brackets, chromatic ghosts, bob, glitch, materialise).
// Only vanilla assets: font gui/fonts/sdf_MetronBook24, panel style rover_sim_colorable (solid colour).

class EZHoloTagW
{
	Widget Root;
	Widget Beam, Ring, RingCore, Plate, PlateGlow, EdgeT, EdgeB, Glitch;
	ref array<Widget> Scan = new array<Widget>;
	ref array<Widget> Br = new array<Widget>;
	ref array<TextWidget> Depth = new array<TextWidget>;
	TextWidget ChromaC, ChromaM, Main;

	void EZHoloTagW(Widget root)
	{
		Root = root;
		Beam = root.FindAnyWidget("Beam");
		Ring = root.FindAnyWidget("Ring");
		RingCore = root.FindAnyWidget("RingCore");
		Plate = root.FindAnyWidget("Plate");
		PlateGlow = root.FindAnyWidget("PlateGlow");
		EdgeT = root.FindAnyWidget("EdgeT");
		EdgeB = root.FindAnyWidget("EdgeB");
		Glitch = root.FindAnyWidget("Glitch");
		int i;
		for (i = 0; i < 4; i++)
			Scan.Insert(root.FindAnyWidget("Scan" + i.ToString()));
		for (i = 0; i < 8; i++)
			Br.Insert(root.FindAnyWidget("Br" + i.ToString()));
		for (i = 0; i < 3; i++)
			Depth.Insert(TextWidget.Cast(root.FindAnyWidget("Depth" + i.ToString())));
		ChromaC = TextWidget.Cast(root.FindAnyWidget("ChromaC"));
		ChromaM = TextWidget.Cast(root.FindAnyWidget("ChromaM"));
		Main = TextWidget.Cast(root.FindAnyWidget("Main"));
	}

	bool IsValid()
	{
		return Root && Plate && Main && ChromaC && ChromaM && Beam && Ring && RingCore && PlateGlow && EdgeT && EdgeB && Glitch && Scan.Count() == 4 && Br.Count() == 8 && Depth.Count() == 3;
	}
}

class EZHoloRenderer
{
	protected ref array<ref EZHoloTagW> m_Pool = new array<ref EZHoloTagW>;
	protected int m_Used;
	protected float m_Time;
	protected ref map<int, float> m_Born = new map<int, float>; // seed -> first-seen time (materialise)

	void ~EZHoloRenderer()
	{
		foreach (EZHoloTagW t : m_Pool)
		{
			if (t && t.Root)
				t.Root.Unlink();
		}
	}

	protected EZHoloTagW Get()
	{
		if (m_Used >= m_Pool.Count())
		{
			Widget root = GetGame().GetWorkspace().CreateWidgets("EZLoderScreen/gui/layouts/ez_holotag.layout");
			if (!root)
				return null;
			EZHoloTagW nt = new EZHoloTagW(root);
			if (!nt.IsValid())
			{
				root.Unlink();
				return null;
			}
			m_Pool.Insert(nt);
		}
		EZHoloTagW t = m_Pool[m_Used];
		m_Used++;
		return t;
	}

	// colour from hex with alpha, optionally blended toward white (0..1)
	static int EZCol(string hex, int alpha, float toWhite = 0)
	{
		int rgb = EZHoloConfig.HexToARGB(hex, 0) & 0xFFFFFF;
		int r = (rgb >> 16) & 0xFF;
		int g = (rgb >> 8) & 0xFF;
		int b = rgb & 0xFF;
		r = r + (255 - r) * toWhite;
		g = g + (255 - g) * toWhite;
		b = b + (255 - b) * toWhite;
		alpha = Math.Clamp(alpha, 0, 255);
		return (alpha << 24) | (r << 16) | (g << 8) | b;
	}

	protected static void Rect(Widget w, float x, float y, float rw, float rh, int col)
	{
		w.SetPos(x, y);
		w.SetSize(Math.Max(rw, 1), Math.Max(rh, 1));
		w.SetColor(col);
		w.Show(true);
	}

	protected static void Txt(TextWidget w, string s, float x, float y, float tw, float th, int fs, int col)
	{
		w.SetText(s);
		w.SetTextExactSize(fs);
		w.SetPos(x, y);
		w.SetSize(tw, th);
		w.SetColor(col);
		w.Show(true);
	}

	protected void Draw(vector world, string name, string hex, float dist, float maxDist, int seed, EZHoloConfig cfg)
	{
		vector s = GetGame().GetScreenPos(world);
		if (s[2] <= 0)
			return;
		int sw, sh;
		GetScreenSize(sw, sh);
		if (s[0] < -200 || s[0] > sw + 200 || s[1] < -200 || s[1] > sh + 200)
			return;
		EZHoloTagW t = Get();
		if (!t)
			return;

		EZClientSettings us = EZClientSettings.Get();
		bool fx = cfg.Flicker && us.TagFlicker;

		// --- alpha: flicker, materialise, distance fade, user opacity
		float a = 235;
		if (fx)
		{
			a = 200 + 35 * Math.Sin(m_Time * 9.0 + seed);
			if (Math.RandomFloat01() < 0.02)
				a = 80; // glitch dropout
		}
		if (!m_Born.Contains(seed))
			m_Born.Set(seed, m_Time);
		float age = m_Time - m_Born.Get(seed);
		if (age < 0.6)
		{
			float mat = age / 0.6;
			if (fx && Math.RandomFloat01() < 0.5)
				mat = mat * 0.3;
			a = a * mat;
		}
		if (maxDist > 0 && dist > maxDist * 0.7)
			a = a * Math.Clamp((maxDist - dist) / (maxDist * 0.3), 0.25, 1.0);
		a = a * us.TagOpacity;
		int al = Math.Clamp(a, 0, 255);

		// --- perspective scale: closer = bigger
		float k = Math.Clamp(5.0 / Math.Max(dist, 1.0), 0.6, 1.25);
		int fs = Math.Round(us.TagSize * k);
		if (fs < 10)
			fs = 10;
		string label = name;
		label.ToUpper();
		float tw = fs * 0.62 * label.Length() + 4;
		float th = fs * 1.3;
		float pad = 14 * k;
		float pw = tw + pad * 2;
		float ph = th * 0.85 + 6 * k;         // slight vertical squash of the plate
		float beamH = 34 * k;
		float ringW = pw * 0.45;
		float ringH = 5 * k;
		float W = pw + 20;
		float H = ph + beamH + ringH + 10;
		float bob = 0;
		if (fx)
			bob = 2.5 * k * Math.Sin(m_Time * 2.2 + seed * 0.7);

		t.Root.SetPos(s[0] - W * 0.5, s[1] - H);
		t.Root.SetSize(W, H);
		t.Root.Show(true);

		float px = 10;
		float py = 4 + bob;
		float cx = W * 0.5;
		float ringY = H - ringH - 2;

		// projection: beam from emitter ring up to plate, ring glow on the head
		Rect(t.Beam, cx - 3 * k, py + ph, 6 * k, ringY - (py + ph) + ringH * 0.5, EZCol(hex, al * 0.22, 0.2));
		Rect(t.Ring, cx - ringW * 0.5, ringY, ringW, ringH, EZCol(hex, al * 0.35, 0.1));
		Rect(t.RingCore, cx - ringW * 0.2, ringY + ringH * 0.25, ringW * 0.4, ringH * 0.5, EZCol(hex, al * 0.8, 0.6));

		// plate: outer glow + translucent fill + bright top/bottom edges
		Rect(t.PlateGlow, px - 4, py - 4, pw + 8, ph + 8, EZCol(hex, al * 0.10, 0));
		Rect(t.Plate, px, py, pw, ph, EZCol(hex, al * 0.22, 0));
		float shimmer = 0.75;
		if (fx)
			shimmer = 0.6 + 0.4 * Math.AbsFloat(Math.Sin(m_Time * 3.0 + seed));
		Rect(t.EdgeT, px, py, pw, 1.5, EZCol(hex, al * shimmer, 0.5));
		Rect(t.EdgeB, px, py + ph - 1.5, pw, 1.5, EZCol(hex, al * 0.6, 0.3));

		// corner brackets (horizontal + vertical stroke per corner)
		float bl = Math.Max(8 * k, 5);
		float bt = 2;
		int bc = EZCol(hex, al, 0.65);
		Rect(t.Br[0], px - 3, py - 3, bl, bt, bc);              Rect(t.Br[1], px - 3, py - 3, bt, bl, bc);
		Rect(t.Br[2], px + pw + 3 - bl, py - 3, bl, bt, bc);    Rect(t.Br[3], px + pw + 3 - bt, py - 3, bt, bl, bc);
		Rect(t.Br[4], px - 3, py + ph + 3 - bt, bl, bt, bc);    Rect(t.Br[5], px - 3, py + ph + 3 - bl, bt, bl, bc);
		Rect(t.Br[6], px + pw + 3 - bl, py + ph + 3 - bt, bl, bt, bc); Rect(t.Br[7], px + pw + 3 - bt, py + ph + 3 - bl, bt, bl, bc);

		// moving scanlines inside the plate
		for (int i = 0; i < 4; i++)
		{
			float f = m_Time * 0.35 + i * 0.25 + seed * 0.13;
			f = f - Math.Floor(f);
			Rect(t.Scan[i], px + 1, py + 1 + f * (ph - 3), pw - 2, 1, EZCol(hex, al * 0.28, 0.4));
		}

		// glitch slice: occasional bright horizontal band shifted sideways
		if (fx && Math.RandomFloat01() < 0.05)
			Rect(t.Glitch, px + Math.RandomFloat(-6, 6), py + Math.RandomFloat01() * ph, pw, Math.RandomFloat(2, 5), EZCol(hex, al * 0.5, 0.7));
		else
			t.Glitch.Show(false);

		// text: 3 extrusion layers going back/down, chromatic ghosts, bright main face
		float jitter = 0;
		if (fx && Math.RandomFloat01() < 0.04)
			jitter = Math.RandomFloat(-2, 2);
		float tx = px + pad + jitter;
		float ty = py + (ph - th) * 0.5;
		for (int d = 0; d < 3; d++)
		{
			float o = (3 - d) * 1.2 * k;
			Txt(t.Depth[d], label, tx + o, ty + o, tw, th, fs, EZCol(hex, al * (0.18 + 0.12 * d), 0));
			t.Depth[d].SetOutline(0, 0);
		}
		Txt(t.ChromaC, label, tx - 1, ty, tw, th, fs, ARGB(al * 0.35, 0, 255, 255));
		Txt(t.ChromaM, label, tx + 1, ty, tw, th, fs, ARGB(al * 0.35, 255, 0, 255));
		Txt(t.Main, label, tx, ty, tw, th, fs, EZCol(hex, al, 0.55));
		t.Main.SetOutline(2, EZCol(hex, al * 0.6, 0));
	}

	void Update(float dt)
	{
		m_Time += dt;
		m_Used = 0;
		EZHoloConfig cfg = EZHolo.s_ClientCfg;
		PlayerBase me = PlayerBase.Cast(GetGame().GetPlayer());
		EZClientSettings us = EZClientSettings.Get();
		if (cfg && cfg.Enabled && us.ShowTags && me && me.IsAlive() && !GetGame().GetUIManager().GetMenu())
		{
			float maxD = Math.Min(us.TagDistance, cfg.MaxDistance); // server caps client
			if (us.ShowOwnTag && me.EZ_GetHoloType() != 0)
			{
				vector myHead = me.GetBonePositionWS(me.GetBoneIndexByName("Head")) + "0 0.45 0";
				string myHex = cfg.ColorPlayer;
				if (me.EZ_GetHoloType() == 2)
					myHex = cfg.ColorAdmin;
				Draw(myHead, EZName(me, "You"), myHex, 1, 0, me.GetID(), cfg);
			}
			vector cam = GetGame().GetCurrentCameraPosition();
			bool meInZone = cfg.InZone(me.GetPosition());
			array<vector> drawnAdmins = new array<vector>;

			array<PlayerBase> tracked = EZHolo.Tracked();
			if (!tracked)
				tracked = new array<PlayerBase>; // defensive: never iterate null
			foreach (PlayerBase p : tracked)
			{
				if (!p || p == me || !p.IsAlive())
					continue;
				int t = p.EZ_GetHoloType();
				vector head = p.GetBonePositionWS(p.GetBoneIndexByName("Head")) + "0 0.45 0";
				float d = vector.Distance(cam, head);
				if (t == 2)
				{
					if (!us.ShowAdminTags)
						continue;
					if (d <= cfg.AdminMaxDistance)
					{
						Draw(head, EZName(p, "ADMIN"), cfg.ColorAdmin, d, 0, p.GetID(), cfg);
						drawnAdmins.Insert(p.GetPosition());
					}
					continue;
				}
				if (t == 4 && cfg.BanditTagsEverywhere)
				{
					if (d <= maxD)
						Draw(head, "Bandit: " + p.GetDisplayName(), cfg.ColorBandit, d, maxD, p.GetID(), cfg);
					continue;
				}
				// non-admin holos: viewer AND target inside a sanctuary, within MaxDistance
				if (!meInZone || d > maxD || !cfg.InZone(p.GetPosition()))
					continue;
				if (t == 4)
					Draw(head, "Bandit: " + p.GetDisplayName(), cfg.ColorBandit, d, maxD, p.GetID(), cfg);
				if (t == 1)
					Draw(head, EZName(p, "Survivor"), cfg.ColorPlayer, d, maxD, p.GetID(), cfg);
				else if (t == 3)
					Draw(head, cfg.GuardName, cfg.ColorGuard, d, maxD, p.GetID(), cfg);
			}

			// far-away admins (outside network bubble) from the 2 s server broadcast
			if (us.ShowAdminTags && EZHolo.s_AdminNames && EZHolo.s_AdminPos)
			{
				string myName;
				if (me.GetIdentity())
					myName = me.GetIdentity().GetName();
				for (int i = 0; i < EZHolo.s_AdminNames.Count() && i < EZHolo.s_AdminPos.Count(); i++)
				{
					vector ap = EZHolo.s_AdminPos[i];
					if (EZHolo.s_AdminNames[i] == myName && vector.Distance(ap, me.GetPosition()) < 10)
						continue;
					bool dup = false;
					foreach (vector dp : drawnAdmins)
					{
						if (vector.Distance(dp, ap) < 15) { dup = true; break; }
					}
					if (dup)
						continue;
					float ad = vector.Distance(cam, ap);
					if (ad <= cfg.AdminMaxDistance)
						Draw(ap, EZHolo.s_AdminNames[i] + "  " + Math.Round(ad).ToString() + "m", cfg.ColorAdmin, ad, 0, i * 7, cfg);
				}
			}
		}
		for (int k = m_Used; k < m_Pool.Count(); k++)
			m_Pool[k].Root.Show(false);
	}

	protected string EZName(PlayerBase p, string fallback)
	{
		if (p.GetIdentity())
			return p.GetIdentity().GetName();
		return fallback;
	}
}

modded class MissionGameplay
{
	ref EZHoloRenderer m_EZHolo;
	int m_EZEarIdx;              // index into EarplugLevels; 0 = first level (normally 100%)
	float m_EZOrigVolume = -1;
	Widget m_EZEarHud;
	float m_EZFlipArmed;
	bool m_EZPrefsSent;

	override void OnUpdate(float timeslice)
	{
		super.OnUpdate(timeslice);
		if (!m_EZHolo)
			m_EZHolo = new EZHoloRenderer();
		m_EZHolo.Update(timeslice);
		if (m_EZFlipArmed > 0)
			m_EZFlipArmed -= timeslice;

		PlayerBase me = PlayerBase.Cast(GetGame().GetPlayer());
		if (me && !m_EZPrefsSent && me.GetIdentity())
		{
			EZClientPrefs.Send();
			m_EZPrefsSent = true;
		}
		if (GetGame().GetUIManager().GetMenu())
			return;

		if (EZPressed("UAEZHoloAdmin") && me)
			me.RPCSingleParam(EZ_RPC_HOLO_TOGGLE, new Param1<bool>(true), true);
		if (EZPressed("UAEZEarplugs"))
			EZ_CycleEarplugs();
		if (EZPressed("UAEZSettings"))
			GetGame().GetUIManager().EnterScriptedMenu(EZ_MENU_SETTINGS, null);
		if (EZPressed("UAEZFlipVehicle") && me)
			EZ_FlipKey(me);
	}

	protected bool EZPressed(string name)
	{
		UAInput inp = GetUApi().GetInputByName(name);
		return inp && inp.LocalPress();
	}

	void EZ_FlipKey(PlayerBase me)
	{
		CarScript car;
		vector from = GetGame().GetCurrentCameraPosition();
		vector to = from + GetGame().GetCurrentCameraDirection() * 5;
		vector hitPos, hitNormal;
		int comp;
		set<Object> hits = new set<Object>;
		if (DayZPhysics.RaycastRV(from, to, hitPos, hitNormal, comp, hits, null, me, false, false, ObjIntersectView, 0.3))
		{
			foreach (Object o : hits)
			{
				car = CarScript.Cast(o);
				if (car)
					break;
			}
		}
		if (!car || !EZFlip.CanFlip(me, car))
		{
			NotificationSystem.AddNotificationExtended(3, "Flip vehicle", "Look at an overturned, empty vehicle with the engine off.", "set:dayz_gui image:icon_info");
			return;
		}
		if (EZClientSettings.Get().FlipConfirm && m_EZFlipArmed <= 0)
		{
			m_EZFlipArmed = 3.0;
			NotificationSystem.AddNotificationExtended(3, "Flip vehicle", "Press again within 3 s to flip.", "set:dayz_gui image:icon_info");
			return;
		}
		m_EZFlipArmed = 0;
		me.RPCSingleParam(EZ_RPC_FLIP_REQUEST, new Param1<Object>(car), true);
	}

	void EZ_CycleEarplugs()
	{
		EZClientSettings s = EZClientSettings.Get();
		AbstractSoundScene scene = GetGame().GetSoundScene();
		if (!scene)
			return;
		if (m_EZOrigVolume < 0)
			m_EZOrigVolume = scene.GetSoundVolume();
		m_EZEarIdx = (m_EZEarIdx + 1) % s.EarplugLevels.Count();
		int pct = s.EarplugLevels[m_EZEarIdx];
		scene.SetSoundVolume(m_EZOrigVolume * pct / 100.0, 0.5);
		string txt = "Earplugs OUT (" + pct.ToString() + "%)";
		if (pct < 100)
			txt = "Earplugs IN - game volume " + pct.ToString() + "%";
		NotificationSystem.AddNotificationExtended(2, "Earplugs", txt, "set:dayz_gui image:icon_info");
		if (!m_EZEarHud)
			m_EZEarHud = GetGame().GetWorkspace().CreateWidgets("EZLoderScreen/gui/layouts/ez_earhud.layout");
		if (m_EZEarHud)
		{
			TextWidget t = TextWidget.Cast(m_EZEarHud);
			if (t)
				t.SetText("EARPLUGS " + pct.ToString() + "%");
			m_EZEarHud.Show(pct < 100 && s.EarplugHud);
		}
	}

	override void OnMissionFinish()
	{
		AbstractSoundScene scene = GetGame().GetSoundScene();
		if (scene && m_EZOrigVolume >= 0)
			scene.SetSoundVolume(m_EZOrigVolume, 0);
		if (m_EZEarHud)
			m_EZEarHud.Unlink();
		super.OnMissionFinish();
	}
}

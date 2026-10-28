// EZLoderScreen 9.7 - EchelonZ main menu + lobby overlay.
// Add-on approach: vanilla/Expansion/Dabs Init() runs first via super, then our
// layout is created ON TOP of layoutRoot. Replaced vanilla widgets are only hidden
// (Show(false)), never destroyed, so other mods that look them up keep working.
// The lobby is a panel inside MainMenu (not a separate menu/mission), so the
// DynamicMusicPlayer is never touched by screen changes and menu music never cuts.
// Nothing in this file calls SetCategory / Stop on the DMP except the user's
// NEXT button (EZ_SkipTrack).
modded class MainMenu
{
	protected Widget          m_EZRoot;
	protected Widget          m_EZMainPanel;
	protected Widget          m_EZLobbyPanel;
	protected ImageWidget     m_EZBgA;
	protected ImageWidget     m_EZBgB;
	protected ImageWidget     m_EZLobbyBg;
	protected TextWidget      m_EZNowTrack;
	protected TextWidget      m_EZLobbyAddr;
	protected TextWidget      m_EZLobbyChar;
	protected ref array<string> m_EZBackgrounds;
	protected int             m_EZBgIndex;
	protected float           m_EZBgTimer;
	protected float           m_EZFade;		// < 0 = not fading
	protected bool            m_EZBgAFront;
	protected bool            m_EZInLobby;
	protected float           m_EZTrackTimer;
	protected string          m_EZLastTrack;

	override Widget Init()
	{
		Widget root = super.Init();
		if (!root)
			return root;

		m_EZRoot = g_Game.GetWorkspace().CreateWidgets("EZLoderScreen/gui/layouts/ez_mainmenu.layout", root);
		if (!m_EZRoot)
		{
			Print("[EZLoderScreen] ez_mainmenu.layout failed to load - keeping stock menu");
			return root;
		}

		m_EZMainPanel  = m_EZRoot.FindAnyWidget("EZMainPanel");
		m_EZLobbyPanel = m_EZRoot.FindAnyWidget("EZLobbyPanel");
		m_EZBgA        = ImageWidget.Cast(m_EZRoot.FindAnyWidget("EZBgA"));
		m_EZBgB        = ImageWidget.Cast(m_EZRoot.FindAnyWidget("EZBgB"));
		m_EZLobbyBg    = ImageWidget.Cast(m_EZRoot.FindAnyWidget("EZLobbyBg"));
		m_EZNowTrack   = TextWidget.Cast(m_EZRoot.FindAnyWidget("EZNowTrack"));
		m_EZLobbyAddr  = TextWidget.Cast(m_EZRoot.FindAnyWidget("EZLobbyAddr"));
		m_EZLobbyChar  = TextWidget.Cast(m_EZRoot.FindAnyWidget("EZLobbyChar"));

		EZ_MenuConfig.GetBackgrounds(m_EZBackgrounds);
		m_EZBgIndex  = 0;
		m_EZBgTimer  = 0;
		m_EZFade     = -1;
		m_EZBgAFront = true;
		if (m_EZBgA && m_EZBackgrounds.Count() > 0)
		{
			m_EZBgA.LoadImageFile(0, m_EZBackgrounds[0]);
			m_EZBgA.SetAlpha(1);
		}
		if (m_EZBgB)
		{
			if (m_EZBackgrounds.Count() > 1)
				m_EZBgB.LoadImageFile(0, m_EZBackgrounds[1]);
			m_EZBgB.SetAlpha(0);
		}
		if (m_EZLobbyBg)
			m_EZLobbyBg.LoadImageFile(0, EZ_MenuConfig.GetLobbyBackground());

		EZ_FillNews();
		if (m_EZLobbyAddr)
			m_EZLobbyAddr.SetText(EZ_MenuConfig.SERVER_IP + ":" + EZ_MenuConfig.SERVER_PORT.ToString());
		TextWidget sub = TextWidget.Cast(m_EZRoot.FindAnyWidget("EZBtn_Play_Sub"));
		if (sub)
			sub.SetText("Direct connect - " + EZ_MenuConfig.SERVER_IP);

		EZ_HideStock();
		EZ_ShowLobby(false);
		EZ_UpdateNowPlaying(true);
		return root;
	}

	protected void EZ_HideStock()
	{
		if (!layoutRoot || !m_EZRoot)
			return;
		array<string> names = {"play_panel_root", "settings_panel_root", "dayz_logo", "carousel_Frame", "last_server_info", "character_stats_root", "character_name_xbox_background", "dlc_Frame"};
		foreach (string n : names)
		{
			Widget w = layoutRoot.FindAnyWidget(n);
			if (w)
				w.Show(false);
		}
	}

	protected void EZ_FillNews()
	{
		MultilineTextWidget news = MultilineTextWidget.Cast(m_EZRoot.FindAnyWidget("EZNewsText"));
		if (!news)
			return;
		array<string> heads;
		array<string> bodies;
		EZ_MenuConfig.GetNews(heads, bodies);
		string txt = "";
		for (int i = 0; i < heads.Count(); i++)
		{
			txt = txt + heads[i] + "\n";
			if (i < bodies.Count())
				txt = txt + bodies[i] + "\n";
			txt = txt + "\n";
		}
		news.SetText(txt);
	}

	protected void EZ_ShowLobby(bool show)
	{
		m_EZInLobby = show;
		if (m_EZMainPanel)  m_EZMainPanel.Show(!show);
		if (m_EZLobbyPanel) m_EZLobbyPanel.Show(show);
		if (m_EZLobbyBg)    m_EZLobbyBg.Show(show);
		if (show && m_EZLobbyChar)
		{
			string pname = "Survivor";
			GetGame().GetPlayerName(pname);
			if (pname == "") pname = "Survivor";
			m_EZLobbyChar.SetText("Character: " + pname);
		}
	}

	protected void EZ_Join()
	{
		Print("[EZLoderScreen] Direct connect " + EZ_MenuConfig.SERVER_IP + ":" + EZ_MenuConfig.SERVER_PORT.ToString());
		g_Game.ConnectFromServerBrowser(EZ_MenuConfig.SERVER_IP, EZ_MenuConfig.SERVER_PORT, EZ_MenuConfig.SERVER_PASSWORD);
	}

	protected void EZ_UpdateNowPlaying(bool force)
	{
		if (!m_EZNowTrack)
			return;
		string ss = "";
		Mission mission = g_Game.GetMission();
		if (mission)
		{
			DynamicMusicPlayer dmp = mission.GetDynamicMusicPlayer();
			if (dmp)
				ss = dmp.EZ_GetCurrentSoundSet();
		}
		if (!force && ss == m_EZLastTrack)
			return;
		m_EZLastTrack = ss;
		if (ss == "")
			m_EZNowTrack.SetText("...");
		else
			m_EZNowTrack.SetText(EZ_MenuConfig.TrackDisplayName(ss) + "  -  EchelonZ Menu Theme");
	}


	protected void EZ_UpdateBackground(float timeslice)
	{
		if (!m_EZBgA || !m_EZBgB || !m_EZBackgrounds || m_EZBackgrounds.Count() < 2)
			return;
		ImageWidget front = m_EZBgB;
		ImageWidget back  = m_EZBgA;
		if (m_EZBgAFront)
		{
			front = m_EZBgA;
			back  = m_EZBgB;
		}
		if (m_EZFade < 0)
		{
			m_EZBgTimer += timeslice;
			if (m_EZBgTimer >= EZ_MenuConfig.BG_HOLD_SECONDS)
			{
				m_EZBgTimer = 0;
				m_EZFade = 0;
				int next = (m_EZBgIndex + 1) % m_EZBackgrounds.Count();
				back.LoadImageFile(0, m_EZBackgrounds[next]);
				back.SetAlpha(0);
				m_EZBgIndex = next;
			}
			return;
		}
		m_EZFade += timeslice;
		float a = Math.Clamp(m_EZFade / EZ_MenuConfig.BG_FADE_SECONDS, 0, 1);
		// back sits under front in the layout only for B; keep both drawn and swap alphas
		back.SetAlpha(a);
		front.SetAlpha(1 - a);
		if (a >= 1)
		{
			m_EZFade = -1;
			m_EZBgAFront = !m_EZBgAFront;
		}
	}

	override void Update(float timeslice)
	{
		if (m_EZRoot && m_EZInLobby && g_Game && GetUApi().GetInputByID(UAUIBack).LocalPress())
		{
			// Back in the lobby returns to the main panel instead of opening Exit.
			EZ_ShowLobby(false);
			return;
		}
		super.Update(timeslice);
		if (!m_EZRoot)
			return;
		EZ_UpdateBackground(timeslice);
		m_EZTrackTimer += timeslice;
		if (m_EZTrackTimer >= 1.0)
		{
			m_EZTrackTimer = 0;
			EZ_UpdateNowPlaying(false);
		}
	}

	override void OnShow()
	{
		super.OnShow();
		// vanilla OnShow / carousel refresh can re-show stock widgets
		EZ_HideStock();
		EZ_UpdateNowPlaying(true);
	}

	override bool OnClick(Widget w, int x, int y, int button)
	{
		if (m_EZRoot && w && button == MouseState.LEFT)
		{
			switch (w.GetName())
			{
				case "EZBtn_Play":       EZ_ShowLobby(true);          return true;
				case "EZBtn_LobbyJoin":  EZ_Join();                   return true;
				case "EZBtn_LobbyBack":  EZ_ShowLobby(false);         return true;
				case "EZBtn_Browser":    OpenMenuServerBrowser();     return true;
				case "EZBtn_Character":  OpenMenuCustomizeCharacter(); return true;
				case "EZBtn_Settings":   OpenSettings();              return true;
				case "EZBtn_Discord":    g_Game.OpenURL(EZ_MenuConfig.DISCORD_URL); return true;
				case "EZBtn_Exit":       Exit();                      return true;
			}
		}
		return super.OnClick(w, x, y, button);
	}

	protected bool EZ_IsOurButton(Widget w)
	{
		if (!w || !m_EZRoot)
			return false;
		string n = w.GetName();
		return n.IndexOf("EZBtn_") == 0 && n.IndexOf("_Lbl") < 0;
	}

	override bool OnMouseEnter(Widget w, int x, int y)
	{
		if (EZ_IsOurButton(w))
		{
			TextWidget lbl = TextWidget.Cast(w.FindAnyWidget(w.GetName() + "_Lbl"));
			if (lbl)
				lbl.SetColor(ARGB(255, 255, 196, 120));
			return true;
		}
		return super.OnMouseEnter(w, x, y);
	}

	override bool OnMouseLeave(Widget w, Widget enterW, int x, int y)
	{
		if (EZ_IsOurButton(w))
		{
			TextWidget lbl = TextWidget.Cast(w.FindAnyWidget(w.GetName() + "_Lbl"));
			if (lbl)
				lbl.SetColor(ARGB(255, 255, 255, 255));
			return true;
		}
		return super.OnMouseLeave(w, enterW, x, y);
	}
}

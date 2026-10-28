// EZLoderScreen client settings menu. Opened from the "EZLoderScreen" button injected into
// DayZ Options, or with the keybind (default F7). Saved to the client profile.
const int EZ_MENU_SETTINGS = 82341100;

class EZSettingsMenu : UIScriptedMenu
{
	override Widget Init()
	{
		layoutRoot = GetGame().GetWorkspace().CreateWidgets("EZLoderScreen/gui/layouts/ez_settings.layout");
		Refresh();
		return layoutRoot;
	}

	protected void SetBtn(string id, string text)
	{
		ButtonWidget b = ButtonWidget.Cast(layoutRoot.FindAnyWidget("EZBtn_" + id));
		if (b)
			b.SetText(text);
	}

	protected string OnOff(int v)
	{
		if (v)
			return "ON";
		return "OFF";
	}

	void Refresh()
	{
		EZClientSettings s = EZClientSettings.Get();
		string lv = "";
		foreach (int l : s.EarplugLevels)
			lv = lv + l.ToString() + "% ";
		float cap = 15;
		if (EZHolo.s_ClientCfg)
			cap = EZHolo.s_ClientCfg.MaxDistance;
		SetBtn("ShowTags", "Name tags: " + OnOff(s.ShowTags));
		SetBtn("ShowAdminTags", "Admin tags: " + OnOff(s.ShowAdminTags));
		SetBtn("TagOpacity", "Tag opacity: " + Math.Round(s.TagOpacity * 100).ToString() + "%");
		SetBtn("TagSize", "Tag size: " + s.TagSize.ToString() + " px");
		SetBtn("TagDistance", "Tag distance: " + Math.Round(s.TagDistance).ToString() + " m (server max " + Math.Round(cap).ToString() + " m)");
		SetBtn("TagFlicker", "Holo flicker: " + OnOff(s.TagFlicker));
		SetBtn("ShowOwnTag", "Show my own tag: " + OnOff(s.ShowOwnTag));
		SetBtn("Earplugs", "Earplug levels: " + lv);
		SetBtn("EarplugHud", "Earplug HUD indicator: " + OnOff(s.EarplugHud));
		SetBtn("FlipConfirm", "Flip key needs confirm press: " + OnOff(s.FlipConfirm));
		SetBtn("StickyGag", "Sticky-hands gag messages: " + OnOff(s.StickyGagMessages));
		SetBtn("Close", "Save & close");
	}

	override bool OnClick(Widget w, int x, int y, int button)
	{
		EZClientSettings s = EZClientSettings.Get();
		string n = w.GetName();
		if (n == "EZBtn_ShowTags") s.ShowTags = !s.ShowTags;
		else if (n == "EZBtn_ShowAdminTags") s.ShowAdminTags = !s.ShowAdminTags;
		else if (n == "EZBtn_TagOpacity") { s.TagOpacity = s.TagOpacity - 0.2; if (s.TagOpacity < 0.19) s.TagOpacity = 1.0; }
		else if (n == "EZBtn_TagSize") { s.TagSize = s.TagSize + 4; if (s.TagSize > 28) s.TagSize = 14; }
		else if (n == "EZBtn_TagDistance") { s.TagDistance = s.TagDistance + 5; if (s.TagDistance > 50) s.TagDistance = 5; }
		else if (n == "EZBtn_TagFlicker") s.TagFlicker = !s.TagFlicker;
		else if (n == "EZBtn_ShowOwnTag") s.ShowOwnTag = !s.ShowOwnTag;
		else if (n == "EZBtn_Earplugs")
		{
			// presets: 100/50/25 -> 100/30/10 -> 100/60 -> 100/20
			if (s.EarplugLevels.Count() == 3 && s.EarplugLevels[1] == 50) s.EarplugLevels = {100, 30, 10};
			else if (s.EarplugLevels.Count() == 3) s.EarplugLevels = {100, 60};
			else if (s.EarplugLevels[1] == 60) s.EarplugLevels = {100, 20};
			else s.EarplugLevels = {100, 50, 25};
		}
		else if (n == "EZBtn_EarplugHud") s.EarplugHud = !s.EarplugHud;
		else if (n == "EZBtn_FlipConfirm") s.FlipConfirm = !s.FlipConfirm;
		else if (n == "EZBtn_StickyGag") { s.StickyGagMessages = !s.StickyGagMessages; EZClientPrefs.Send(); }
		else if (n == "EZBtn_Close") { s.Save(); Close(); return true; }
		else return false;
		s.Save();
		Refresh();
		return true;
	}
}

class EZClientPrefs
{
	static void Send()
	{
		PlayerBase me = PlayerBase.Cast(GetGame().GetPlayer());
		if (me && GetGame().IsClient())
			me.RPCSingleParam(EZ_RPC_CLIENT_PREFS, new Param1<bool>(EZClientSettings.Get().StickyGagMessages != 0), true);
	}
}

// Inject an "EZLoderScreen" button into DayZ Options (a native extra tab needs the vanilla tabber
// layout replaced, which would break other mods doing the same; a button is the safe equivalent).
modded class OptionsMenu
{
	protected ButtonWidget m_EZBtn;

	override Widget Init()
	{
		Widget r = super.Init();
		if (r)
		{
			m_EZBtn = ButtonWidget.Cast(GetGame().GetWorkspace().CreateWidgets("EZLoderScreen/gui/layouts/ez_optbutton.layout", r));
		}
		return r;
	}

	override bool OnClick(Widget w, int x, int y, int button)
	{
		if (m_EZBtn && w == m_EZBtn)
		{
			GetGame().GetUIManager().EnterScriptedMenu(EZ_MENU_SETTINGS, this);
			return true;
		}
		return super.OnClick(w, x, y, button);
	}
}

modded class MissionBase
{
	override UIScriptedMenu CreateScriptedMenu(int id)
	{
		if (id == EZ_MENU_SETTINGS)
		{
			EZSettingsMenu m = new EZSettingsMenu();
			m.SetID(id);
			return m;
		}
		return super.CreateScriptedMenu(id);
	}
}

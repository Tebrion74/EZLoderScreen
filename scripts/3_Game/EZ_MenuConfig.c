// EZLoderScreen 9.7 - EchelonZ main menu / lobby configuration.
// Edit this file to change the server address, news panel or track names.
class EZ_MenuConfig
{
	static const string SERVER_NAME     = "EchelonZ Badlands";
	static const string SERVER_IP       = "67.210.97.252";
	static const int    SERVER_PORT     = 2303;
	static const string SERVER_PASSWORD = "";
	static const string DISCORD_URL     = "https://discord.gg/Es6czQ2KXm";

	static const float  BG_HOLD_SECONDS = 12.0;	// time each background is shown
	static const float  BG_FADE_SECONDS = 2.5;	// crossfade length

	static void GetBackgrounds(out array<string> list)
	{
		list = new array<string>;
		list.Insert("EZLoderScreen/data/menu/ez_menu_bg1.edds");
		list.Insert("EZLoderScreen/data/menu/ez_menu_bg2.edds");
		list.Insert("EZLoderScreen/data/menu/ez_menu_bg3.edds");
		list.Insert("EZLoderScreen/data/menu/ez_menu_bg4.edds");
	}

	static string GetLobbyBackground()
	{
		return "EZLoderScreen/data/menu/ez_lobby_bg.edds";
	}

	// News / changelog panel. Each entry: header, body. Keep bodies short (2 lines).
	static void GetNews(out array<string> headers, out array<string> bodies)
	{
		headers = new array<string>;
		bodies  = new array<string>;
		headers.Insert("V9.7.0 - EZ-TURBITION");	bodies.Insert("Custom EchelonZ main menu, lobby and now-playing bar");
		headers.Insert("V9.6.3");			bodies.Insert("EZ-Turban with storage, loading-screen artwork update");
		headers.Insert("V10 - COMING");			bodies.Insert("More to come - watch Discord");
		headers.Insert("TRADERS");			bodies.Insert("Bam-e Sabz, Gandomabad, Varzaneh, Gard Abad, Kucha Dar, No Abad");
		headers.Insert("RULES");			bodies.Insert("PvE sanctuaries, PvP everywhere else");
	}

	// SoundSet -> display name for the now-playing bar.
	static string TrackDisplayName(string soundSet)
	{
		switch (soundSet)
		{
			case "EZ_Menu_Rot_SoundSet":    return "Rot";
			case "EZ_Menu_Poe_SoundSet":    return "Poe";
			case "EZ_Menu_Boogie_SoundSet": return "Boogie";
			case "EZ_Menu_Crypt_SoundSet":  return "Crypt";
			case "EZ_Menu_Creep_SoundSet":  return "Creep";
			case "EZ_Menu_Morgue_SoundSet": return "Morgue";
		}
		if (soundSet == "")
			return "";
		string s = soundSet;
		s.Replace("_SoundSet", "");
		return s;
	}
}

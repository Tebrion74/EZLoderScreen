// Verified against vanilla 1.30 scripts (diff.yadz.app, 3_Game/Systems/DynamicMusicPlayer):
//   protected void RegisterTrackMenu(string soundSetName, bool hasPriority = false, int timeOfDay = DynamicMusicPlayerTimeOfDay.ANY)
// hasPriority only matters for the first menu pick after the player is created
// (SelectRandomTrackIndexFromCategoryPriorityFlagFirst); later picks are random with a history buffer.
// DynamicMusicPlayerRegistryNasdara overrides RegisterTracksMenu() without calling super
// (it registers Music_nasdara_menu_SoundSet), so modding only the base class does nothing on Nasdara.
// Chernarus/Enoch/Sakhal registries do not override it.
modded class DynamicMusicPlayerRegistry
{
	protected void EZ_RegisterTracksMenu()
	{
		m_TracksMenu = new array<ref DynamicMusicTrackData>();

		RegisterTrackMenu("EZ_Menu_Rot_SoundSet", true);
		RegisterTrackMenu("EZ_Menu_Poe_SoundSet", true);
		RegisterTrackMenu("EZ_Menu_Boogie_SoundSet", true);
		RegisterTrackMenu("EZ_Menu_Crypt_SoundSet", true);
		RegisterTrackMenu("EZ_Menu_Creep_SoundSet", true);
		RegisterTrackMenu("EZ_Menu_Morgue_SoundSet", true);
	}

	override protected void RegisterTracksMenu()
	{
		EZ_RegisterTracksMenu();
	}
}

modded class DynamicMusicPlayerRegistryNasdara
{
	override protected void RegisterTracksMenu()
	{
		EZ_RegisterTracksMenu();
	}
}

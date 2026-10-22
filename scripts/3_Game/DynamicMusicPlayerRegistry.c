modded class DynamicMusicPlayerRegistry
{
	// 1.29+: RegisterTrackMenu(string soundSet, bool hasPriority = false, int timeOfDay = ANY).
	// One SoundSet per track so the DynamicMusicPlayer random pick + history buffer works;
	// all flagged hasPriority so priority-first selection always picks an EZ track.
	protected override void RegisterTracksMenu()
	{
		m_TracksMenu = new array<ref DynamicMusicTrackData>();

		RegisterTrackMenu("EZ_Menu_Rot_SoundSet", true);
		RegisterTrackMenu("EZ_Menu_Poe_SoundSet", true);
		RegisterTrackMenu("EZ_Menu_Boogie_SoundSet", true);
		RegisterTrackMenu("EZ_Menu_Crypt_SoundSet", true);
		RegisterTrackMenu("EZ_Menu_Creep_SoundSet", true);
		RegisterTrackMenu("EZ_Menu_Morgue_SoundSet", true);
	}
}

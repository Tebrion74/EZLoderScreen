modded class DynamicMusicPlayerRegistry
{
    protected override void RegisterTracksMenu()
	{
		m_TracksMenu = new array<ref DynamicMusicTrackData>();

		RegisterTrackMenu("Josies_Menu_SoundSet");
		//RegisterTrackMenu("FMusic_Menu_SoundSet_2");
	}
}
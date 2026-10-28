// Per-client settings, saved in the CLIENT profile: <Documents>/DayZ/EZLoderScreen_client.json
// Server config still caps everything gameplay-relevant (e.g. tag distance can never exceed server MaxDistance).
class EZClientSettings
{
	int ShowTags = 1;
	int ShowAdminTags = 1;
	float TagOpacity = 1.0;        // 0.2 .. 1.0
	int TagSize = 18;              // 12 .. 28 px
	float TagDistance = 40.0;      // capped by server MaxDistance
	int TagFlicker = 1;
	int ShowOwnTag = 0;
	ref array<int> EarplugLevels = {100, 50, 25}; // cycle order, percent
	int EarplugHud = 1;
	int FlipConfirm = 1;           // keybind flip needs a second press within 3 s
	int LoadingTips = 1;
	int StickyGagMessages = 1;     // purely cosmetic chat/notification lines
	int SettingsVersion = 0;       // 2 = tag distance default raised 15 -> 40

	static const string PATH = "$profile:EZLoderScreen_client.json";
	protected static ref EZClientSettings s_Inst;

	static EZClientSettings Get()
	{
		if (!s_Inst)
		{
			s_Inst = new EZClientSettings();
			if (FileExist(PATH))
				JsonFileLoader<EZClientSettings>.JsonLoadFile(PATH, s_Inst);
			if (s_Inst.SettingsVersion < 2)
			{
				if (s_Inst.TagDistance <= 15.0)
					s_Inst.TagDistance = 40.0; // upgrade old default
				s_Inst.SettingsVersion = 2;
			}
			s_Inst.Sanitize();
		}
		return s_Inst;
	}

	void Sanitize()
	{
		TagOpacity = Math.Clamp(TagOpacity, 0.2, 1.0);
		TagSize = Math.Clamp(TagSize, 12, 28);
		TagDistance = Math.Clamp(TagDistance, 2, 50);
		if (!EarplugLevels || EarplugLevels.Count() == 0)
			EarplugLevels = {100, 50, 25};
	}

	void Save()
	{
		Sanitize();
		JsonFileLoader<EZClientSettings>.JsonSaveFile(PATH, this);
	}
}

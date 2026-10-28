// EZ holographic name tags - config ($profile:EZLoderScreen/HoloTags.json, created on first server start)
class EZHoloZone
{
	string Name;
	float X;
	float Z;
	float Radius;
	void EZHoloZone(string n = "", float x = 0, float z = 0, float r = 0)
	{
		Name = n; X = x; Z = z; Radius = r;
	}
}

class EZHoloConfig
{
	int Enabled = 1;
	float MaxDistance = 40.0;          // players (green) and defender AI (blue)
	float AdminMaxDistance = 20000.0;  // admins (pink) - whole map
	string ColorAdmin = "FF4FD8";      // pink. Orange alternative: "FF8C1A"
	string ColorGuard = "3FA9FF";      // defender AI / InvincibleGuards
	string ColorPlayer = "3CFF6E";     // players inside sanctuary/PvE zones
	string ColorBandit = "FF2020";     // hostile eAI (any faction except InvincibleGuards)
	int BanditTagsEverywhere = 0;      // 0 = bandits follow zone rules (sanctuary breach alert); 1 = within MaxDistance anywhere
	int Flicker = 1;
	string GuardName = "Sanctuary Defender";
	float DefaultZoneRadius = 0;       // >0 overrides every zone radius
	int ConfigVersion = 0;             // 2 = MaxDistance default raised 15 -> 40
	ref array<string> AdminSteamIDs = new array<string>;
	ref array<ref EZHoloZone> Zones = new array<ref EZHoloZone>;

	static const string DIR = "$profile:EZLoderScreen";
	static const string PATH = "$profile:EZLoderScreen/HoloTags.json";

	void Defaults()
	{
		// Live Ninjins PvEZone sanctuaries (centre/radius from the server zone files, 2026-10-21)
		Zones.Insert(new EZHoloZone("Bam-e Sabz", 8640, 8615, 1200));
		Zones.Insert(new EZHoloZone("Gandomabad", 7700, 12515, 1000));
		Zones.Insert(new EZHoloZone("Varzaneh", 13265, 12170, 800));
		Zones.Insert(new EZHoloZone("Gard Abad", 10970, 7985, 700));
		Zones.Insert(new EZHoloZone("Kucha Dar", 4410, 10205, 900));
		Zones.Insert(new EZHoloZone("No Abad", 6710, 4855, 900));
	}

	static EZHoloConfig LoadOrCreate()
	{
		EZHoloConfig cfg = new EZHoloConfig();
		if (FileExist(PATH))
		{
			JsonFileLoader<EZHoloConfig>.JsonLoadFile(PATH, cfg);
			if (!cfg.Zones)
				cfg.Zones = new array<ref EZHoloZone>;
			if (!cfg.AdminSteamIDs)
				cfg.AdminSteamIDs = new array<string>;
			if (cfg.ConfigVersion < 2)
			{
				if (cfg.MaxDistance < 40.0)
					cfg.MaxDistance = 40.0; // upgrade old 15 m default
				cfg.ConfigVersion = 2;
				JsonFileLoader<EZHoloConfig>.JsonSaveFile(PATH, cfg);
			}
		}
		else
		{
			cfg.Defaults();
			cfg.ConfigVersion = 2;
			if (!FileExist(DIR))
				MakeDirectory(DIR);
			JsonFileLoader<EZHoloConfig>.JsonSaveFile(PATH, cfg);
		}
		return cfg;
	}

	bool InZone(vector pos)
	{
		foreach (EZHoloZone z : Zones)
		{
			float r = z.Radius;
			if (DefaultZoneRadius > 0)
				r = DefaultZoneRadius;
			float dx = pos[0] - z.X;
			float dz = pos[2] - z.Z;
			if (dx * dx + dz * dz <= r * r)
				return true;
		}
		return false;
	}

	static int HexToARGB(string hex, int alpha = 255)
	{
		hex.ToUpper();
		if (hex.IndexOf("#") == 0)
			hex = hex.Substring(1, hex.Length() - 1);
		int v = 0;
		string digits = "0123456789ABCDEF";
		for (int i = 0; i < hex.Length() && i < 6; i++)
		{
			int d = digits.IndexOf(hex.Get(i));
			if (d < 0)
				d = 0;
			v = v * 16 + d;
		}
		return (alpha << 24) | v;
	}
}

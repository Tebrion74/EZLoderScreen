// EZLoderScreen - The Big Bang Rebuild: 47 Badlands loading screens (01-27 + A01-A10 + B01-B10).
// Music by: Haunted Corpse (Free Music Archive) CC-BY-NC-ND
class EZLoadScreens
{
	static const int COUNT_OLD = 27; // EchelonZ-Badlands-01..27
	static const int COUNT = 47;     // + EchelonZ-Badlands-A01..A10, B01..B10
	static string Random()
	{
		int i = Math.RandomIntInclusive(1, COUNT);
		string pre = "";
		if (i > COUNT_OLD)
		{
			i = i - COUNT_OLD; // 1..20
			pre = "A";
			if (i > 10)
			{
				i = i - 10;
				pre = "B";
			}
		}
		string n = i.ToString();
		if (i < 10)
			n = "0" + n;
		return "EZLoderScreen\\data\\EchelonZ-Badlands-" + pre + n + ".edds";
	}
}

modded class LoadingScreen
{
	override void Show()
	{
		string preel = EZLoadScreens.Random();
		m_ImageWidgetBackground.LoadMaskTexture("EZLoderScreen/data/ls_mask.paa");
		m_ImageWidgetBackground.LoadImageFile(0, preel);
		m_ImageLogoMid.Show(false);
		m_ImageLogoCorner.Show(false);
		m_ModdedWarning.Show(false);
		super.Show();
	}
};

modded class LoginTimeBase extends UIScriptedMenu
{
	override void Show()
	{
		super.Show();
		if (layoutRoot)
		{
			ImageWidget background = ImageWidget.Cast(layoutRoot.FindAnyWidget("Background"));
			if (background)
				background.LoadImageFile(0, EZLoadScreens.Random());
		}
	}
};

modded class LoginQueueBase extends UIScriptedMenu
{
	override void Show()
	{
		super.Show();
		if (layoutRoot)
		{
			ImageWidget background = ImageWidget.Cast(layoutRoot.FindAnyWidget("Background"));
			if (background)
				background.LoadImageFile(0, EZLoadScreens.Random());
		}
	}
};

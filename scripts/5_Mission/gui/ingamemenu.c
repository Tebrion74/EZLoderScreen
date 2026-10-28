// EZLoderScreen - in-game (Esc) menu logo.
// 9.7: logo found by widget name ("dayz_logo", used by vanilla day_z_ingamemenu.layout
// and by Expansion's InGameMenu) instead of "first ImageWidget in the tree".
// Re-applied on OnShow because Expansion reloads its logo when its settings sync.
modded class InGameMenu
{
	static const string EZ_INGAME_LOGO = "EZLoderScreen/data/ez_logo_mainmenu.paa";

	override Widget Init()
	{
		layoutRoot = super.Init();
		EZ_ApplyLogo();
		return layoutRoot;
	}

	override void OnShow()
	{
		super.OnShow();
		EZ_ApplyLogo();
	}

	protected void EZ_ApplyLogo()
	{
		if (!layoutRoot)
			return;
		ImageWidget logo = ImageWidget.Cast(layoutRoot.FindAnyWidget("dayz_logo"));
		if (!logo)
			return;
		logo.LoadImageFile(0, EZ_INGAME_LOGO);
		logo.SetImage(0);
	}
}

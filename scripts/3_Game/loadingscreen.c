modded class LoadingScreen
{
	ref TStringArray RandomLoadingScreenArray = {
		"EZLoderScreen\\data\\EchelonZ-1.edds",
		"EZLoderScreen\\data\\EchelonZ-2.edds",
		"EZLoderScreen\\data\\EchelonZ-3.edds",
		"EZLoderScreen\\data\\EchelonZ-4.edds",
		"EZLoderScreen\\data\\EchelonZ-5.edds",
		"EZLoderScreen\\data\\EchelonZ-6.edds"

        };
		
	override void Show()
	{		
		string preel = RandomLoadingScreenArray.GetRandomElement();
		m_ImageWidgetBackground.LoadMaskTexture("EZLoderScreen/data/ls_mask.paa");
		m_ImageWidgetBackground.LoadImageFile(0, preel);   
        m_ImageLogoMid.Show(false);
		m_ImageLogoCorner.Show(false);	    	
		m_ModdedWarning.Show(false); // Show / Hide - Modded version warning // 1.17 OK
		super.Show();
	}
};


modded class LoginTimeBase extends UIScriptedMenu
{
	ref TStringArray RandomLoadingScreenArray = {
		"EZLoderScreen\\data\\EchelonZ-1.edds",
		"EZLoderScreen\\data\\EchelonZ-2.edds",
		"EZLoderScreen\\data\\EchelonZ-3.edds",
		"EZLoderScreen\\data\\EchelonZ-4.edds",
		"EZLoderScreen\\data\\EchelonZ-5.edds",
		"EZLoderScreen\\data\\EchelonZ-6.edds"
        };

    override void Show()
    {
        super.Show();
        if (layoutRoot)
        {
            string preel = RandomLoadingScreenArray.GetRandomElement();
            ImageWidget background = ImageWidget.Cast( layoutRoot.FindAnyWidget("Background"));
            background.LoadImageFile(0, preel);  
        }
    }
};


modded class LoginQueueBase extends UIScriptedMenu
{
	ref TStringArray RandomLoadingScreenArray = {
		"EZLoderScreen\\data\\EchelonZ-1.edds",
		"EZLoderScreen\\data\\EchelonZ-2.edds",
		"EZLoderScreen\\data\\EchelonZ-3.edds",
		"EZLoderScreen\\data\\EchelonZ-4.edds",
		"EZLoderScreen\\data\\EchelonZ-5.edds",
		"EZLoderScreen\\data\\EchelonZ-6.edds"
        };

    override void Show()
    {
        super.Show();
        if (layoutRoot)
        {
            string preel = RandomLoadingScreenArray.GetRandomElement();
            ImageWidget background = ImageWidget.Cast( layoutRoot.FindAnyWidget("Background"));
            background.LoadImageFile(0, preel);  
        }
    }
};

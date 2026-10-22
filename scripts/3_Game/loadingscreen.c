modded class LoadingScreen
{
	ref TStringArray RandomLoadingScreenArray = {
		"EZLoderScreen\\data\\EchelonZ-Badlands-01.edds",
		"EZLoderScreen\\data\\EchelonZ-Badlands-02.edds",
		"EZLoderScreen\\data\\EchelonZ-Badlands-03.edds",
		"EZLoderScreen\\data\\EchelonZ-Badlands-04.edds",
		"EZLoderScreen\\data\\EchelonZ-Badlands-05.edds",
		"EZLoderScreen\\data\\EchelonZ-Badlands-06.edds",
		"EZLoderScreen\\data\\EchelonZ-Badlands-07.edds",
		"EZLoderScreen\\data\\EchelonZ-Badlands-08.edds",
		"EZLoderScreen\\data\\EchelonZ-Badlands-09.edds",
		"EZLoderScreen\\data\\EchelonZ-Badlands-10.edds"
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
		"EZLoderScreen\\data\\EchelonZ-Badlands-01.edds",
		"EZLoderScreen\\data\\EchelonZ-Badlands-02.edds",
		"EZLoderScreen\\data\\EchelonZ-Badlands-03.edds",
		"EZLoderScreen\\data\\EchelonZ-Badlands-04.edds",
		"EZLoderScreen\\data\\EchelonZ-Badlands-05.edds",
		"EZLoderScreen\\data\\EchelonZ-Badlands-06.edds",
		"EZLoderScreen\\data\\EchelonZ-Badlands-07.edds",
		"EZLoderScreen\\data\\EchelonZ-Badlands-08.edds",
		"EZLoderScreen\\data\\EchelonZ-Badlands-09.edds",
		"EZLoderScreen\\data\\EchelonZ-Badlands-10.edds"
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
		"EZLoderScreen\\data\\EchelonZ-Badlands-01.edds",
		"EZLoderScreen\\data\\EchelonZ-Badlands-02.edds",
		"EZLoderScreen\\data\\EchelonZ-Badlands-03.edds",
		"EZLoderScreen\\data\\EchelonZ-Badlands-04.edds",
		"EZLoderScreen\\data\\EchelonZ-Badlands-05.edds",
		"EZLoderScreen\\data\\EchelonZ-Badlands-06.edds",
		"EZLoderScreen\\data\\EchelonZ-Badlands-07.edds",
		"EZLoderScreen\\data\\EchelonZ-Badlands-08.edds",
		"EZLoderScreen\\data\\EchelonZ-Badlands-09.edds",
		"EZLoderScreen\\data\\EchelonZ-Badlands-10.edds"
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

class CfgPatches
{
	class EZLoderScreen
	{
       // units[] = {
       //     "TShirt_Blank",
       //     "EZ_Tshirt_Dark"
       // };
        weapons[] = {};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Data",
            "DZ_Characters",
            "DZ_Characters_Tops",
            "DZ_Characters_Headgear"
		};
	};
};
class CfgMods
{
	class EZLoderScreen
	{
		dir="EZLoderScreen";
		picture="";
		action="";
		hideName=1;
		hidePicture=1;
		name="EZLoderScreen";
		credits="The DayZ Community";
		author="JosieG and LordSausageFinger";
		authorID="0";
		version="3";
		extra=0;
		type="mod";
		dependencies[]=
		{
			"Game",
			"Mission"
		};
		class defs
		{
			class gameScriptModule
			{
				value="";
				files[] = {"EZLoderScreen/scripts/3_Game"};
			};
			class missionScriptModule
			{
				value = "";
				files[] = {"EZLoderScreen/scripts/5_Mission"};
			};
		};
	};
};

class CfgSoundSets
{
	class Josies_Menu_SoundSet // do not change anything in this
	{
		soundShaders[] = {"Josies_Menu_Shader"};
		volumeFactor = 1;
		frequencyFactor = 1;
		spatial = 0;
	};
};
class CfgSoundShaders
{
	class Josies_Menu_Shader
	{
		samples[] = {
					 {"\EZLoderScreen\OGG\Rot.ogg",1},
					 {"\EZLoderScreen\OGG\Poe.ogg",2},
					 {"\EZLoderScreen\OGG\Boogie.ogg",3},
                     {"\EZLoderScreen\OGG\Crypt.ogg",4},
					 {"\EZLoderScreen\OGG\Creep.ogg",5},
					 {"\EZLoderScreen\OGG\Morgue.ogg",6}
					}; 
		volume = 0.8;  // volume of your music
	};
};
class cfgCharacterScenes
{
    class ChernarusPlus
    {
        class loc1
        {
            target[] = {9934.76,1653.95,6}; // Position of character
            position[] = {9909.98,1619.83,0.8}; // Position of camera
            fov = 0.65; // Zoom of scene on character
            date[] = {2017/10/11/05/59}; // The time/date of scene (year, month, day, hour, minute)
            overcast = 0.3; // The overcast for the scene
            rain = 0.0; // The amount of rain in scene
            fog = 0.8; // The amount of fog in scene
            wind = 0.2;
        };
        class loc2
        {
            target[] = {2523.55,1217.29,6};
            position[] = {2495.36,1214.35,0.8};
            fov = 0.65;
            date[] = {2017/10/11/05/59};
            overcast = 0.7;
            rain = 1;
            fog = 0.3;
            wind = 0.4;
        };
        class loc3
        {
            target[] = {4419.82,5649.22,321.694};
            position[] = {4424.01,5647.31,0.8};
            fov = 0.65;
            date[] = {2017/10/11/05/59};
            overcast = 0.2;
            rain = 0.3;
            fog = 0.2;
            wind = 0.1;
        };
        class loc4
        {
            target[] = {10625.2,2657.75,32.7498};
            position[] = {10626.5,2662.08,0.8};
            fov = 0.65;
            date[] = {2017/10/11/05/59};
            overcast = 0.4;
            rain = 0.6;
            fog = 0.5;
            wind = 0.2;
        };
    };
};
class CfgMissions
{
    class Cutscenes
    {
        class TESTcutscene
        {
            directory = "EZLoderScreen\intro.something";
        };
    };
};
class CfgWorlds
{
    class EZLoderScreen
    {
        cutscenes[] = {"TESTcutscene"};
    };    
};
class CfgVehicles
{
	class TShirt_ColorBase;

	class EZ_Tshirt_Dark:TShirt_ColorBase
	{
		scope = 2;
		displayName = "EZ TEE";
		descriptionShort = "EZ Tees by LordSausageFinger";
		weight = 32;
		itemSize[] = {1,1};
		itemsCargoSize[] = {10,10};
		quickBarBonus = 6;
		ragQuantity = 12;
		varWetMax = 0;
		repairCosts[] = {25,25};
		hiddenSelectionsTextures[] =
        {
            "EZLoderScreen\data\tshirt_EZ_Dark_co.paa",
            "EZLoderScreen\data\tshirt_EZ_Dark_co.paa",
            "EZLoderScreen\data\tshirt_EZ_Dark_co.paa"
        };
	};
   	class BaseballCap_ColorBase;

	class EZ_Cap_Dark: BaseballCap_ColorBase
	{
		scope = 2;
        displayName = "EZ Cap";
		descriptionShort = "EZ Wear by LordSausageFinger";
		weight = 32;
		itemSize[] = {1,1};
		hiddenSelectionsTextures[]=
		{
			"EZLoderScreen\data\EZCap_JeanDark_co.paa",
			"EZLoderScreen\data\EZCap_JeanDark_co.paa",
			"EZLoderScreen\data\EZCap_JeanDark_co.paa"
		};
	};


};

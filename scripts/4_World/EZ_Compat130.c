// EZ_Compat130.c - DayZ 1.30 compatibility shim.
// CarScript.ToggleHeadlights() was removed in 1.30; light state is native on Transport now
// (LightIsOn / LightOn / LightOff). Older car mods still call/override it.
modded class CarScript
{
	void ToggleHeadlights()
	{
		if (LightIsOn())
			LightOff();
		else
			LightOn();
	}
}

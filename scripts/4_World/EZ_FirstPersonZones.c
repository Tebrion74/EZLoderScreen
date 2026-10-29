// EZ First Person Zones: forces first-person view on foot everywhere except inside the six Nasdara sanctuaries.
// Only the vehicle DRIVER keeps the 3PP toggle everywhere; passengers follow on-foot rules.
// Matches Ninjin's PvPPvE ThirdPersonOnlyDriver=1.
// Zones hardcoded from NinjinsPvPPvE/Config/zones/PVE/*Sanctuary.json (all shape 0 = circle, X/Z only, height ignored).
class EZ_FirstPersonZones
{
	static bool InCircle(vector pos, float cx, float cz, float r)
	{
		float dx = pos[0] - cx;
		float dz = pos[2] - cz;
		float d2 = dx * dx + dz * dz;
		return d2 <= r * r;
	}

	static bool IsInSanctuary(vector pos)
	{
		if (InCircle(pos, 4410.0, 10205.0, 900.0))   // Kucha Dar
			return true;
		if (InCircle(pos, 10970.0, 7985.0, 700.0))   // Gard Abad
			return true;
		if (InCircle(pos, 8640.0, 8615.0, 1200.0))   // Bam-e Sabz
			return true;
		if (InCircle(pos, 6710.0, 4855.0, 900.0))    // No Abad
			return true;
		if (InCircle(pos, 7700.0, 12515.0, 1000.0))  // Gandomabad
			return true;
		if (InCircle(pos, 13265.0, 12170.0, 800.0))  // Varzaneh
			return true;
		return false;
	}
}

modded class DayZPlayerImplement
{
	// Same driver test vanilla uses for the horn (ActionCarHorn): seat animation type of my crew index.
	bool EZ_IsDriver()
	{
		Transport trans = null;
		HumanCommandVehicle hcv = GetCommand_Vehicle();
		if (hcv)
			trans = hcv.GetTransport();
		if (!trans)
			trans = Transport.Cast(GetParent());
		if (!trans)
			return false;
		int seat = trans.CrewMemberIndex(this);
		if (seat < 0)
			return false;
		return trans.GetSeatAnimationType(seat) == DayZPlayerConstants.VEHICLESEAT_DRIVER;
	}

	override int CameraHandler(int pCameraMode)
	{
		if (GetInstanceType() == DayZPlayerInstanceType.INSTANCETYPE_CLIENT)
		{
			if (!EZ_IsDriver())
			{
				if (!EZ_FirstPersonZones.IsInSanctuary(GetPosition()))
				{
					m_Camera3rdPerson = false;
				}
			}
		}
		return super.CameraHandler(pCameraMode);
	}
}

// EZ WheelFix - overrides wheel inventorySlot[] only; source PBOs untouched.
// GT2RS spare is now Rear-class only (Front no longer fits it); Enzo spare is rear-class only (Star_Enzo_Wheel family).
// Vanilla Hatchback_02/Sedan_02 slots dropped from these wheels.
class CfgPatches
{
	class EZ_WheelFix
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]={"Star_Enzo","GT2RS_MR"};
	};
};
class CfgVehicles
{
	class CarWheel;
	class GT2RS_MRWheel_offroad_Front: CarWheel
	{
		inventorySlot[]={"GT2RS_MRWheel_offroad_1_1","GT2RS_MRWheel_offroad_2_1"};
	};
	class GT2RS_MRWheel_offroad_Front_destroyed: GT2RS_MRWheel_offroad_Front
	{
		inventorySlot[]={"GT2RS_MRWheel_offroad_1_1","GT2RS_MRWheel_offroad_2_1"};
	};
	class GT2RS_MRWheel_offroad_Rear: GT2RS_MRWheel_offroad_Front
	{
		inventorySlot[]={"GT2RS_MRWheel_offroad_1_2","GT2RS_MRWheel_offroad_2_2","GT2RS_MRWheel_offroad_spare_1"};
	};
	class GT2RS_MRWheel_offroad_Rear_destroyed: GT2RS_MRWheel_offroad_Rear
	{
		inventorySlot[]={"GT2RS_MRWheel_offroad_1_2","GT2RS_MRWheel_offroad_2_2","GT2RS_MRWheel_offroad_spare_1"};
	};
	class Star_Enzo_Wheel: CarWheel
	{
		inventorySlot[]={"Star_Enzo_Wheel_1_2","Star_Enzo_Wheel_2_2","Star_Enzo_Wheel_spare_1"};
	};
	class Star_Enzo_Wheel1: CarWheel
	{
		inventorySlot[]={"Star_Enzo_Wheel_1_1","Star_Enzo_Wheel_2_1"};
	};
	class Star_Enzo_wheel1_Blue: Star_Enzo_Wheel1
	{
		inventorySlot[]={"Star_Enzo_Wheel_1_1","Star_Enzo_Wheel_2_1"};
	};
	class Star_Enzo_wheel_Blue: Star_Enzo_Wheel
	{
		inventorySlot[]={"Star_Enzo_Wheel_1_2","Star_Enzo_Wheel_2_2","Star_Enzo_Wheel_spare_1"};
	};
	class Star_Enzo_wheel1_Red: Star_Enzo_Wheel1
	{
		inventorySlot[]={"Star_Enzo_Wheel_1_1","Star_Enzo_Wheel_2_1"};
	};
	class Star_Enzo_wheel_Red: Star_Enzo_Wheel
	{
		inventorySlot[]={"Star_Enzo_Wheel_1_2","Star_Enzo_Wheel_2_2","Star_Enzo_Wheel_spare_1"};
	};
	class Star_Enzo_wheel1_yellow: Star_Enzo_Wheel1
	{
		inventorySlot[]={"Star_Enzo_Wheel_1_1","Star_Enzo_Wheel_2_1"};
	};
	class Star_Enzo_wheel_yellow: Star_Enzo_Wheel
	{
		inventorySlot[]={"Star_Enzo_Wheel_1_2","Star_Enzo_Wheel_2_2","Star_Enzo_Wheel_spare_1"};
	};
	class Star_Enzo_wheel1_white: Star_Enzo_Wheel1
	{
		inventorySlot[]={"Star_Enzo_Wheel_1_1","Star_Enzo_Wheel_2_1"};
	};
	class Star_Enzo_wheel_white: Star_Enzo_Wheel
	{
		inventorySlot[]={"Star_Enzo_Wheel_1_2","Star_Enzo_Wheel_2_2","Star_Enzo_Wheel_spare_1"};
	};
	class Star_Enzo_wheel1_pink: Star_Enzo_Wheel1
	{
		inventorySlot[]={"Star_Enzo_Wheel_1_1","Star_Enzo_Wheel_2_1"};
	};
	class Star_Enzo_wheel_pink: Star_Enzo_Wheel
	{
		inventorySlot[]={"Star_Enzo_Wheel_1_2","Star_Enzo_Wheel_2_2","Star_Enzo_Wheel_spare_1"};
	};
	class Star_Enzo_wheel1_orange: Star_Enzo_Wheel1
	{
		inventorySlot[]={"Star_Enzo_Wheel_1_1","Star_Enzo_Wheel_2_1"};
	};
	class Star_Enzo_wheel_orange: Star_Enzo_Wheel
	{
		inventorySlot[]={"Star_Enzo_Wheel_1_2","Star_Enzo_Wheel_2_2","Star_Enzo_Wheel_spare_1"};
	};
	class Star_Enzo_Wheel_destroyed: Star_Enzo_Wheel
	{
		inventorySlot[]={"Star_Enzo_Wheel_1_2","Star_Enzo_Wheel_2_2","Star_Enzo_Wheel_spare_1"};
	};
	class Star_Enzo_Wheel1_destroyed: Star_Enzo_Wheel1
	{
		inventorySlot[]={"Star_Enzo_Wheel_1_1","Star_Enzo_Wheel_2_1"};
	};
};

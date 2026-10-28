// EZ Ammo Stacks - replaces BulletStacksPlusPlusEnhanced (old mod: flat count=100).
// Only changes max stack size (count) on loose ammo. Vanilla DayZ 1.29 + Mortys Weapons (TTC_*).
// Mortys CfgPatches names verified from @Mortys Weapons/Addons/TTC_*.pbo configs.
class CfgPatches
{
    class EZLoderScreen_AmmoStacks
    {
        units[] = {};
        weapons[] = {};
        requiredVersion = 0.1;
        requiredAddons[] =
        {
            "DZ_Data",
            "DZ_Weapons_Ammunition",
            // Mortys Weapons (TTC)
            "TTC_Deagle", "TTC_44Magnum", "TTC_MP7A1", "TTC_MCX", "TTC_MP44",
            "TTCAmmo3006", "TTCAmmo300blk", "TTCAmmo303", "TTCAmmo338",
            "TTCAmmo4570", "TTC_Ammo50BMG", "TTCAmmo50Beo", "TTCAmmo8mm"
        };
    };
};

class CfgMagazines
{
    class Ammunition_Base;

    // ---- Vanilla pistol / small calibre: 100
    class Ammo_22: Ammunition_Base { count = 100; };
    class Ammo_380: Ammunition_Base { count = 100; };
    class Ammo_9x19: Ammunition_Base { count = 100; };
    class Ammo_45ACP: Ammunition_Base { count = 100; };
    class Ammo_357: Ammunition_Base { count = 100; };

    // ---- Vanilla rifle: 60
    class Ammo_545x39: Ammunition_Base { count = 60; };
    class Ammo_545x39Tracer: Ammunition_Base { count = 60; };
    class Ammo_556x45: Ammunition_Base { count = 60; };
    class Ammo_556x45Tracer: Ammunition_Base { count = 60; };
    class Ammo_762x39: Ammunition_Base { count = 60; };
    class Ammo_762x39Tracer: Ammunition_Base { count = 60; };
    class Ammo_762x54: Ammunition_Base { count = 60; };
    class Ammo_762x54Tracer: Ammunition_Base { count = 60; };
    class Ammo_308Win: Ammunition_Base { count = 60; };
    class Ammo_308WinTracer: Ammunition_Base { count = 60; };
    class Ammo_9x39: Ammunition_Base { count = 60; };
    class Ammo_9x39AP: Ammunition_Base { count = 60; };

    // ---- Vanilla shotgun: 40
    class Ammo_12gaPellets: Ammunition_Base { count = 40; };
    class Ammo_12gaSlug: Ammunition_Base { count = 40; };
    class Ammo_12gaRubberSlug: Ammunition_Base { count = 40; };
    class Ammo_12gaBeanbag: Ammunition_Base { count = 40; };

    // ---- Vanilla flares: 10 (Red/Green/Blue inherit from Ammo_Flare)
    class Ammo_Flare: Ammunition_Base { count = 10; };

    // ---- Mortys Weapons pistol / PDW
    class TTC_Ammo_44Mag: Ammunition_Base { count = 60; };
    class TTC_Ammo_50AE: Ammunition_Base { count = 60; };
    class TTC_Ammo_4630: Ammunition_Base { count = 100; };

    // ---- Mortys Weapons rifle: 60
    class TTC_Ammo_277: Ammunition_Base { count = 60; };
    class TTC_Ammo_300blk: Ammunition_Base { count = 60; };
    class TTC_Ammo_792x33: Ammunition_Base { count = 60; };
    class TTC_Ammo_3006: Ammunition_Base { count = 60; };
    class TTC_Ammo_303: Ammunition_Base { count = 60; };
    class TTC_Ammo_8mm: Ammunition_Base { count = 60; };
    class TTC_Ammo_4570: Ammunition_Base { count = 60; };
    class TTC_Ammo_50Beo: Ammunition_Base { count = 60; };

    // ---- Mortys Weapons big / rare
    class TTC_Ammo_338: Ammunition_Base { count = 30; };
    class TTC_Ammo_50BMG: Ammunition_Base { count = 20; };
};

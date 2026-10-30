class CfgPatches {
    class EZLoderScreen {
        units[] = {"EZ_PineappleSeeds", "EZ_PineappleSeedsPack", "EZ_Pineapple", "EZ_PineappleSlice", "EZ_TerjeMedManual", "EZ_Kameez", "EZ_BallisticHelmet", "EZ_Mich2001Helmet", "EZ_GorkaHelmet", "EZ_PlateCarrierVest", "EZ_PlateCarrierHolster", "EZ_SmershVest", "EZ_TacticalGloves", "EZ_MilitaryBelt", "EZ_Balaclava3Holes", "EZ_TacticalShirt", "EZ_BDUPants"};
        weapons[] = {};
        requiredVersion = 0.1;
        requiredAddons[] = {"DZ_Data", "DZ_Characters", "DZ_Characters_Tops", "DZ_Characters_Headgear", "DZ_Characters_Vests", "DZ_Characters_Gloves", "DZ_Characters_Belts", "DZ_Characters_Masks", "DZ_Characters_Pants", "DZ_Characters_Nasdara_Headgear", /* TODO verify in DayZ Tools: add the Nasdara tops CfgPatches name here if KameezShirt_ColorBase is not in DZ_Characters_Tops */ "DZ_Scripts", "DZ_Sounds_Effects", "DZ_Gear_Food", "DZ_Gear_Cultivation", "DZ_Gear_Books", "DayZExpansion_Chat_Scripts", "DayZExpansion_Chat_GUI"};
    };
};
class CfgMods {
    class EZLoderScreen {
        dir = "EZLoderScreen";
        picture = "";
        action = "";
        hideName = 1;
        hidePicture = 1;
        name = "EZLoderScreen";
        credits = "JosieG, LordSausageFinger; CarPack by Starxick & camper10112; Music by: Haunted Corpse (Free Music Archive) CC-BY-NC-ND";
        author = "JosieG and LordSausageFinger";
        authorID = "0";
        version = "9.9";
        inputs = "EZLoderScreen/data/inputs.xml";
        extra = 0;
        type = "mod";
        dependencies[] = {"Game", "World", "Mission"};
        class defs {
            class gameScriptModule {
                value = "";
                files[] = {"EZLoderScreen/scripts/3_Game"};
            };
            class worldScriptModule {
                value = "";
                files[] = {"EZLoderScreen/scripts/4_World"};
            };
            class missionScriptModule {
                value = "";
                files[] = {"EZLoderScreen/scripts/5_Mission"};
            };
        };
    };
};
class CfgSoundShaders {
    class EZ_Menu_Base_SoundShader {
        volume = 0.8;
        range = 10000;
    };
    class EZ_Menu_Rot_SoundShader: EZ_Menu_Base_SoundShader {
        samples[] = {{"EZLoderScreen\OGG\Rot", 1}};
    };
    class EZ_Menu_Poe_SoundShader: EZ_Menu_Base_SoundShader {
        samples[] = {{"EZLoderScreen\OGG\Poe", 1}};
    };
    class EZ_Menu_Boogie_SoundShader: EZ_Menu_Base_SoundShader {
        samples[] = {{"EZLoderScreen\OGG\Boogie", 1}};
    };
    class EZ_Menu_Crypt_SoundShader: EZ_Menu_Base_SoundShader {
        samples[] = {{"EZLoderScreen\OGG\Crypt", 1}};
    };
    class EZ_Menu_Creep_SoundShader: EZ_Menu_Base_SoundShader {
        samples[] = {{"EZLoderScreen\OGG\Creep", 1}};
    };
    class EZ_Menu_Morgue_SoundShader: EZ_Menu_Base_SoundShader {
        samples[] = {{"EZLoderScreen\OGG\Morgue", 1}};
    };
};
class CfgSoundSets {
    class EZ_Menu_Base_SoundSet {
        spatial = 0;
        loop = 0;
        doppler = 0;
        volumeFactor = 1;
        frequencyFactor = 1;
    };
    class EZ_Menu_Rot_SoundSet: EZ_Menu_Base_SoundSet {
        soundShaders[] = {"EZ_Menu_Rot_SoundShader"};
    };
    class EZ_Menu_Poe_SoundSet: EZ_Menu_Base_SoundSet {
        soundShaders[] = {"EZ_Menu_Poe_SoundShader"};
    };
    class EZ_Menu_Boogie_SoundSet: EZ_Menu_Base_SoundSet {
        soundShaders[] = {"EZ_Menu_Boogie_SoundShader"};
    };
    class EZ_Menu_Crypt_SoundSet: EZ_Menu_Base_SoundSet {
        soundShaders[] = {"EZ_Menu_Crypt_SoundShader"};
    };
    class EZ_Menu_Creep_SoundSet: EZ_Menu_Base_SoundSet {
        soundShaders[] = {"EZ_Menu_Creep_SoundShader"};
    };
    class EZ_Menu_Morgue_SoundSet: EZ_Menu_Base_SoundSet {
        soundShaders[] = {"EZ_Menu_Morgue_SoundShader"};
    };
};
class cfgCharacterScenes {
    class ChernarusPlus {
        class loc1 {
            target[] = {9934.76, 1653.95, 6};
            position[] = {9909.98, 1619.83, 0.8};
            fov = 0.65;
            date[] = {"2017/10/11/05/59"};
            overcast = 0.3;
            rain = 0;
            fog = 0.8;
            wind = 0.2;
        };
        class loc2 {
            target[] = {2523.55, 1217.29, 6};
            position[] = {2495.36, 1214.35, 0.8};
            fov = 0.65;
            date[] = {"2017/10/11/05/59"};
            overcast = 0.7;
            rain = 1;
            fog = 0.3;
            wind = 0.4;
        };
        class loc3 {
            target[] = {4419.82, 5649.22, 321.694};
            position[] = {4424.01, 5647.31, 0.8};
            fov = 0.65;
            date[] = {"2017/10/11/05/59"};
            overcast = 0.2;
            rain = 0.3;
            fog = 0.2;
            wind = 0.1;
        };
        class loc4 {
            target[] = {10625.2, 2657.75, 32.7498};
            position[] = {10626.5, 2662.08, 0.8};
            fov = 0.65;
            date[] = {"2017/10/11/05/59"};
            overcast = 0.4;
            rain = 0.6;
            fog = 0.5;
            wind = 0.2;
        };
    };
};
class CfgMissions {
    class Cutscenes {
        class TESTcutscene {
            directory = "EZLoderScreen\intro.something";
        };
    };
};
class CfgWorlds {
    class EZLoderScreen {
        cutscenes[] = {"TESTcutscene"};
    };
};
class FruitStageTransitions;
class FoodAnimationSources;
class CfgVehicles {
    class TShirt_ColorBase;
    class EZ_Tshirt_Dark: TShirt_ColorBase {
        scope = 2;
        displayName = "EZ TEE";
        descriptionShort = "EZ Tees by LordSausageFinger";
        weight = 32;
        itemSize[] = {1, 1};
        itemsCargoSize[] = {10, 10};
        quickBarBonus = 6;
        ragQuantity = 12;
        varWetMax = 0;
        repairCosts[] = {25, 25};
        hiddenSelectionsTextures[] = {"EZLoderScreen\data\tshirt_EZ_Dark_co.paa", "EZLoderScreen\data\tshirt_EZ_Dark_co.paa", "EZLoderScreen\data\tshirt_EZ_Dark_co.paa"};
    };
    // 9.9: EZ_Kameez replaces EZ_Tshirt_Dark (tee kept defined for one wipe so stashed tees do not error).
    class KameezShirt_ColorBase;
    class EZ_Kameez: KameezShirt_ColorBase {
        scope = 2;
        displayName = "EZ Kameez";
        descriptionShort = "EZ Wear by LordSausageFinger. Knee-length, never wet, pockets for days.";
        weight = 32;
        itemSize[] = {1, 1};
        itemsCargoSize[] = {10, 12};
        quickBarBonus = 6;
        ragQuantity = 12;
        varWetMax = 0;
        repairCosts[] = {25, 25};
        // order assumed camoGround, camoMale, camoFemale (same as vanilla _ColorBase tops) - verify
        hiddenSelectionsTextures[] = {"EZLoderScreen\data\kameez_EZ_Dark_g_co.paa", "EZLoderScreen\data\kameez_EZ_Dark_co.paa", "EZLoderScreen\data\kameez_EZ_Dark_co.paa"};
    };
    // 9.9: EZ tactical wave 1 (helmets). Texture-only reskins; armour/cargo stay vanilla. Logo UV placement unverified in-game.
    class BallisticHelmet_ColorBase;
    class EZ_BallisticHelmet: BallisticHelmet_ColorBase {
        scope = 2;
        displayName = "EZ Ballistic Helmet";
        descriptionShort = "EZ Wear by LordSausageFinger. Dark shell, same vanilla protection.";
        // base material = HelmetMich.rvmat (Green/Black/UN set), inherited from ColorBase
        hiddenSelectionsTextures[] = {"EZLoderScreen\data\ez_ballistichelmet_co.paa", "EZLoderScreen\data\ez_ballistichelmet_co.paa", "EZLoderScreen\data\ez_ballistichelmet_co.paa"};
    };
    class Mich2001Helmet;
    class EZ_Mich2001Helmet: Mich2001Helmet {
        scope = 2;
        displayName = "EZ MICH 2001 Helmet";
        descriptionShort = "EZ Wear by LordSausageFinger. Rails stay vanilla (separate material).";
        hiddenSelectionsTextures[] = {"EZLoderScreen\data\ez_mich2001helmet_co.paa", "EZLoderScreen\data\ez_mich2001helmet_co.paa", "EZLoderScreen\data\ez_mich2001helmet_co.paa"};
    };
    class GorkaHelmet;
    class EZ_GorkaHelmet: GorkaHelmet {
        scope = 2;
        displayName = "EZ Gorka Helmet";
        descriptionShort = "EZ Wear by LordSausageFinger. Visor glass stays vanilla.";
        hiddenSelectionsTextures[] = {"EZLoderScreen\data\ez_gorkahelmet_co.paa", "EZLoderScreen\data\ez_gorkahelmet_co.paa", "EZLoderScreen\data\ez_gorkahelmet_co.paa"};
    };
    // 9.9: EZ tactical wave 2 (vests/gloves/belt/mask/shirt/pants). Texture-only reskins built from the REAL vanilla _co
    // (tools/make_gear.py). Bases/selections verified against vanilla config.bin (debinarized). Armour/cargo stay vanilla.
    class PlateCarrierVest_Black;
    class PlateCarrierHolster_Black;
    class SmershVest;
    class TacticalGloves_Black;
    class MilitaryBelt;
    class Balaclava3Holes_Black;
    class TacticalShirt_Black;
    class BDUPants;
    class EZ_PlateCarrierVest: PlateCarrierVest_Black {
        scope = 2;
        displayName = "EZ Plate Carrier";
        descriptionShort = "EZ Wear by LordSausageFinger. Dark finish, same vanilla protection.";
        // selections camoGround/Male/Female live on the colour leaves, not on PlateCarrierVest itself
        hiddenSelectionsTextures[] = {"EZLoderScreen\\data\\ez_platecarrier_co.paa", "EZLoderScreen\\data\\ez_platecarrier_co.paa", "EZLoderScreen\\data\\ez_platecarrier_co.paa"};
    };
    class EZ_PlateCarrierHolster: PlateCarrierHolster_Black {
        scope = 2;
        displayName = "EZ Plate Carrier Holster";
        descriptionShort = "EZ Wear by LordSausageFinger. Matches the EZ plate carrier.";
        // vanilla: hiddenSelections[] = {"camoGround"} only (3 textures listed, like vanilla)
        hiddenSelectionsTextures[] = {"EZLoderScreen\\data\\ez_platecarrier_co.paa", "EZLoderScreen\\data\\ez_platecarrier_co.paa", "EZLoderScreen\\data\\ez_platecarrier_co.paa"};
    };
    class EZ_SmershVest: SmershVest {
        scope = 2;
        displayName = "EZ Smersh Vest";
        descriptionShort = "EZ Wear by LordSausageFinger. Dark finish, same vanilla cargo.";
        hiddenSelectionsTextures[] = {"EZLoderScreen\\data\\ez_smersh_g_co.paa", "EZLoderScreen\\data\\ez_smersh_co.paa", "EZLoderScreen\\data\\ez_smersh_co.paa"};
    };
    class EZ_TacticalGloves: TacticalGloves_Black {
        scope = 2;
        displayName = "EZ Tactical Gloves";
        descriptionShort = "EZ Wear by LordSausageFinger. Dark finish.";
        // 4th selection "personality" left vanilla, as on TacticalGloves_Black
        hiddenSelectionsTextures[] = {"EZLoderScreen\\data\\ez_tacticalgloves_co.paa", "EZLoderScreen\\data\\ez_tacticalgloves_co.paa", "EZLoderScreen\\data\\ez_tacticalgloves_co.paa"};
    };
    class EZ_MilitaryBelt: MilitaryBelt {
        scope = 2;
        displayName = "EZ Military Belt";
        descriptionShort = "EZ Wear by LordSausageFinger. Dark webbing.";
        // TODO verify in-game: vanilla uses a procedural colour here; this _co is built on mil_belt_ca.paa (the rvmat texture)
        hiddenSelectionsTextures[] = {"EZLoderScreen\\data\\ez_militarybelt_co.paa", "EZLoderScreen\\data\\ez_militarybelt_co.paa", "EZLoderScreen\\data\\ez_militarybelt_co.paa"};
    };
    class EZ_Balaclava3Holes: Balaclava3Holes_Black {
        scope = 2;
        displayName = "EZ Balaclava";
        descriptionShort = "EZ Wear by LordSausageFinger. Dark knit.";
        hiddenSelectionsTextures[] = {"EZLoderScreen\\data\\ez_balaclava3holes_co.paa", "EZLoderScreen\\data\\ez_balaclava3holes_co.paa", "EZLoderScreen\\data\\ez_balaclava3holes_co.paa"};
    };
    class EZ_TacticalShirt: TacticalShirt_Black {
        scope = 2;
        displayName = "EZ Tactical Shirt";
        descriptionShort = "EZ Wear by LordSausageFinger. Dark finish, same vanilla cargo.";
        hiddenSelectionsTextures[] = {"EZLoderScreen\\data\\ez_tacticalshirt_ground_co.paa", "EZLoderScreen\\data\\ez_tacticalshirt_co.paa", "EZLoderScreen\\data\\ez_tacticalshirt_co.paa"};
    };
    class EZ_BDUPants: BDUPants {
        scope = 2;
        displayName = "EZ BDU Pants";
        descriptionShort = "EZ Wear by LordSausageFinger. Dark woodland, same vanilla cargo.";
        hiddenSelectionsTextures[] = {"EZLoderScreen\\data\\ez_bdupants_co.paa", "EZLoderScreen\\data\\ez_bdupants_co.paa", "EZLoderScreen\\data\\ez_bdupants_co.paa"};
    };
    class BaseballCap_ColorBase;
    class EZ_Cap_Dark: BaseballCap_ColorBase {
        scope = 2;
        displayName = "EZ Cap";
        descriptionShort = "EZ Wear by LordSausageFinger";
        weight = 32;
        itemSize[] = {1, 1};
        hiddenSelectionsTextures[] = {"EZLoderScreen\data\EZCap_JeanDark_co.paa", "EZLoderScreen\data\EZCap_JeanDark_co.paa", "EZLoderScreen\data\EZCap_JeanDark_co.paa"};
    };
    class TurbanHat_ColorBase;
    class EZ_Turban_Dark: TurbanHat_ColorBase {
        scope = 2;
        displayName = "EZ Turban";
        descriptionShort = "EZ Wear by LordSausageFinger. Rumour has it there's a secret compartment in the folds.";
        weight = 180;
        itemSize[] = {2, 2};
        itemsCargoSize[] = {6, 5};
        heatIsolation = 0.4;
        hiddenSelectionsTextures[] = {"EZLoderScreen\data\EZTurban_m_Dark_co.paa", "EZLoderScreen\data\EZTurban_m_Dark_co.paa", "EZLoderScreen\data\EZTurban_f_Dark_co.paa"};
    };
    class Inventory_Base;
    class SeedBase;
    class SeedPackBase;
    class TomatoSeedsPack;
    class PlantBase;
    class Edible_Base;
    class Pumpkin;
    class SlicedPumpkin;
    class EZ_PineappleSeeds: SeedBase {
        scope = 2;
        displayName = "Pineapple Seeds";
        descriptionShort = "A handful of pineapple seeds. Plant them in a garden plot or greenhouse.";
        model = "\dz\gear\cultivation\pepper_seeds.p3d";
        weight = 0;
        weightPerQuantityUnit = 1;
        itemSize[] = {1, 1};
        varQuantityInit = 10;
        varQuantityMin = 0;
        varQuantityMax = 10;
        canBeSplit = 1;
        class Horticulture {
            PlantType = "EZ_Plant_Pineapple";
        };
    };
    class EZ_PineappleSeedsPack: TomatoSeedsPack {
        scope = 2;
        displayName = "Pineapple Seeds Pack";
        descriptionShort = "A pack of pineapple seeds. Open it to get the seeds.";
        model = "\dz\gear\cultivation\tomato_seeds_pack.p3d";
        weight = 3;
        itemSize[] = {1, 1};
        class Horticulture {
            ContainsSeedsType = "EZ_PineappleSeeds";
            ContainsSeedsQuantity = 10;
        };
    };
    class EZ_Plant_Pineapple: PlantBase {
        scope = 2;
        displayName = "Pineapple plant";
        model = "\EZLoderScreen\data\pineapple\ez_pineapple_plant.p3d";
        class Horticulture {
            GrowthStagesCount = 6;
            CropsCount = 2;
            CropsType = "EZ_Pineapple";
        };
    };
    class EZ_Pineapple: Pumpkin {
        scope = 2;
        displayName = "Pineapple";
        descriptionShort = "A ripe, juicy pineapple. Sweet, filling and full of water.";
        model = "\EZLoderScreen\data\pineapple\ez_pineapple.p3d";
        rotationFlags = 34;
        weight = 0;
        weightPerQuantityUnit = 1;
        itemSize[] = {2, 3};
        stackedUnit = "g";
        quantityBar = 1;
        varQuantityInit = 250;
        varQuantityMin = 0;
        varQuantityMax = 250;
        absorbency = 0.2;
        inventorySlot[] = {};
        containsSeedsType = "EZ_PineappleSeeds";
        containsSeedsQuantity = "2";
        class DamageSystem {
            class GlobalHealth {
                class Health {
                    hitpoints = 100;
                    healthLevels[] = {1, "EZLoderScreen\data\pineapple\ez_pineapple.rvmat", 0.7, "EZLoderScreen\data\pineapple\ez_pineapple.rvmat", 0.5, "EZLoderScreen\data\pineapple\ez_pineapple.rvmat", 0.3, "EZLoderScreen\data\pineapple\ez_pineapple.rvmat", 0, "EZLoderScreen\data\pineapple\ez_pineapple.rvmat"};
                };
            };
        };
        class AnimationSources: FoodAnimationSources {};
        class Food {
            class FoodStages {
                class Raw {
                    visual_properties[] = {-1, -1, -1};
                    nutrition_properties[] = {2.5, 60, 85, 1, 0};
                    cooking_properties[] = {0, 0};
                };
                class Rotten {
                    visual_properties[] = {-1, -1, -1};
                    nutrition_properties[] = {2, 30, 45, 1, 0, 16};
                    cooking_properties[] = {0, 0};
                };
                class Baked {
                    visual_properties[] = {-1, -1, -1};
                    nutrition_properties[] = {1.75, 90, 50, 1, 0};
                    cooking_properties[] = {70, 35};
                };
                class Boiled {
                    visual_properties[] = {-1, -1, -1};
                    nutrition_properties[] = {1.5, 70, 85, 1, 0};
                    cooking_properties[] = {70, 45};
                };
                class Dried {
                    visual_properties[] = {-1, -1, -1};
                    nutrition_properties[] = {0.75, 110, 5, 1, 0};
                    cooking_properties[] = {70, 30, 80};
                };
                class Burned {
                    visual_properties[] = {-1, -1, -1};
                    nutrition_properties[] = {2, 20, 5, 1, 0, 16};
                    cooking_properties[] = {100, 30};
                };
            };
            class FoodStageTransitions: FruitStageTransitions {};
        };
        class NoiseImpact {
            strength = 600;
            type = "sound";
        };
        class AnimEvents {
            class SoundWeapon {
                class openTunaCan {
                    soundSet = "openTunaCan_SoundSet";
                    id = 204;
                };
                class pickUpItem {
                    soundSet = "pickUpPotato_SoundSet";
                    id = 797;
                };
                class Eating_TakeFood {
                    soundSet = "Eating_TakeFood_Soundset";
                    id = 889;
                };
                class Eating_BoxOpen {
                    soundSet = "Eating_BoxOpen_Soundset";
                    id = 893;
                };
                class Eating_BoxShake {
                    soundSet = "Eating_BoxShake_Soundset";
                    id = 894;
                };
                class Eating_BoxEnd {
                    soundSet = "Eating_BoxEnd_Soundset";
                    id = 895;
                };
                class drop {
                    soundset = "apple_drop_SoundSet";
                    id = 898;
                };
            };
        };
    };
    class EZ_PineappleSlice: SlicedPumpkin {
        scope = 2;
        displayName = "Pineapple Slice";
        descriptionShort = "A quarter of a pineapple. Sweet and juicy, can be eaten raw or cooked.";
        model = "\EZLoderScreen\data\pineapple\ez_pineapple_slice.p3d";
        hiddenSelections[] = {};
        hiddenSelectionsTextures[] = {};
        varQuantityInit = 63;
        varQuantityMin = 0;
        varQuantityMax = 63;
        class Food {
            class FoodStages {
                class Raw {
                    visual_properties[] = {0, 0, 0};
                    nutrition_properties[] = {2.5, 60, 85, 1, 0};
                    cooking_properties[] = {0, 0};
                };
                class Rotten {
                    visual_properties[] = {-1, -1, 5};
                    nutrition_properties[] = {2, 30, 45, 1, 0, 16};
                    cooking_properties[] = {0, 0};
                };
                class Baked {
                    visual_properties[] = {0, 1, 1};
                    nutrition_properties[] = {1.75, 90, 50, 1, 0};
                    cooking_properties[] = {70, 35};
                };
                class Boiled {
                    visual_properties[] = {0, 2, 2};
                    nutrition_properties[] = {1.5, 70, 85, 1, 0};
                    cooking_properties[] = {70, 45};
                };
                class Dried {
                    visual_properties[] = {0, 1, 3};
                    nutrition_properties[] = {0.75, 110, 5, 1, 0};
                    cooking_properties[] = {70, 30, 80};
                };
                class Burned {
                    visual_properties[] = {0, 1, 4};
                    nutrition_properties[] = {2, 20, 5, 1, 0, 16};
                    cooking_properties[] = {100, 30};
                };
            };
            class FoodStageTransitions: FruitStageTransitions {};
        };
    };
    class EZ_TerjeMedManual: Inventory_Base {
        scope = 2;
        displayName = "Terje Field Medical Manual";
        descriptionShort = "A dog-eared field medic's handbook covering wounds, bleeding, surgery, infections, poisoning, pain and the zombie virus, with the medicine to use for each. Hold it and read it.";
        model = "\dz\gear\books\Book_kniga.p3d";
        rotationFlags = 1;
        weight = 300;
        itemSize[] = {2, 2};
        absorbency = 1;
        varWetMax = 1;
        class DamageSystem {
            class GlobalHealth {
                class Health {
                    hitpoints = 100;
                    healthLevels[] = {{1.0, {"DZ\gear\books\Data\book.rvmat"}}, {0.7, {"DZ\gear\books\Data\book.rvmat"}}, {0.5, {"DZ\gear\books\Data\book_damage.rvmat"}}, {0.3, {"DZ\gear\books\Data\book_damage.rvmat"}}, {0.0, {"DZ\gear\books\Data\book_destruct.rvmat"}}};
                };
            };
        };
    };
};

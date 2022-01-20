#ifndef __OCNPCEX_H__VER0__
#define __OCNPCEX_H__VER0__

namespace Gothic_I_Classic {

    struct TNpcAttributes {
    public:
        // basic attributes, lower-bound by 0
        int     Strength;                   // ATR_STRENGTH, maps back to oCNpc::attribute[NPC_ATR_STRENGTH]
        int     Constitution;               // ATR_CONSTITUTION, [nyx-core]
        // legacy attributes, lower-bound by 0, re-mapped
        int     Dexterity;                  // ATR_DEXTERITY, maps back to oCNpc::attribute[NPC_ATR_DEXTERITY], identical to oCNpcEx::exp::Marksmanship
        // psi attributes
        int     Willpower;                  // ATR_WILL, [nyx-core]
        int     WillpowerMax;               // ATR_WILL_MAX, [nyx-core]
        int     Madness;                    // ATR_MADNESS, [nyx-core]
        int     MadnessMax;                 // ATR_MADNESS_MAX, [nyx-core]
        // consumable / replenishable attributes, regneration
        int     Nutrition;                  // ATR_NUTRITION, [nyx-core], basic currency for all regneration
        int     NutritionMax;               // ATR_NUTRITION_MAX, [nyx-core]
        int     Strength2HitpointsScale;    // ATR_STR2HP_SCALE, [nyx-core]
        int     Hitpoints;                  // ATR_HITPOINTS, maps back to oCNpc::attribute[NPC_ATR_HITPOINTS]
        int     HitpointsMax;               // ATR_HITPOINTS_MAX, maps back to oCNpc::attribute[NPC_ATR_HITPOINTSMAX]
        float   HitpointsReg;               // ATR_HITPOINTS_REG, [nyx-core], %MAX / sec
        float   HitpointsRegCost;           // ATR_HITPOINTS_REG_COST, [nyx-core], nutrition / HP regen
        float   HitpointsRegLockTime;       // ATR_HITPOINTS_REG_LOCK_TIME, [nyx-core], secs of regen suspension upon hit
        int     Constitution2StaminaScale;  // ATR_CON2STA_SCALE, [nyx-core]
        int     Stamina;                    // ATR_STAMINA, [nyx-core]
        int     StaminaMax;                 // ATR_STAMINA_MAX, [nyx-core]
        float   StaminaReg;                 // ATR_STAMINA_REG, [nyx-core], %MAX / sec
        float   StaminaRegCost;             // ATR_STAMINA_REG_COST, [nyx-core], nutrition / STA regen
        float   StaminaRegLockTime;         // ATR_STAMINA_REG_LOCK_TIME, [nyx-core], secs of regen suspension upon hit
        // TODO: mana-scaling attribute?
        int     Mana;                       // ATR_MANA, maps back to oCNpc::attribute[NPC_ATR_MANA]
        int     ManaMax;                    // ATR_MANA_MAX, maps back to oCNpc::attribute[NPC_ATR_MANAMAX]
        float   ManaReg;                    // ATR_MANA_REG, [nyx-core], %MAX / sec
        float   ManaRegCost;                // ATR_MANA_REG_COST, [nyx-core], nutrition / MANA regen
        float   ManaRegLockTime;            // ATR_MANA_REG_LOCK_TIME, [nyx-core], secs of regen suspension upon hit
        // TODO: toxin-scaling attribute?
        int     Toxin;                      // ATR_TOXIN, [nyx-core]
        int     ToxinMax;                   // ATR_TOXIN_MAX, [nyx-core]
        float   ToxinReg;                   // ATR_TOXIN_REG, [nyx-core], -%MAX / sec
        float   ToxinRegCost;               // ATR_TOXIN_REG_COST, [nyx-core], nutrition / TOXIN refresh
        float   ToxinRegLockTime;           // ATR_TOXIN_REG_LOCK_TIME, [nyx-core], secs of refresh suspension upon hit
        // TODO: define radiation mechanic
        int     Radiation;                  // ATR_RADIATION, [nyx-core]
        int     RadiationMax;               // ATR_RADIATION_MAX, [nyx-core]
        float   RadiationReg;               // ATR_RADIATION_REG, [nyx-core], -%MAX / sec
    };

    struct TNpcExperience {
    public:
        // character progression, lower-bound by 0
        int     Martialarts;                // EXP_MARTIALARTS, melee skills
        int     Marksmanship;               // EXP_MARKSMANSHIP, ranged skills, scales hit-chance!
        int     Thievery;                   // EXP_THIEVERY, stealth skills
        int     Arcane;                     // EXP_ARCANE, magic skills
        int     Athletics;                  // EXP_ATHLETICS, movement skills
        int     Huntsmanship;               // EXP_HUNTSMANSHIP, hunting skills
        int     Metallurgy;                 // EXP_METALLURGY, smithing skills
        int     Armory;                     // EXP_ARMORY, armor crafting skills
        int     Alchemy;                    // EXP_ALCHEMY, alchemy skills
        int     Philology;                  // EXP_PHILOLOGY, language skills
    };

    struct TNpcSkills {
    public:
        // EXP_MARTIALARTS                  // Ex-Swordsmanship
        int     Brawl;                      // TAL_BRAWL: [1 .. 2] (1) fistfight, (2) jump-kick
        int     Dagger;                     // TAL_DAGGER: [1 .. 3] dirty daggertricks I-III
        int     Assassin;                   // TAL_ASSASSIN: requires TAL_DAGGER
        int     Axe1H;                      // TAL_1H_AXE: [1 .. 3]
        int     Sword1H;                    // TAL_1H_SWORD: [1 .. 3]
        int     Axe2H;                      // TAL_2H_AXE: [1 .. 3]
        int     Sword2H;                    // TAL_2H_SWORD: [1 .. 3]
        int     Shield;                     // TAL_SHIELD: [1 .. 2] (1) use shield, (2) shield bash
        int     Staff;                      // TAL_STAFF: [1 .. 3]
        // EXP_MARKSMANSHIP
        int     Bow;                        // TAL_BOW: [1 .. 3]
        int     XBow;                       // TAL_XBOW: [1 .. 3]
        // EXP_THIEVERY
        int     Sneak;                      // TAL_SNEAK: enables sneaking, disabled by medium and heavy armor
        int     Hide;                       // TAL_HIDE: "hide in shadows"
        int     Picklock;                   // TAL_PICKLOCK: [1 .. 3]
        int     Pickpocket;                 // TAL_PICKPOCKET: [1 .. 3]
        int     Traps;                      // TAL_TRAPS: identify, set and disarm traps
        int     SeventhSense;               // TAL_SEVENTHSENSE: identify important things nearby
        int     NightSight;                 // TAL_NIGHTSIGHT: "dark sense", activate light-filter in darkness
        // EXP_ARCANE
        int     Mana;                       // TAL_MANA: activate mana pool
        int     Heal;                       // TAL_HEAL: activate magic healing
        int     MagicCircle;                // TAL_MAGIC: [1 .. 6], magic circle to cast runes
        int     IdentifyMagic;              // TAL_IDENTIFY: identify magic effects
        int     Scrolls;                    // TAL_SCROLLS: write magic scrolls
        int     Enchanting;                 // TAL_ENCHANTING: create magic jewelry
        int     Thaumaturgy;                // TAL_THAUMATURGY: create magic runes
        int     IronWill;                   // TAL_IRONWILL: increasing will (to survive) scaled with decreasing hp
        int     FireMaster;                 // TAL_FIREMASTER: extreme mana regen near fire / stronger fire spells?
        int     WaterMaster;                // TAL_WATERMASTER: extreme mana regen near water / stronger water spells?
        // EXP_ATHLETICS
        int     Throw;                      // TAL_THROW [1 .. 2]: distract or hit npcs, throw bombs
        int     Run;                        // TAL_RUN: enables running
        int     Sprint;                     // TAL_SPRINT: enables sprinting, disabled by heavy armor
        int     Climb;                      // TAL_CLIMB: enables climbing, disabled by heavy armor
        int     Swim;                       // TAL_SWIM [1 .. 2]: enables swimming/diving, disabled by heavy armor
        int     Acrobatics;                 // TAL_ACROBATICS: [1 .. 3] enables acro skills, disabled by medium/heavy armor
        // EXP_HUNTSMANSHIP
        int     TakeMeat;                   // TAL_TAKEMEAT: harvest meat from dead animals
        int     Skin;                       // TAL_SKIN: skin animals
        int     Claws;                      // TAL_CLAWS: take claws, horns and teeth
        int     Arrows;                     // TAL_ARROWS: craft arrows
        int     BowMaker;                   // TAL_BOWMAKER: craft bows / xbows
        int     TameAnimal;                 // TAL_TAMEANIMAL: tame wild animals
        // EXP_METALLURGY
        int     Dig;                        // TAL_DIG: dig ore
        int     Smith;                      // TAL_SMITH: forge weapons
        int     Smelting;                   // TAL_SMELTING: smelt ore, salvage metal from old items
        int     Jewelry;                    // TAL_JEWELRY: craft jewelry, insert gems, add carvings
        // EXP_ARMORY
        int     Tan;                        // TAL_TAN: make leather from raw hides
        int     Patch;                      // TAL_PATCH: patch-up / enhance armor
        int     Armor;                      // TAL_ARMOR: craft armor
        // EXP_ALCHEMY
        int     Cooking;                    // TAL_COOKING: cooking recipes
        int     Herbs;                      // TAL_HERBS: identify herbs
        int     Mushrooms;                  // TAL_MUSHROOMS: identify mushrooms
        int     Alchemy;                    // TAL_ALCHEMY: [1 .. 3], brew potions
        int     Explosives;                 // TAL_EXPLOSIVES: craft explosives
        // EXP_PHILOLOGY
        int     SpeakOrc;                   // TAL_SPEAKORC: orcish language
        int     SpeakMora;                  // TAL_SPEAKMORA: ancient human language

    };

    class oCNpcEx : public oCNpc {
    public:
        zCLASS_UNION_DECLARATION(oCNpcEx);

        TNpcAttributes  attr;               // NYX attribute extensions
        TNpcExperience exp;                 // NYX progression system
        TNpcSkills skills;                  // NYX skill table

        // timer for regeneration and buff cycles
        CTimer TimerAI;
        int LockRegenHpTime;
        int LockRegenStaminaTime;
        int LockRegenManaTime;
        int LockToxinRegenTime;

        // movement flags
        bool32 SneakEnabled;
        bool32 RunEnabled;
        bool32 SprintEnabled;
        bool32 ClimbEnabled;
        bool32 SwimEnabled;
        bool32 AcrobaticsEnabled;

        oCNpcEx();
        void ProcessAttributes();
        void ProcessRegen();
        void ProcessSprint();
        void ProcessAnimations();
        virtual void ProcessNpc();
        virtual void OnDamage(oSDamageDescriptor& damage);
        virtual void Archive(zCArchiver& ar);
        virtual void Unarchive(zCArchiver& ar);
    };


    class oCObjectFactoryEx : public oCObjectFactory {
    public:
        zCLASS_UNION_DECLARATION(oCObjectFactoryEx);
        virtual oCNpc* CreateNpc(int index);
    };
}

#endif

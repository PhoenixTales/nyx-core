#include <UnionAfx.h>
#include "oCNpcEx.h"
//#include "oCGameEx.h"

namespace Gothic_I_Classic {

    //extern oCGameEx* ogame_ex;  // get reference to extended game object

    zCLASS_UNION_DEFINITION(oCNpcEx, oCNpc, 0, 0);
    zCLASS_UNION_DEFINITION(oCObjectFactoryEx, oCObjectFactory, 0, 0);

    oCNpcEx::oCNpcEx() : oCNpc() {
        // regen timer locks
        LockRegenHpTime = 0;
        LockRegenManaTime = 0;
        LockRegenStaminaTime = 0;
        LockToxinRegenTime = 0;
        // movement flags
        SneakEnabled = True;
        RunEnabled = True;
        SprintEnabled = True;
        ClimbEnabled = True;
        SwimEnabled = True;
        AcrobaticsEnabled = True;
        // default NPC primary attributes, TODO: define macro
        attr.Strength = 5;
        attr.Constitution = 5;
        attr.Dexterity = 5;
        attr.WillpowerMax = 5;
        attr.Willpower = attr.WillpowerMax;
        attr.MadnessMax = attr.WillpowerMax;
        attr.Madness = 0;
        attr.NutritionMax = 1000;
        attr.Nutrition = attr.NutritionMax;
        attr.Strength2HitpointsScale = 8;
        attr.HitpointsMax = attr.Strength * attr.Strength2HitpointsScale;
        attr.Hitpoints = attr.HitpointsMax;
        attr.HitpointsReg = 1.0f;
        attr.HitpointsRegCost = 4.0f;
        attr.Constitution2StaminaScale = 10;
        attr.StaminaMax = attr.Constitution * attr.Constitution2StaminaScale;
        attr.Stamina = attr.StaminaMax;
        attr.StaminaReg = 5.0f;
        attr.StaminaRegCost = 1.0f;
        attr.ManaMax = 5;
        attr.Mana = attr.ManaMax;
        attr.ManaReg = 1.0f;
        attr.ManaRegCost = 2.0f;
        attr.Toxin = 0;
        attr.ToxinMax = 100;
        attr.ToxinReg = 0.5f;
        attr.ToxinRegCost = 2.0f;
        attr.Radiation = 0;
        attr.RadiationMax = 100;
        // default NPC experience, TODO: define macro
        exp.Martialarts = 5;
        exp.Marksmanship = 5;
        exp.Thievery = 5;
        exp.Arcane = 5;
        exp.Athletics = 5;
        exp.Huntsmanship = 5;
        exp.Metallurgy = 5;
        exp.Armory = 5;
        exp.Alchemy = 5;
        exp.Philology = 5;
        // default NPC skills, TODO: define macro
    }

    void oCNpcEx::ProcessAttributes() {
        // called in oCNpcEx::ProcessNPC(), enforces attribute consistency
        // get base attributes from oCNpc::attribute
        attr.Hitpoints = attribute[NPC_ATR_HITPOINTS];
        attr.HitpointsMax = attribute[NPC_ATR_HITPOINTSMAX];
        attr.Mana = attribute[NPC_ATR_MANA];
        attr.ManaMax = attribute[NPC_ATR_MANAMAX];
        attr.Strength = attribute[NPC_ATR_STRENGTH];
        attr.Dexterity = attribute[NPC_ATR_DEXTERITY];
        exp.Marksmanship = attribute[NPC_ATR_DEXTERITY];
        // apply attribute scales
        attr.HitpointsMax = attr.Strength * attr.Strength2HitpointsScale;
        attr.StaminaMax = attr.Constitution * attr.Constitution2StaminaScale;
        // apply attribute caps
        attr.Hitpoints = min(attr.Hitpoints, attr.HitpointsMax);
        attr.Mana = min(attr.Mana, attr.ManaMax);
        attr.Stamina = min(attr.Stamina, attr.StaminaMax);
        // map base attributes back to oCNpc::attribute
        attribute[NPC_ATR_HITPOINTS] = attr.Hitpoints;
        attribute[NPC_ATR_HITPOINTSMAX] = attr.HitpointsMax;
        attribute[NPC_ATR_MANA] = attr.Mana;
        attribute[NPC_ATR_MANAMAX] = attr.ManaMax;
        attribute[NPC_ATR_STRENGTH] = attr.Strength;
        attribute[NPC_ATR_DEXTERITY] = attr.Dexterity;
        // attribute[NPC_ATR_REGENERATEHP] not mapped back, since unused in engine VER0
        // attribute[NPC_ATR_REGENERATEMANA] not mapped back, since unused in engine VER0
    }

    void oCNpcEx::ProcessRegen() {
        // Regeneration Timers ID, TODO: refactor into NPC
        static const uint RegenStaminaTimerID = 1;
        static const uint RegenHpTimerID = 2;
        static const uint RegenManaTimerID = 3;
        static const uint RegenToxinTimerID = 4;
        static const uint RegenLockTimerID = 10;

        // If the game is paused, timers will also be paused
        TimerAI.Suspend(RegenStaminaTimerID, ogame->singleStep);
        TimerAI.Suspend(RegenHpTimerID, ogame->singleStep);
        TimerAI.Suspend(RegenManaTimerID, ogame->singleStep);
        TimerAI.Suspend(RegenToxinTimerID, ogame->singleStep);
        TimerAI.Suspend(RegenLockTimerID, ogame->singleStep);

        // regenerate stamina, health, mana, toxin (in that order) by consuming nutrition
        float points_per_sec;  // total amount of points regenerated per sec
        float cost_per_sec;  // total nutrition cost per sec
        int time_per_point;  // time in [ms] to regenerate one point
        int cost_per_point;  // nutrition cost to regenerate one point

        // stamina
        if (!LockRegenStaminaTime && attr.Stamina < attr.StaminaMax) {
          points_per_sec = (attr.StaminaReg / 100.0f) * attr.StaminaMax;
          cost_per_sec = attr.StaminaRegCost * points_per_sec;
          time_per_point = 1000.0f / points_per_sec;
          cost_per_point = cost_per_sec / points_per_sec;
          if (TimerAI(RegenStaminaTimerID, time_per_point)) {
            if (attr.Nutrition >= cost_per_point) {
              attr.Stamina++;
              attr.Nutrition -= cost_per_point;
            }
            else {
              //screen->PrintCXY("I'm too hungry to regenerate stamina!");  // DEBUG
            }
          }
        }
        // health
        if (!LockRegenHpTime && attribute[NPC_ATR_HITPOINTS] < attribute[NPC_ATR_HITPOINTSMAX]) {
          points_per_sec = (attr.HitpointsReg / 100.0f) * attr.HitpointsMax;
          cost_per_sec = attr.HitpointsRegCost * points_per_sec;
          time_per_point = 1000.0f / points_per_sec;
          cost_per_point = cost_per_sec / points_per_sec;
          if (TimerAI(RegenHpTimerID, time_per_point)) {
            if (attr.Nutrition >= cost_per_point) {
              attribute[NPC_ATR_HITPOINTS]++;
              attr.Nutrition -= cost_per_point;
            }
            else {
              //screen->PrintCXY("I'm too hungry to regenerate life!");  // DEBUG
            }
          }
        }
        // mana
        if (!LockRegenManaTime && attribute[NPC_ATR_MANA] < attribute[NPC_ATR_MANAMAX]) {
          points_per_sec = (attr.ManaReg / 100.0f) * attr.ManaMax;
          cost_per_sec = attr.ManaRegCost * points_per_sec;
          time_per_point = 1000.0f / points_per_sec;
          cost_per_point = cost_per_sec / points_per_sec;
          if (TimerAI(RegenManaTimerID, time_per_point)) {
            if (attr.Nutrition >= cost_per_point) {
              attribute[NPC_ATR_MANA]++;
              attr.Nutrition -= cost_per_point;
            }
            else {
              //screen->PrintCXY("I'm too hungry to regenerate mana!");  // DEBUG
            }
          }
        }
        // toxin
        if (!LockToxinRegenTime && attr.Toxin > 0) {
          points_per_sec = (attr.ToxinReg / 100.0f) * attr.ToxinMax;
          cost_per_sec = attr.ToxinRegCost * points_per_sec;
          time_per_point = 1000.0f / points_per_sec;
          cost_per_point = cost_per_sec / points_per_sec;
          if (TimerAI(RegenToxinTimerID, time_per_point))
            if (attr.Nutrition >= cost_per_point) {
              attr.Toxin--;
              attr.Nutrition -= cost_per_point;
            }
            else {
              //screen->PrintCXY("I'm too hungry to refresh from toxicity!");  // DEBUG
            }
        }
        // TODO: drain life, if poisoned


        // And this timer removes locks from regen. Every second, it lowers locks by 1.
        // And when the value becomes 0, regeneration starts working again.
        if (TimerAI(RegenLockTimerID, 1000)) {
            if (LockRegenHpTime)
                LockRegenHpTime--;
            if (LockRegenManaTime)
                LockRegenManaTime--;
            if (LockRegenStaminaTime)
                LockRegenStaminaTime--;
            if (LockToxinRegenTime)
              LockToxinRegenTime--;
        }
    }

    void oCNpcEx::ProcessSprint() {
      // stamina waste timer ID
      static const uint SpendStaminaID = 0;
      if (this != player)
        return;

      // Get a running animation instance for the current combat state.
      // from the list of animations anictrl, where s_runl is an array of identifiers.
      // Next, check if the animation of the current fmode is active. We also define
      // the possibility of imposing a sprint.
      zCModelAni* RunAni = GetModel()->GetAniFromAniID(anictrl->s_runl[fmode]);
      bool32      AniIsActive = GetModel()->IsStateActive(RunAni);
      bool32      CanSprint = zinput->GetMouseButtonPressedMid() && attr.Stamina && AniIsActive;

      // Sprint activation
      if (CanSprint && !SprintEnabled) {
        RunAni->fpsRate = RunAni->fpsRateSource * 1.5;
        SprintEnabled = True;
      }
      // Sprint deactivation
      else if (!CanSprint && SprintEnabled) {
        RunAni->fpsRate = RunAni->fpsRateSource;
        SprintEnabled = False;
      }

      // Bind the timer to the gameplay. He will pause if the game is paused.
      TimerAI.Suspend(SpendStaminaID, ogame->singleStep);

      if (SprintEnabled) {
        // We indicate that 2 seconds after the sprint stamina will not be restored
        LockRegenStaminaTime = 2;

        // A waste of stamina will be spent by pressing MMB and then every 100ms
        if (attr.Stamina && TimerAI(SpendStaminaID, 100, TM_PRIMARY))
          attr.Stamina--;
      }

    }

    /* processes animation cycle and handles stamina consumption */
    void oCNpcEx::ProcessAnimations() {
      // stamina consumption timer
      static const uint SpendStaminaID = 0;
      TimerAI.Suspend(SpendStaminaID, ogame->singleStep);
      // character model
      zCModel* mdl = GetModel();
      // running / sprinting
      if (this != player) {
        // run animations of NPCs are not affected by pressed button
      }
      else {
        zCModelAni* Ani_S_RUNL = mdl->GetAniFromAniID(mdl->GetAniIDFromAniName("S_RUNL"));
        bool32      IsRunning = (mdl->IsStateActive(Ani_S_RUNL));
        // TODO: change MMB to input map
        bool32      CanSprint = zinput->GetMouseButtonPressedMid() && attr.Stamina && IsRunning;
        if (CanSprint && !SprintEnabled) {
          Ani_S_RUNL->fpsRate = Ani_S_RUNL->fpsRateSource * 1.5;
          SprintEnabled = True;
        }
        else if (!CanSprint && SprintEnabled) {
          Ani_S_RUNL->fpsRate = Ani_S_RUNL->fpsRateSource;
          SprintEnabled = False;
        }
        if (SprintEnabled) {
          LockRegenStaminaTime = 2;  // TODO: NPC-based regen lock
          if (attr.Stamina && TimerAI(SpendStaminaID, 100, TM_PRIMARY))
            attr.Stamina--;
        }
      }
      // TODO: jump animations
      // melee animations
      zCModelAni* Ani_S_1HATTACK = mdl->GetAniFromAniID(mdl->GetAniIDFromAniName("S_1HATTACK"));
      zCModelAni* Ani_T_1HATTACKL = mdl->GetAniFromAniID(mdl->GetAniIDFromAniName("T_1HATTACKL"));
      zCModelAni* Ani_T_1HATTACKR = mdl->GetAniFromAniID(mdl->GetAniIDFromAniName("T_1HATTACKR"));
      zCModelAni* Ani_T_1HATTACKMOVE = mdl->GetAniFromAniID(mdl->GetAniIDFromAniName("T_1HATTACKMOVE"));
      zCModelAni* Ani_S_2HATTACK = mdl->GetAniFromAniID(mdl->GetAniIDFromAniName("S_2HATTACK"));
      zCModelAni* Ani_T_2HATTACKL = mdl->GetAniFromAniID(mdl->GetAniIDFromAniName("T_2HATTACKL"));
      zCModelAni* Ani_T_2HATTACKR = mdl->GetAniFromAniID(mdl->GetAniIDFromAniName("T_2HATTACKR"));
      zCModelAni* Ani_T_2HATTACKMOVE = mdl->GetAniFromAniID(mdl->GetAniIDFromAniName("T_2HATTACKMOVE"));
      // ranged animations
      // TODO: stamina consumption while aiming?
      zCModelAni* Ani_S_BOWSHOOT = mdl->GetAniFromAniID(mdl->GetAniIDFromAniName("S_BOWSHOOT"));
      zCModelAni* Ani_S_CBOWSHOOT = mdl->GetAniFromAniID(mdl->GetAniIDFromAniName("S_CBOWSHOOT"));
      zCModelAni* Ani_T_BOWRELOAD = mdl->GetAniFromAniID(mdl->GetAniIDFromAniName("T_BOWRELOAD"));
      zCModelAni* Ani_T_CBOWRELOAD = mdl->GetAniFromAniID(mdl->GetAniIDFromAniName("T_CBOWRELOAD"));
      // melee parade animations
      zCModelAni* Ani_T_1HPARADE_O = mdl->GetAniFromAniID(mdl->GetAniIDFromAniName("T_1HPARADE_O"));
      zCModelAni* Ani_T_2HPARADE_O = mdl->GetAniFromAniID(mdl->GetAniIDFromAniName("T_2HPARADE_O"));
      // detect active animation, TODO: can we do this more elegantly?
      zCModelAni* ActiveAni = 0;
      if (mdl->IsStateActive(Ani_S_1HATTACK)) ActiveAni = Ani_S_1HATTACK;
      if (mdl->IsStateActive(Ani_T_1HATTACKL)) ActiveAni = Ani_T_1HATTACKL;
      if (mdl->IsStateActive(Ani_T_1HATTACKR)) ActiveAni = Ani_T_1HATTACKR;
      if (mdl->IsStateActive(Ani_T_1HATTACKMOVE)) ActiveAni = Ani_T_1HATTACKMOVE;
      if (mdl->IsStateActive(Ani_S_2HATTACK)) ActiveAni = Ani_S_2HATTACK;
      if (mdl->IsStateActive(Ani_T_2HATTACKL)) ActiveAni = Ani_T_2HATTACKL;
      if (mdl->IsStateActive(Ani_T_2HATTACKR)) ActiveAni = Ani_T_2HATTACKR;
      if (mdl->IsStateActive(Ani_T_2HATTACKMOVE)) ActiveAni = Ani_T_2HATTACKMOVE;
      if (mdl->IsStateActive(Ani_S_BOWSHOOT)) ActiveAni = Ani_S_BOWSHOOT;
      if (mdl->IsStateActive(Ani_T_1HPARADE_O)) ActiveAni = Ani_T_1HPARADE_O;
      if (mdl->IsStateActive(Ani_T_2HPARADE_O)) ActiveAni = Ani_T_2HPARADE_O;
      // detect stamina-consuming moves
      bool32 IsStriking = (mdl->IsStateActive(Ani_S_1HATTACK)) \
        || (mdl->IsStateActive(Ani_T_1HATTACKL)) \
        || (mdl->IsStateActive(Ani_T_1HATTACKR)) \
        || (mdl->IsStateActive(Ani_T_1HATTACKMOVE)) \
        || (mdl->IsStateActive(Ani_S_2HATTACK)) \
        || (mdl->IsStateActive(Ani_T_2HATTACKL)) \
        || (mdl->IsStateActive(Ani_T_2HATTACKR)) \
        || (mdl->IsStateActive(Ani_T_2HATTACKMOVE));
      bool32 IsShooting = (mdl->IsStateActive(Ani_S_BOWSHOOT)) \
        || (mdl->IsStateActive(Ani_S_CBOWSHOOT));
      bool32 IsParrying = (mdl->IsStateActive(Ani_T_1HPARADE_O)) \
        || (mdl->IsStateActive(Ani_T_2HPARADE_O));
      // compute stamina consumption when using a weapon
      oCItem* EquippedWeapon = this->GetWeapon();
      int cur_str = attr.Strength;
      int cond_str;
      int cost_sta;
      if (IsStriking || IsShooting || IsParrying) {
        if (attr.Stamina) {
          if (TimerAI(SpendStaminaID, 1500, TM_PRIMARY)) {  // TODO: bind stamina consumption precisely to ani execution?
            cond_str = EquippedWeapon->cond_value[2];  // TODO: is cond_value[2] hard-coded?
            cond_str *= 2;  // DEBUG: increase to see effect
            cost_sta = max(0, cond_str - cur_str);
            attr.Stamina = max(0, attr.Stamina - cost_sta);
            if (IsStriking) {
              ActiveAni->fpsRate = ActiveAni->fpsRateSource;  // play active fight ani at normal speed
            }
            else if (IsShooting) {
              ActiveAni->fpsRate = ActiveAni->fpsRateSource;  // play active fight ani at normal speed
              // play reload anis at normal speed
              Ani_T_BOWRELOAD->fpsRate = Ani_T_BOWRELOAD->fpsRateSource;
              Ani_T_CBOWRELOAD->fpsRate = Ani_T_CBOWRELOAD->fpsRateSource;
            }
          }
        }
        else {
          // TODO: for ranged fighting, slow down reload
          if (IsStriking) {
            ActiveAni->fpsRate = ActiveAni->fpsRateSource * 0.7;  // slow down active fight ani
          }
          else if (IsShooting) {
            ActiveAni->fpsRate = ActiveAni->fpsRateSource * 0.7;  // slow down active fight ani
            // slow down reload anis
            Ani_T_BOWRELOAD->fpsRate = Ani_T_BOWRELOAD->fpsRateSource * 0.7;
            Ani_T_CBOWRELOAD->fpsRate = Ani_T_CBOWRELOAD->fpsRateSource * 0.7;
          }
        }
        LockRegenStaminaTime = 2;  // TODO: NPC-based regen lock
      }
    }

    void oCNpcEx::ProcessNpc() {
        // Binding a timer to an NPC loop
        TimerAI.Attach();
        // call extensions of ProcessNPC
        ProcessAttributes();  // enforce consistency of attributes
        ProcessRegen();
        //ProcessSprint();  // TODO: movestates
        ProcessAnimations();

        // fade out other NPCs obstructing player camera
        if (this != player) {
            // Define the bbox model. We calculate its actual center
            // summing up the local center with the NPC position in the world.
            zTBBox3D BBox3D = GetModel()->bbox3D;
            zVEC3    VobCenter = GetPositionWorld() + BBox3D.GetCenter();
            zVEC3    CameraPosition = ogame->GetCameraVob()->GetPositionWorld();
            float    DistanceToCamera = VobCenter.Distance(CameraPosition);

            // Next, we calculate the total radius of the model through the length of the difference
            // minimum and maximum coordinates. By condition, we are interested
            // 0.8 of the length and 0.5 of the previous result.
            float FadeDistanceBegin = (BBox3D.maxs - BBox3D.mins).Length() * 0.8f;
            float FadeDistanceEnd = FadeDistanceBegin * 0.5f;

            // The condition for turning off the alpha if the character is not interfering.
            if (DistanceToCamera > FadeDistanceBegin) {
                if (visualAlphaEnabled) {
                    visualAlpha = 1.0f;
                    visualAlphaEnabled = False;
                }
            }
            else {
                if (!visualAlphaEnabled)
                    visualAlphaEnabled = True;

                // If the camera is inside the cutoff border closest to the NPC,
                // then character transparency is always 0
                if (DistanceToCamera < FadeDistanceEnd)
                    visualAlpha = 0.0f;

                // Otherwise, we work according to the relationship formulas, where we determine
                // amount of transparency at a given camera position.
                else {
                    float FadeLengthMax = FadeDistanceBegin - FadeDistanceEnd;
                    float FadeLength = DistanceToCamera - FadeDistanceEnd;
                    visualAlpha = 1.0f / FadeLengthMax * FadeLength;
                }
            }
        }

        // call parent
        oCNpc::ProcessNpc();
    }

    void oCNpcEx::OnDamage(oSDamageDescriptor& damage) {
        oCNpc::OnDamage(damage);
        // suspend regeneration for a brief period of time [sec]
        // TODO: use attr.<ATR>LockTime here!
        LockRegenStaminaTime = 2;
        LockRegenHpTime = 5;
        LockRegenManaTime = 2;
        LockToxinRegenTime = 0;
    }

    void oCNpcEx::Archive(zCArchiver& ar) {
        // Save original NPC data to save
        oCNpc::Archive(ar);

        // We save our data in a save
        // TODO: add all new attributes to save file
        //ar.WriteFloat("REGENHPINTENSITY", RegenHpIntensity);
        //ar.WriteFloat("REGENMANAINTENSITY", RegenManaIntensity);
        //ar.WriteFloat("REGENSTAMINAINTENSITY", RegenStaminaIntensity);
        ar.WriteInt("LOCKREGENHPTIME", LockRegenHpTime);
        ar.WriteInt("LOCKREGENMANATIME", LockRegenManaTime);
        ar.WriteInt("LOCKREGENSTAMINATIME", LockRegenStaminaTime);
        ar.WriteInt("STAMINAMAX", attr.StaminaMax);
        ar.WriteInt("STAMINA", attr.Stamina);
    }

    void oCNpcEx::Unarchive(zCArchiver& ar) {
        // Read the original NPC data from the save game
        oCNpc::Unarchive(ar);

        // We read our NPC data from the save game
        // TODO: read all new attributes from save file
        //ar.ReadFloat("REGENHPINTENSITY", RegenHpIntensity);
        //ar.ReadFloat("REGENMANAINTENSITY", RegenManaIntensity);
        //ar.ReadFloat("REGENSTAMINAINTENSITY", RegenStaminaIntensity);
        ar.ReadInt("LOCKREGENHPTIME", LockRegenHpTime);
        ar.ReadInt("LOCKREGENMANATIME", LockRegenManaTime);
        ar.ReadInt("LOCKREGENSTAMINATIME", LockRegenStaminaTime);
        ar.ReadInt("STAMINAMAX", attr.StaminaMax);
        ar.ReadInt("STAMINA", attr.Stamina);
    }

    oCNpc* oCObjectFactoryEx::CreateNpc(int index) {
        oCNpc* npc = new oCNpcEx();

        if (index != zPAR_INDEX_UNDEF)
            npc->InitByScript(index, 0);

        return npc;
    }

    void OnInitFactory() {
        zfactory = new oCObjectFactoryEx();
        // TODO: define new player reference here (oCNpcEx)!
    }
}

// call in Game_DefineExternals
void GameGlobal_OnInitFactory() {
    Gothic_I_Classic::OnInitFactory();
}

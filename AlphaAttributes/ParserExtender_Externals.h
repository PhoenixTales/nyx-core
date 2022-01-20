/* zParserExtender, adapted from: https://github.com/Gratt-5r2/zParserExtender */
#include "oCNpcEx.h"

namespace NAMESPACE {


  /****************************************
  ********** zParserExtender core *********
  ****************************************/

  int Cast_PointerToInstance() {
    zCParser* par = zCParser::GetParser();
    int address;
    par->GetParameter(address);
    par->SetReturn((void*)address);
    return 0;
  }

  int Cast_InstanceToPointer() {
    zCParser* par = zCParser::GetParser();
    void* instance = par->GetInstance();
    par->SetReturn( (int)instance );
    return 0;
  }

  int Cast_PointerToNpc() {
    zCParser* par = zCParser::GetParser();
    void* instance = par->GetInstance();
    par->SetReturn( (int)instance );
    return 0;
  }

  int Cast_InstanceIsNpc() {
    zCParser* par = zCParser::GetParser();
    zCObject* instance = (zCObject*)par->GetInstance();
    par->SetReturn( (int)instance->CastTo<oCNpc>() );
    return 0;
  }

  int Cast_InstanceIsItem() {
    zCParser* par = zCParser::GetParser();
    zCObject* instance = (zCObject*)par->GetInstance();
    par->SetReturn( (int)instance->CastTo<oCItem>() );
    return 0;
  }

  int Cast_InstanceIsMob() {
    zCParser* par = zCParser::GetParser();
    zCObject* instance = (zCObject*)par->GetInstance();
    par->SetReturn( (int)instance->CastTo<oCMOB>() );
    return 0;
  }

  int Cast_GetInstanceIndex() {
    zCParser* par = zCParser::GetParser();
    zCObject* instance = (zCObject*)par->GetInstance();
    oCVob* vob = instance->CastTo<oCVob>();
    par->SetReturn( vob ? vob->GetInstance() : -1 );
    return 0;
  }

  int Hlp_HasFocusVob() {
    zCParser* par = zCParser::GetParser();
    oCNpc* instance = (oCNpc*)par->GetInstance();
    par->SetReturn( (int)instance->GetFocusVob() );
    return 0;
  }

  int Hlp_GetFocusVob() {
    zCParser* par = zCParser::GetParser();
    oCNpc* instance = (oCNpc*)par->GetInstance();
    par->SetReturn( instance->GetFocusVob() );
    return 0;
  }

  int Hlp_GetFocusVobName() {
    zCParser* par = zCParser::GetParser();
    oCNpc* instance = (oCNpc*)par->GetInstance();
    par->SetReturn( (zSTRING&)instance->GetFocusVob()->GetObjectName() );
    return 0;
  }

  int Hlp_GetStringLength() {
    zCParser* par = zCParser::GetParser();
    zSTRING str;
    par->GetParameter( str );
    par->SetReturn( str.Length() );
    return 0;
  }

  int Hlp_IsNAN() {
    zCParser* par = zCParser::GetParser();
    float value;
    par->GetParameter( value );
    par->SetReturn( ISNAN( value ) );
    return 0;
  }

  int Hlp_KeyToggled() {
    zCParser* par = zCParser::GetParser();
    int key;
    par->GetParameter( key );
    par->SetReturn( zKeyToggled( key ) );
    return 0;
  }

  int Hlp_KeyPressed() {
    zCParser* par = zCParser::GetParser();
    int key;
    par->GetParameter( key );
    par->SetReturn( zKeyPressed( key ) );
    return 0;
  }

  int Hlp_LogicalKeyToggled() {
    zCParser* par = zCParser::GetParser();
    int logical;
    par->GetParameter( logical );
    par->SetReturn( zinput->GetToggled( logical ) );
    return 0;
  }

  int Hlp_GameOnPause() {
    zCParser* par = zCParser::GetParser();
    par->SetReturn( ogame->IsOnPause() );
    return 0;
  }

  int Wld_ChangeLevel() {
    zCParser* par = zCParser::GetParser();
    zSTRING worldName;
    zSTRING waypointName;
    par->GetParameter( waypointName );
    par->GetParameter( worldName );
    ogame->ChangeLevel( worldName, waypointName );
    return 0;
  }

  int Wld_FindVob() {
    zCParser* par = zCParser::GetParser();
    zSTRING vobName;
    par->GetParameter( vobName );
    oCWorld* world = ogame->GetGameWorld();
    zCVob* vob = world->SearchVobByName( vobName );
    par->SetReturn( vob );
    return 0;
  }

  int Wld_PlayEffectVob() {
    zCParser* par = zCParser::GetParser();
    zSTRING effect;
    zCVob* pvob;
    int level;
    int damage;
    int damage_type;
    int damage_speed;

    par->GetParameter( damage_speed );
    par->GetParameter( damage_type );
    par->GetParameter( damage );
    par->GetParameter( level );
    pvob = (zCVob*)par->GetInstance();
    par->GetParameter( effect );

    oCVisualFX::CreateAndPlay( effect, pvob, Null, level, damage, damage_type, damage_speed );
    return 0;
  }

  int Wld_PlayEffectAt() {
    zCParser* par = zCParser::GetParser();
    zSTRING effect;
    zVEC3 ppos;
    int level;
    int damage;
    int damage_type;
    int damage_speed;

    par->GetParameter( damage_speed );
    par->GetParameter( damage_type );
    par->GetParameter( damage );
    par->GetParameter( level );
    ppos = *(zVEC3*)par->GetInstance();
    par->GetParameter( effect );

    oCVisualFX::CreateAndPlay( effect, ppos, Null, level, damage, damage_type, damage_speed );
    return 0;
  }

  int Wld_ToggleRain() {
    zCParser* par = zCParser::GetParser();
    oCWorld* world = ogame->GetGameWorld();
    float weight;
    float time;
    par->GetParameter( time );
    par->GetParameter( weight );
    zCSkyControler_Outdoor* controller = world->GetActiveSkyControler()->CastTo<zCSkyControler_Outdoor>();
    if( controller )
      controller->SetRainFXWeight( weight, time );

    return 0;
  }

  int Wld_SetWeatherType() {
#if CURRENT_ENGINE >= 2
    zCParser* par = zCParser::GetParser();
    oCWorld* world = ogame->GetGameWorld();
    int weather;
    par->GetParameter( weather );
    zCSkyControler_Outdoor* controller = world->GetActiveSkyControler()->CastTo<zCSkyControler_Outdoor>();
    if( controller )
      controller->SetWeatherType( (zTWeather&)weather );
#endif
    return 0;
  }

  int Wld_GetWeatherType() {
    zCParser* par = zCParser::GetParser();
#if CURRENT_ENGINE >= 2
    oCWorld* world = ogame->GetGameWorld();
    int weather;
    par->GetParameter( weather );
    zCSkyControler_Outdoor* controller = world->GetActiveSkyControler()->CastTo<zCSkyControler_Outdoor>();
    par->SetReturn( controller ? controller->GetWeatherType() : -1 );
#else
    par->SetReturn( -1 );
#endif
    return 0;
  }

  int Mdl_GetAnimationIndex() {
    zCParser* par = zCParser::GetParser();
    oCNpc* npc;
    zSTRING aniName;
    par->GetParameter( aniName );
    npc = (oCNpc*)par->GetInstance();
    npc->GetModel()->GetAniIDFromAniName( aniName );
    return 0;
  }

  int Mdl_GetAnimationName() {
    zCParser* par = zCParser::GetParser();
    oCNpc* npc;
    int index;
    par->GetParameter( index );
    npc = (oCNpc*)par->GetInstance();
    zCModelAni* ani = npc->GetModel()->GetAniFromAniID( index );
    par->SetReturn( ani ? ani->aniName : "" );
    return 0;
  }

  int Mdl_AnimationIsExists() {
    zCParser* par = zCParser::GetParser();
    oCNpc* npc;
    int index;
    par->GetParameter( index );
    npc = (oCNpc*)par->GetInstance();
    zCModelAni* ani = npc->GetModel()->GetAniFromAniID( index );
    par->SetReturn( ani ? True : False );
    return 0;
  }

  int Mdl_AnimationIsActive() {
    zCParser* par = zCParser::GetParser();
    oCNpc* npc;
    int index;
    par->GetParameter( index );
    npc = (oCNpc*)par->GetInstance();
    zCModel* model = npc->GetModel();
    zCModelAni* ani = model->GetAniFromAniID( index );
    par->SetReturn( ani ? model->IsAniActive( ani ) : False );
    return 0;
  }

  int Mdl_SetAllAnimationsFPS() {
    zCParser* par = zCParser::GetParser();
    oCNpc* npc;
    float fps;
    par->GetParameter( fps );
    npc = (oCNpc*)par->GetInstance();
    zCModel* model = npc->GetModel();

    auto& protos = model->modelProtoList;
    for( int i = 0; i < protos.GetNum(); i++ ) {
      auto& anis = protos[i]->protoAnis;
      for( int j = 0; j < anis.GetNum(); j++ ) {
        anis[j]->fpsRate = fps;
      }
    } 

    return 0;
  }

  int Mdl_ResetAllAnimationsFPS() {
    zCParser* par = zCParser::GetParser();
    oCNpc* npc;
    npc = (oCNpc*)par->GetInstance();
    zCModel* model = npc->GetModel();

    auto& protos = model->modelProtoList;
    for( int i = 0; i < protos.GetNum(); i++ ) {
      auto& anis = protos[i]->protoAnis;
      for( int j = 0; j < anis.GetNum(); j++ ) {
        anis[j]->fpsRate = anis[j]->fpsRateSource;
      }
    }

    return 0;
  }

  int Mdl_SetAnimationFPS() {
    zCParser* par = zCParser::GetParser();
    oCNpc* npc;
    int index;
    float fps;
    par->GetParameter( fps );
    par->GetParameter( index );
    npc = (oCNpc*)par->GetInstance();
    zCModel* model = npc->GetModel();

    zCModelAni* ani = model->GetAniFromAniID( index );
    if( ani )
      ani->fpsRate = fps;

    return 0;
  }

  int Mdl_ResetAnimationFPS() {
    zCParser* par = zCParser::GetParser();
    oCNpc* npc;
    int index;
    par->GetParameter( index );
    npc = (oCNpc*)par->GetInstance();
    zCModel* model = npc->GetModel();

    zCModelAni* ani = model->GetAniFromAniID( index );
    if( ani )
      ani->fpsRate = ani->fpsRateSource;

    return 0;
  }

  int Mdl_SetVisible() {
    zCParser* par = zCParser::GetParser();
    oCNpc* npc;
    int visible;
    par->GetParameter( visible );
    npc = (oCNpc*)par->GetInstance();
    npc->GetModel()->isVisible = visible;
    return 0;
  }

  int Npc_SetAsHero() {
    zCParser* par = zCParser::GetParser();
    oCNpc* npc;
    npc = (oCNpc*)par->GetInstance();
    npc->SetAsPlayer();
    return 0;
  }

  int Npc_OpenInventory() {
    zCParser* par = zCParser::GetParser();
    oCNpc* npc;
    npc = (oCNpc*)par->GetInstance();
    npc->OpenInventory();
    return 0;
  }

  int Npc_OpenInventorySteal() {
    zCParser* par = zCParser::GetParser();
    oCNpc* npc;
    npc = (oCNpc*)par->GetInstance();
    npc->OpenSteal();
    return 0;
  }

  int Npc_OpenInventoryTrade() {
    zCParser* par = zCParser::GetParser();
    oCNpc* npc;
    npc = (oCNpc*)par->GetInstance();
    npc->OpenTradeOffer( player );
    return 0;
  }

  int Mob_Destroy() {
    zCParser* par = zCParser::GetParser();
    oCMOB* mob;
    mob = (oCMOB*)par->GetInstance();
    mob->Destroy();
    return 0;
  }

  int Mob_RemoveItem() {
    zCParser* par = zCParser::GetParser();
    oCMOB* mob;
    int index;
    par->GetParameter( index );
    mob = (oCMOB*)par->GetInstance();
    
    oCMobContainer* mob_container = mob->CastTo<oCMobContainer>();
    if( mob_container ) {
      zCListSort<oCItem>* list = mob_container->items->contents->next;
      while( list ) {
        oCItem* item = list->GetData();
        if( item->instanz == index ) {
          mob_container->Remove( item );
          break;
        }

        list = list->next;
      }
    }

    return 0;
  }

  int Mob_RemoveItems() {
    zCParser* par = zCParser::GetParser();
    oCMOB* mob;
    int index;
    int count;
    par->GetParameter( count );
    par->GetParameter( index );
    mob = (oCMOB*)par->GetInstance();
    
    oCMobContainer* mob_container = mob->CastTo<oCMobContainer>();
    if( mob_container ) {
      zCListSort<oCItem>* list = mob_container->items->contents->next;
      while( list ) {
        oCItem* item = list->GetData();
        if( item->instanz == index ) {
          if( item->amount > count )
            item->amount -= count;
          else
            mob_container->Remove( item );
          break;
        }

        list = list->next;
      }
    }

    return 0;
  }

  int Mob_InsertItem() {
    zCParser* par = zCParser::GetParser();
    oCMOB* mob;
    int index;
    par->GetParameter( index );
    mob = (oCMOB*)par->GetInstance();

    oCMobContainer* mob_container = mob->CastTo<oCMobContainer>();
    if( mob_container ) {
      oCItem* item = new oCItem();
      item->InitByScript( index, 1 );
      mob_container->Insert( item );
    }

    return 0;
  }
  
  int Mob_InsertItems() {
    zCParser* par = zCParser::GetParser();
    oCMOB* mob;
    int index;
    int count;
    par->GetParameter( count );
    par->GetParameter( index );
    mob = (oCMOB*)par->GetInstance();

    oCMobContainer* mob_container = mob->CastTo<oCMobContainer>();
    if( mob_container ) {
      oCItem* item = new oCItem();
      item->InitByScript( index, count );
      mob_container->Insert( item );
    }

    return 0;
  }

  int Mob_GetLockCombination() {
    zCParser* par = zCParser::GetParser();
    oCMOB* mob;
    mob = (oCMOB*)par->GetInstance();

    oCMobLockable* mob_lockable = mob->CastTo<oCMobContainer>();
    if( mob_lockable )
      par->SetReturn( mob_lockable->pickLockStr );

    return 0;
  }

  int Mob_SetLockCombination() {
    zCParser* par = zCParser::GetParser();
    oCMOB* mob;
    zSTRING combination;
    par->GetParameter( combination );
    mob = (oCMOB*)par->GetInstance();

    oCMobLockable* mob_lockable = mob->CastTo<oCMobContainer>();
    if( mob_lockable )
      mob_lockable->pickLockStr = combination;

    return 0;
  }

  int Mob_IsLocked() {
    zCParser* par = zCParser::GetParser();
    oCMOB* mob;
    mob = (oCMOB*)par->GetInstance();

    oCMobLockable* mob_lockable = mob->CastTo<oCMobContainer>();
    if( mob_lockable )
      par->SetReturn( mob_lockable->locked );

    return 0;
  }

  int Mob_SetLocked() {
    zCParser* par = zCParser::GetParser();
    oCMOB* mob;
    int locked;
    par->GetParameter( locked );
    mob = (oCMOB*)par->GetInstance();

    oCMobLockable* mob_lockable = mob->CastTo<oCMobContainer>();
    if( mob_lockable )
      mob_lockable->locked = locked;

    return 0;
  }

  int Mob_GetKeyInstance() {
    zCParser* par = zCParser::GetParser();
    oCMOB* mob;
    mob = (oCMOB*)par->GetInstance();

    oCMobLockable* mob_lockable = mob->CastTo<oCMobContainer>();
    if( mob_lockable ) {
      int index = par->GetIndex( mob_lockable->keyInstance );
      par->SetReturn( index );
    }

    return 0;
  }

  int Mob_SetKeyInstance() {
    zCParser* par = zCParser::GetParser();
    oCMOB* mob;
    int index;
    par->GetParameter( index );
    mob = (oCMOB*)par->GetInstance();

    oCMobLockable* mob_lockable = mob->CastTo<oCMobContainer>();
    if( mob_lockable ) {
      zCPar_Symbol* sym = par->GetSymbol( index );
      if( sym )
        mob_lockable->keyInstance = sym->name;
    }

    return 0;
  }

  int Hlp_MessageBox() {
    zCParser* par = zCParser::GetParser();
    zSTRING message;
    par->GetParameter( message );
    Message::Box( message, "Parser" );
    return 0;
  }



  /****************************************
  **********       NYX-CORE      **********
  ****************************************/

  /* D: func void Npc_ChangeIntAttributeEx(var C_NPC self, var string attr_name, var int value){}; */
  int Npc_ChangeIntAttributeEx() {
    zCParser* par = zCParser::GetParser();
    int value;
    par->GetParameter(value);
    zSTRING attr_name;
    par->GetParameter(attr_name);
    oCNpcEx* npc_ex = (oCNpcEx*)par->GetInstance();
    if (attr_name == "ATR_STRENGTH") {
      npc_ex->attribute[NPC_ATR_STRENGTH] += value;  // map to base attributes instead of attr, because of oCNpcEx::ProcessAttributes()
      npc_ex->attribute[NPC_ATR_STRENGTH] = (0 > npc_ex->attribute[NPC_ATR_STRENGTH]) ? 0 : npc_ex->attribute[NPC_ATR_STRENGTH];
    }
    else if (attr_name == "ATR_CONSTITUTION") {
      npc_ex->attr.Constitution += value;
      npc_ex->attr.Constitution = (0 > npc_ex->attr.Constitution) ? 0 : npc_ex->attr.Constitution;
    }
    else if (attr_name == "ATR_DEXTERITY") {
      npc_ex->attribute[NPC_ATR_DEXTERITY] += value;  // map to base attributes instead of attr, because of oCNpcEx::ProcessAttributes()
      npc_ex->attribute[NPC_ATR_DEXTERITY] = (0 > npc_ex->attribute[NPC_ATR_DEXTERITY]) ? 0 : npc_ex->attribute[NPC_ATR_DEXTERITY];
    }
    else if (attr_name == "ATR_WILL") {
      npc_ex->attr.Willpower += value;
      // convert to madness, if dropping below 0
      if (npc_ex->attr.Willpower < 0) {
        npc_ex->attr.Madness -= npc_ex->attr.Willpower;
        npc_ex->attr.Willpower = 0;
      }
    }
    else if (attr_name == "ATR_WILL_MAX") {
      npc_ex->attr.WillpowerMax += value;
      npc_ex->attr.WillpowerMax = (0 > npc_ex->attr.WillpowerMax) ? 0 : npc_ex->attr.WillpowerMax;
    }
    else if (attr_name == "ATR_MADNESS") {
      npc_ex->attr.Madness += value;
      // convert to willpower, if dropping below 0
      if (npc_ex->attr.Madness < 0) {
        npc_ex->attr.Willpower -= npc_ex->attr.Madness;
        npc_ex->attr.Madness = 0;
      }
    }
    else if (attr_name == "ATR_MADNESS_MAX") {
      npc_ex->attr.MadnessMax += value;
      npc_ex->attr.MadnessMax = (0 > npc_ex->attr.MadnessMax) ? 0 : npc_ex->attr.MadnessMax;
    }
    else if (attr_name == "ATR_NUTRITION") {
      npc_ex->attr.Nutrition += value;
      npc_ex->attr.Nutrition = (0 > npc_ex->attr.Nutrition) ? 0 : npc_ex->attr.Nutrition;
    }
    else if (attr_name == "ATR_NUTRITION_MAX") {
      npc_ex->attr.NutritionMax += value;
      npc_ex->attr.NutritionMax = (0 > npc_ex->attr.NutritionMax) ? 0 : npc_ex->attr.NutritionMax;
    }
    else if (attr_name == "ATR_STR2HP_SCALE") {
      npc_ex->attr.Strength2HitpointsScale += value;
      npc_ex->attr.Strength2HitpointsScale = (0 > npc_ex->attr.Strength2HitpointsScale) ? 0 : npc_ex->attr.Strength2HitpointsScale;
    }
    else if (attr_name == "ATR_HITPOINTS") {
      npc_ex->attribute[NPC_ATR_HITPOINTS] += value;  // map to base attributes instead of attr, because of oCNpcEx::ProcessAttributes()
      npc_ex->attribute[NPC_ATR_HITPOINTS] = (0 > npc_ex->attribute[NPC_ATR_HITPOINTS]) ? 0 : npc_ex->attribute[NPC_ATR_HITPOINTS];
    }
    else if (attr_name == "ATR_HITPOINTS_MAX") {
      npc_ex->attribute[NPC_ATR_HITPOINTSMAX] += value;  // map to base attributes instead of attr, because of oCNpcEx::ProcessAttributes()
      npc_ex->attribute[NPC_ATR_HITPOINTSMAX] = (0 > npc_ex->attribute[NPC_ATR_HITPOINTSMAX]) ? 0 : npc_ex->attribute[NPC_ATR_HITPOINTSMAX];
    }
    else if (attr_name == "ATR_CON2STA_SCALE") {
      npc_ex->attr.Constitution2StaminaScale += value;
      npc_ex->attr.Constitution2StaminaScale = (0 > npc_ex->attr.Constitution2StaminaScale) ? 0 : npc_ex->attr.Constitution2StaminaScale;
    }
    else if (attr_name == "ATR_STAMINA") {
      npc_ex->attr.Stamina += value;
      npc_ex->attr.Stamina = (0 > npc_ex->attr.Stamina) ? 0 : npc_ex->attr.Stamina;
    }
    else if (attr_name == "ATR_STAMINA_MAX") {
      npc_ex->attr.StaminaMax += value;
      npc_ex->attr.StaminaMax = (0 > npc_ex->attr.StaminaMax) ? 0 : npc_ex->attr.StaminaMax;
    }
    else if (attr_name == "ATR_MANA") {
      npc_ex->attribute[NPC_ATR_MANA] += value;  // map to base attributes instead of attr, because of oCNpcEx::ProcessAttributes()
      npc_ex->attribute[NPC_ATR_MANA] = (0 > npc_ex->attribute[NPC_ATR_MANA]) ? 0 : npc_ex->attribute[NPC_ATR_MANA];
    }
    else if (attr_name == "ATR_MANA_MAX") {
      npc_ex->attribute[NPC_ATR_MANAMAX] += value;  // map to base attributes instead of attr, because of oCNpcEx::ProcessAttributes()
      npc_ex->attribute[NPC_ATR_MANAMAX] = (0 > npc_ex->attribute[NPC_ATR_MANAMAX]) ? 0 : npc_ex->attribute[NPC_ATR_MANAMAX];
    }
    else if (attr_name == "ATR_TOXIN") {
      npc_ex->attr.Toxin += value;
      npc_ex->attr.Toxin = (0 > npc_ex->attr.Toxin) ? 0 : npc_ex->attr.Toxin;
    }
    else if (attr_name == "ATR_TOXIN_MAX") {
      npc_ex->attr.ToxinMax += value;
      npc_ex->attr.ToxinMax = (0 > npc_ex->attr.ToxinMax) ? 0 : npc_ex->attr.ToxinMax;
    }
    else if (attr_name == "ATR_RADIATION") {
      npc_ex->attr.Radiation += value;
      npc_ex->attr.Radiation = (0 > npc_ex->attr.Radiation) ? 0 : npc_ex->attr.Radiation;
    }
    else if (attr_name == "ATR_RADIATION_MAX") {
      npc_ex->attr.RadiationMax += value;
      npc_ex->attr.RadiationMax = (0 > npc_ex->attr.RadiationMax) ? 0 : npc_ex->attr.RadiationMax;
    }
    return 0;
  }

  /* D: func int Npc_GetIntAttributeEx(var C_NPC self, var string attr_name){}; */
  int Npc_GetIntAttributeEx() {
    zCParser* par = zCParser::GetParser();
    zSTRING attr_name;
    par->GetParameter(attr_name);
    oCNpcEx* npc_ex = (oCNpcEx*)par->GetInstance();
    int value;
    if (attr_name == "ATR_STRENGTH") {
      value = npc_ex->attr.Strength;
    }
    else if (attr_name == "ATR_CONSTITUTION") {
      value = npc_ex->attr.Constitution;
    }
    else if (attr_name == "ATR_DEXTERITY") {
      value = npc_ex->attr.Dexterity;
    }
    else if (attr_name == "ATR_WILL") {
      value = npc_ex->attr.Willpower;
    }
    else if (attr_name == "ATR_WILL_MAX") {
      value = npc_ex->attr.WillpowerMax;
    }
    else if (attr_name == "ATR_MADNESS") {
      value = npc_ex->attr.Madness;
    }
    else if (attr_name == "ATR_MADNESS_MAX") {
      value = npc_ex->attr.MadnessMax;
    }
    else if (attr_name == "ATR_NUTRITION") {
      value = npc_ex->attr.Nutrition;
    }
    else if (attr_name == "ATR_NUTRITION_MAX") {
      value = npc_ex->attr.NutritionMax;
    }
    else if (attr_name == "ATR_STR2HP_SCALE") {
      value = npc_ex->attr.Strength2HitpointsScale;
    }
    else if (attr_name == "ATR_HITPOINTS") {
      value = npc_ex->attr.Hitpoints;
    }
    else if (attr_name == "ATR_HITPOINTS_MAX") {
      value = npc_ex->attr.HitpointsMax;
    }
    else if (attr_name == "ATR_CON2STA_SCALE") {
      value = npc_ex->attr.Constitution2StaminaScale;
    }
    else if (attr_name == "ATR_STAMINA") {
      value = npc_ex->attr.Stamina;
    }
    else if (attr_name == "ATR_STAMINA_MAX") {
      value = npc_ex->attr.StaminaMax;
    }
    else if (attr_name == "ATR_MANA") {
      value = npc_ex->attr.Mana;
    }
    else if (attr_name == "ATR_MANA_MAX") {
      value = npc_ex->attr.ManaMax;
    }
    else if (attr_name == "ATR_TOXIN") {
      value = npc_ex->attr.Toxin;
    }
    else if (attr_name == "ATR_TOXIN_MAX") {
      value = npc_ex->attr.ToxinMax;
    }
    else if (attr_name == "ATR_RADIATION") {
      value = npc_ex->attr.Radiation;
    }
    else if (attr_name == "ATR_RADIATION_MAX") {
      value = npc_ex->attr.RadiationMax;
    }
    par->SetReturn(value);
    return 0;
  }

  /* D: func void Npc_GiveExperienceEx(var C_NPC self, var string exp_name, var int value){}; */
  int Npc_GiveExperienceEx() {
    zCParser* par = zCParser::GetParser();
    int value;
    par->GetParameter(value);
    zSTRING exp_name;
    par->GetParameter(exp_name);
    oCNpcEx* npc_ex = (oCNpcEx*)par->GetInstance();
    if (exp_name == "EXP_MARTIALARTS") {
      npc_ex->exp.Martialarts += value;
      npc_ex->exp.Martialarts = (0 > npc_ex->exp.Martialarts) ? 0 : npc_ex->exp.Martialarts;
    }
    else if (exp_name == "EXP_MARKSMANSHIP") {
      npc_ex->attribute[NPC_ATR_DEXTERITY] += value;  // map to base attributes instead of attr, because of hitchance scaling
      npc_ex->attribute[NPC_ATR_DEXTERITY] = (0 > npc_ex->attribute[NPC_ATR_DEXTERITY]) ? 0 : npc_ex->attribute[NPC_ATR_DEXTERITY];
    }
    else if (exp_name == "EXP_THIEVERY") {
      npc_ex->exp.Thievery += value;
      npc_ex->exp.Thievery = (0 > npc_ex->exp.Thievery) ? 0 : npc_ex->exp.Thievery;
    }
    else if (exp_name == "EXP_ARCANE") {
      npc_ex->exp.Arcane += value;
      npc_ex->exp.Arcane = (0 > npc_ex->exp.Arcane) ? 0 : npc_ex->exp.Arcane;
    }
    else if (exp_name == "EXP_ATHLETICS") {
      npc_ex->exp.Athletics += value;
      npc_ex->exp.Athletics = (0 > npc_ex->exp.Athletics) ? 0 : npc_ex->exp.Athletics;
    }
    else if (exp_name == "EXP_HUNTSMANSHIP") {
      npc_ex->exp.Huntsmanship += value;
      npc_ex->exp.Huntsmanship = (0 > npc_ex->exp.Huntsmanship) ? 0 : npc_ex->exp.Huntsmanship;
    }
    else if (exp_name == "EXP_METALLURGY") {
      npc_ex->exp.Metallurgy += value;
      npc_ex->exp.Metallurgy = (0 > npc_ex->exp.Metallurgy) ? 0 : npc_ex->exp.Metallurgy;
    }
    else if (exp_name == "EXP_ARMORY") {
      npc_ex->exp.Armory += value;
      npc_ex->exp.Armory = (0 > npc_ex->exp.Armory) ? 0 : npc_ex->exp.Armory;
    }
    else if (exp_name == "EXP_ALCHEMY") {
      npc_ex->exp.Alchemy += value;
      npc_ex->exp.Alchemy = (0 > npc_ex->exp.Alchemy) ? 0 : npc_ex->exp.Alchemy;
    }
    else if (exp_name == "EXP_PHILOLOGY") {
      npc_ex->exp.Philology += value;
      npc_ex->exp.Philology = (0 > npc_ex->exp.Philology) ? 0 : npc_ex->exp.Philology;
    }
    return 0;
  }

  /* D: func int Npc_GetExperienceEx(var C_NPC self, var string exp_name){}; */
  int Npc_GetExperienceEx() {
    zCParser* par = zCParser::GetParser();
    zSTRING exp_name;
    par->GetParameter(exp_name);
    oCNpcEx* npc_ex = (oCNpcEx*)par->GetInstance();
    int value;
    if (exp_name == "EXP_MARTIALARTS") {
      value = npc_ex->exp.Martialarts;
    }
    else if (exp_name == "EXP_MARKSMANSHIP") {
      value = npc_ex->exp.Marksmanship;
    }
    else if (exp_name == "EXP_THIEVERY") {
      value = npc_ex->exp.Thievery;
    }
    else if (exp_name == "EXP_ARCANE") {
      value = npc_ex->exp.Arcane;
    }
    else if (exp_name == "EXP_ATHLETICS") {
      value = npc_ex->exp.Athletics;
    }
    else if (exp_name == "EXP_HUNTSMANSHIP") {
      value = npc_ex->exp.Huntsmanship;
    }
    else if (exp_name == "EXP_METALLURGY") {
      value = npc_ex->exp.Metallurgy;
    }
    else if (exp_name == "EXP_ARMORY") {
      value = npc_ex->exp.Armory;
    }
    else if (exp_name == "EXP_ALCHEMY") {
      value = npc_ex->exp.Alchemy;
    }
    else if (exp_name == "EXP_PHILOLOGY") {
      value = npc_ex->exp.Philology;
    }
    par->SetReturn(value);
    return 0;
  }

  /* D: func void Npc_SetTalentEx(var C_NPC self, var string tal_name, var int value){}; */
  int Npc_SetTalentEx() {
    zCParser* par = zCParser::GetParser();
    int value;
    par->GetParameter(value);
    zSTRING tal_name;
    par->GetParameter(tal_name);
    oCNpcEx* npc_ex = (oCNpcEx*)par->GetInstance();
    // EXP_MARTIALARTS
    if (tal_name == "TAL_BRAWL") {
      npc_ex->skills.Brawl = value;
    }
    else if (tal_name == "TAL_DAGGER") {
      npc_ex->skills.Dagger = value;
    }
    else if (tal_name == "TAL_ASSASSIN") {
      npc_ex->skills.Assassin = value;
    }
    else if (tal_name == "TAL_1H_AXE") {
      npc_ex->skills.Axe1H = value;
    }
    else if (tal_name == "TAL_1H_SWORD") {
      npc_ex->skills.Sword1H = value;
    }
    else if (tal_name == "TAL_2H_AXE") {
      npc_ex->skills.Axe2H = value;
    }
    else if (tal_name == "TAL_2H_SWORD") {
      npc_ex->skills.Sword2H = value;
    }
    else if (tal_name == "TAL_SHIELD") {
      npc_ex->skills.Shield = value;
    }
    else if (tal_name == "TAL_STAFF") {
      npc_ex->skills.Staff = value;
    }
    // EXP_MARKSMANSHIP
    else if (tal_name == "TAL_BOW") {
      npc_ex->skills.Bow = value;
    }
    else if (tal_name == "TAL_XBOW") {
      npc_ex->skills.XBow = value;
    }
    // EXP_THIEVERY
    else if (tal_name == "TAL_SNEAK") {
      npc_ex->skills.Sneak = value;
    }
    else if (tal_name == "TAL_HIDE") {
      npc_ex->skills.Hide = value;
    }
    else if (tal_name == "TAL_PICKLOCK") {
      npc_ex->skills.Picklock = value;
    }
    else if (tal_name == "TAL_PICKPOCKET") {
      npc_ex->skills.Pickpocket = value;
    }
    else if (tal_name == "TAL_TRAPS") {
      npc_ex->skills.Traps = value;
    }
    else if (tal_name == "TAL_SEVENTHSENSE") {
      npc_ex->skills.SeventhSense = value;
    }
    else if (tal_name == "TAL_NIGHTSIGHT") {
      npc_ex->skills.NightSight = value;
    }
    // EXP_ARCANE
    else if (tal_name == "TAL_MANA") {
      npc_ex->skills.Mana = value;
    }
    else if (tal_name == "TAL_HEAL") {
      npc_ex->skills.Heal = value;
    }
    else if (tal_name == "TAL_MAGIC") {
      npc_ex->skills.MagicCircle = value;
    }
    else if (tal_name == "TAL_IDENTIFY") {
      npc_ex->skills.IdentifyMagic = value;
    }
    else if (tal_name == "TAL_SCROLLS") {
      npc_ex->skills.Scrolls = value;
    }
    else if (tal_name == "TAL_ENCHANTING") {
      npc_ex->skills.Enchanting = value;
    }
    else if (tal_name == "TAL_THAUMATURGY") {
      npc_ex->skills.Thaumaturgy = value;
    }
    else if (tal_name == "TAL_IRONWILL") {
      npc_ex->skills.IronWill = value;
    }
    else if (tal_name == "TAL_FIREMASTER") {
      npc_ex->skills.FireMaster = value;
    }
    else if (tal_name == "TAL_WATERMASTER") {
      npc_ex->skills.WaterMaster = value;
    }
    // EXP_ATHLETICS
    else if (tal_name == "TAL_THROW") {
      npc_ex->skills.Throw = value;
    }
    else if (tal_name == "TAL_RUN") {
      npc_ex->skills.Run = value;
    }
    else if (tal_name == "TAL_SPRINT") {
      npc_ex->skills.Sprint = value;
    }
    else if (tal_name == "TAL_CLIMB") {
      npc_ex->skills.Climb = value;
    }
    else if (tal_name == "TAL_SWIM") {
      npc_ex->skills.Swim = value;
    }
    else if (tal_name == "TAL_ACROBATICS") {
      npc_ex->skills.Acrobatics = value;
    }
    // EXP_HUNTSMANSHIP
    else if (tal_name == "TAL_TAKEMEAT") {
      npc_ex->skills.TakeMeat = value;
    }
    else if (tal_name == "TAL_SKIN") {
      npc_ex->skills.Skin = value;
    }
    else if (tal_name == "TAL_CLAWS") {
      npc_ex->skills.Claws = value;
    }
    else if (tal_name == "TAL_ARROWS") {
      npc_ex->skills.Arrows = value;
    }
    else if (tal_name == "TAL_BOWMAKER") {
      npc_ex->skills.BowMaker = value;
    }
    else if (tal_name == "TAL_TAMEANIMAL") {
      npc_ex->skills.TameAnimal = value;
    }
    // EXP_METALLURGY
    else if (tal_name == "TAL_DIG") {
      npc_ex->skills.Dig = value;
    }
    else if (tal_name == "TAL_SMITH") {
      npc_ex->skills.Smith = value;
    }
    else if (tal_name == "TAL_SMELTING") {
      npc_ex->skills.Smelting = value;
    }
    else if (tal_name == "TAL_JEWELRY") {
      npc_ex->skills.Jewelry = value;
    }
    // EXP_ARMORY
    else if (tal_name == "TAL_TAN") {
      npc_ex->skills.Tan = value;
    }
    else if (tal_name == "TAL_PATCH") {
    npc_ex->skills.Patch = value;
    }
    else if (tal_name == "TAL_ARMOR") {
      npc_ex->skills.Armor = value;
    }
    // EXP_ALCHEMY
    else if (tal_name == "TAL_COOKING") {
      npc_ex->skills.Cooking = value;
    }
    else if (tal_name == "TAL_HERBS") {
      npc_ex->skills.Herbs = value;
    }
    else if (tal_name == "TAL_MUSHROOMS") {
      npc_ex->skills.Mushrooms = value;
    }
    else if (tal_name == "TAL_ALCHEMY") {
      npc_ex->skills.Alchemy = value;
    }
    else if (tal_name == "TAL_EXPLOSIVES") {
      npc_ex->skills.Explosives = value;
    }
    // EXP_PHILOLOGY
    else if (tal_name == "TAL_SPEAKORC") {
      npc_ex->skills.SpeakOrc = value;
    }
    else if (tal_name == "TAL_SPEAKMORA") {
      npc_ex->skills.SpeakMora = value;
    }
    return 0;
  }
 
  /* D: func int Npc_GetTalentEx(var C_NPC self, var string tal_name){}; */
  int Npc_GetTalentEx() {
    zCParser* par = zCParser::GetParser();
    zSTRING tal_name;
    par->GetParameter(tal_name);
    oCNpcEx* npc_ex = (oCNpcEx*)par->GetInstance();
    int value;
    // EXP_MARTIALARTS
    if (tal_name == "TAL_BRAWL") {
      value = npc_ex->skills.Brawl;
    }
    else if (tal_name == "TAL_DAGGER") {
      value = npc_ex->skills.Dagger;
    }
    else if (tal_name == "TAL_ASSASSIN") {
      value = npc_ex->skills.Assassin;
    }
    else if (tal_name == "TAL_1H_AXE") {
      value = npc_ex->skills.Axe1H;
    }
    else if (tal_name == "TAL_1H_SWORD") {
      value = npc_ex->skills.Sword1H;
    }
    else if (tal_name == "TAL_2H_AXE") {
      value = npc_ex->skills.Axe2H;
    }
    else if (tal_name == "TAL_2H_SWORD") {
      value = npc_ex->skills.Sword2H;
    }
    else if (tal_name == "TAL_SHIELD") {
      value = npc_ex->skills.Shield;
    }
    else if (tal_name == "TAL_STAFF") {
      value = npc_ex->skills.Staff;
    }
    // EXP_MARKSMANSHIP
    else if (tal_name == "TAL_BOW") {
      value = npc_ex->skills.Bow;
    }
    else if (tal_name == "TAL_XBOW") {
      value = npc_ex->skills.XBow;
    }
    // EXP_THIEVERY
    else if (tal_name == "TAL_SNEAK") {
      value = npc_ex->skills.Sneak;
    }
    else if (tal_name == "TAL_HIDE") {
      value = npc_ex->skills.Hide;
    }
    else if (tal_name == "TAL_PICKLOCK") {
      value = npc_ex->skills.Picklock;
    }
    else if (tal_name == "TAL_PICKPOCKET") {
      value = npc_ex->skills.Pickpocket;
    }
    else if (tal_name == "TAL_TRAPS") {
      value = npc_ex->skills.Traps;
    }
    else if (tal_name == "TAL_SEVENTHSENSE") {
      value = npc_ex->skills.SeventhSense;
    }
    else if (tal_name == "TAL_NIGHTSIGHT") {
      value = npc_ex->skills.NightSight;
    }
    // EXP_ARCANE
    else if (tal_name == "TAL_MANA") {
      value = npc_ex->skills.Mana;
    }
    else if (tal_name == "TAL_HEAL") {
      value = npc_ex->skills.Heal;
    }
    else if (tal_name == "TAL_MAGIC") {
      value = npc_ex->skills.MagicCircle;
    }
    else if (tal_name == "TAL_IDENTIFY") {
      value = npc_ex->skills.IdentifyMagic;
    }
    else if (tal_name == "TAL_SCROLLS") {
      value = npc_ex->skills.Scrolls;
    }
    else if (tal_name == "TAL_ENCHANTING") {
      value = npc_ex->skills.Enchanting;
    }
    else if (tal_name == "TAL_THAUMATURGY") {
      value = npc_ex->skills.Thaumaturgy;
    }
    else if (tal_name == "TAL_IRONWILL") {
      value = npc_ex->skills.IronWill;
    }
    else if (tal_name == "TAL_FIREMASTER") {
      value = npc_ex->skills.FireMaster;
    }
    else if (tal_name == "TAL_WATERMASTER") {
      value = npc_ex->skills.WaterMaster;
    }
    // EXP_ATHLETICS
    else if (tal_name == "TAL_THROW") {
      value = npc_ex->skills.Throw;
    }
    else if (tal_name == "TAL_RUN") {
      value = npc_ex->skills.Run;
    }
    else if (tal_name == "TAL_SPRINT") {
      value = npc_ex->skills.Sprint;
    }
    else if (tal_name == "TAL_CLIMB") {
      value = npc_ex->skills.Climb;
    }
    else if (tal_name == "TAL_SWIM") {
    value = npc_ex->skills.Swim;
    }
    else if (tal_name == "TAL_ACROBATICS") {
    value = npc_ex->skills.Acrobatics;
    }
    // EXP_HUNTSMANSHIP
    else if (tal_name == "TAL_TAKEMEAT") {
    value = npc_ex->skills.TakeMeat;
    }
    else if (tal_name == "TAL_SKIN") {
    value = npc_ex->skills.Skin;
    }
    else if (tal_name == "TAL_CLAWS") {
    value = npc_ex->skills.Claws;
    }
    else if (tal_name == "TAL_ARROWS") {
    value = npc_ex->skills.Arrows;
    }
    else if (tal_name == "TAL_BOWMAKER") {
    value = npc_ex->skills.BowMaker;
    }
    else if (tal_name == "TAL_TAMEANIMAL") {
    value = npc_ex->skills.TameAnimal;
    }
    // EXP_METALLURGY
    else if (tal_name == "TAL_DIG") {
    value = npc_ex->skills.Dig;
    }
    else if (tal_name == "TAL_SMITH") {
    value = npc_ex->skills.Smith;
    }
    else if (tal_name == "TAL_SMELTING") {
    value = npc_ex->skills.Smelting;
    }
    else if (tal_name == "TAL_JEWELRY") {
    value = npc_ex->skills.Jewelry;
    }
    // EXP_ARMORY
    else if (tal_name == "TAL_TAN") {
    value = npc_ex->skills.Tan;
    }
    else if (tal_name == "TAL_PATCH") {
    value = npc_ex->skills.Patch;
    }
    else if (tal_name == "TAL_ARMOR") {
    value = npc_ex->skills.Armor;
    }
    // EXP_ALCHEMY
    else if (tal_name == "TAL_COOKING") {
    value = npc_ex->skills.Cooking;
    }
    else if (tal_name == "TAL_HERBS") {
    value = npc_ex->skills.Herbs;
    }
    else if (tal_name == "TAL_MUSHROOMS") {
    value = npc_ex->skills.Mushrooms;
    }
    else if (tal_name == "TAL_ALCHEMY") {
    value = npc_ex->skills.Alchemy;
    }
    else if (tal_name == "TAL_EXPLOSIVES") {
    value = npc_ex->skills.Explosives;
    }
    // EXP_PHILOLOGY
    else if (tal_name == "TAL_SPEAKORC") {
    value = npc_ex->skills.SpeakOrc;
    }
    else if (tal_name == "TAL_SPEAKMORA") {
    value = npc_ex->skills.SpeakMora;
    }
    par->SetReturn(value);
    return 0;
  }


  void DefineExternals() {
    // CAST
    parser->DefineExternal( "Cast_PointerToInstance",    Cast_PointerToInstance,    zPAR_TYPE_INSTANCE, zPAR_TYPE_INT,      0 );
    parser->DefineExternal( "Cast_PointerToNpc",         Cast_PointerToInstance,    zPAR_TYPE_INSTANCE, zPAR_TYPE_INT,      0 );
    parser->DefineExternal( "Cast_PointerToItem",        Cast_PointerToInstance,    zPAR_TYPE_INSTANCE, zPAR_TYPE_INT,      0 );
    parser->DefineExternal( "Cast_InstanceToPointer",    Cast_InstanceToPointer,    zPAR_TYPE_INT,      zPAR_TYPE_INSTANCE, 0 );
    parser->DefineExternal( "Cast_InstanceIsItem",       Cast_InstanceIsItem,       zPAR_TYPE_INT,      zPAR_TYPE_INSTANCE, 0 );
    parser->DefineExternal( "Cast_InstanceIsMob",        Cast_InstanceIsMob,        zPAR_TYPE_INT,      zPAR_TYPE_INSTANCE, 0 );
    parser->DefineExternal( "Cast_GetInstanceIndex",     Cast_GetInstanceIndex,     zPAR_TYPE_INT,      zPAR_TYPE_INSTANCE, 0 );

    // HLP
    parser->DefineExternal( "Hlp_HasFocusVob",           Hlp_HasFocusVob,           zPAR_TYPE_INT,      zPAR_TYPE_INSTANCE, 0 );
    parser->DefineExternal( "Hlp_GetFocusVob",           Hlp_GetFocusVob,           zPAR_TYPE_INSTANCE, zPAR_TYPE_INSTANCE, 0 );
    parser->DefineExternal( "Hlp_GetFocusVobName",       Hlp_GetFocusVobName,       zPAR_TYPE_STRING,   zPAR_TYPE_INSTANCE, 0 );
    parser->DefineExternal( "Hlp_GetStringLength",       Hlp_GetStringLength,       zPAR_TYPE_INT,      zPAR_TYPE_STRING,   0 );
    parser->DefineExternal( "Hlp_IsNAN",                 Hlp_IsNAN,                 zPAR_TYPE_INT,      zPAR_TYPE_FLOAT,    0 );
    parser->DefineExternal( "Hlp_KeyToggled",            Hlp_KeyToggled,            zPAR_TYPE_INT,      zPAR_TYPE_INT,      0 );
    parser->DefineExternal( "Hlp_KeyPressed",            Hlp_KeyPressed,            zPAR_TYPE_INT,      zPAR_TYPE_INT,      0 );
    parser->DefineExternal( "Hlp_LogicalKeyToggled",     Hlp_LogicalKeyToggled,     zPAR_TYPE_INT,      zPAR_TYPE_INT,      0 );
    parser->DefineExternal( "Hlp_GameOnPause",           Hlp_GameOnPause,           zPAR_TYPE_INT,      0 );
    parser->DefineExternal( "Hlp_MessageBox",            Hlp_MessageBox,            zPAR_TYPE_VOID,     zPAR_TYPE_STRING,   0 );

    // WLD
    parser->DefineExternal( "Wld_ChangeLevel",           Wld_ChangeLevel,           zPAR_TYPE_VOID,     zPAR_TYPE_STRING,   zPAR_TYPE_STRING,   0 );
    parser->DefineExternal( "Wld_FindVob",               Wld_FindVob,               zPAR_TYPE_INSTANCE, zPAR_TYPE_STRING,   0 );
    parser->DefineExternal( "Wld_PlayEffectVob",         Wld_PlayEffectVob,         zPAR_TYPE_VOID,     zPAR_TYPE_STRING,   zPAR_TYPE_INSTANCE, zPAR_TYPE_INT, zPAR_TYPE_INT, zPAR_TYPE_INT, zPAR_TYPE_INT, 0 );
    parser->DefineExternal( "Wld_PlayEffectAt",          Wld_PlayEffectAt,          zPAR_TYPE_VOID,     zPAR_TYPE_STRING,   zPAR_TYPE_INSTANCE, zPAR_TYPE_INT, zPAR_TYPE_INT, zPAR_TYPE_INT, zPAR_TYPE_INT, 0 );
    parser->DefineExternal( "Wld_ToggleRain",            Wld_ToggleRain,            zPAR_TYPE_VOID,     zPAR_TYPE_FLOAT,    zPAR_TYPE_FLOAT,    0 );
    parser->DefineExternal( "Wld_SetWeatherType",        Wld_SetWeatherType,        zPAR_TYPE_VOID,     zPAR_TYPE_INT,      0 );
    parser->DefineExternal( "Wld_GetWeatherType",        Wld_GetWeatherType,        zPAR_TYPE_INT,      0 );

    // MDL
    parser->DefineExternal( "Mdl_GetAnimationIndex",     Mdl_GetAnimationIndex,     zPAR_TYPE_INT,      zPAR_TYPE_INSTANCE, zPAR_TYPE_STRING,   0 );
    parser->DefineExternal( "Mdl_GetAnimationName",      Mdl_GetAnimationName,      zPAR_TYPE_STRING,   zPAR_TYPE_INSTANCE, zPAR_TYPE_INT,      0 );
    parser->DefineExternal( "Mdl_AnimationIsExists",     Mdl_AnimationIsExists,     zPAR_TYPE_INT,      zPAR_TYPE_INSTANCE, zPAR_TYPE_INT,      0 );
    parser->DefineExternal( "Mdl_AnimationIsActive",     Mdl_AnimationIsActive,     zPAR_TYPE_INT,      zPAR_TYPE_INSTANCE, zPAR_TYPE_INT,      0 );
    parser->DefineExternal( "Mdl_SetAllAnimationsFPS",   Mdl_SetAllAnimationsFPS,   zPAR_TYPE_VOID,     zPAR_TYPE_INSTANCE, zPAR_TYPE_FLOAT,    0 );
    parser->DefineExternal( "Mdl_ResetAllAnimationsFPS", Mdl_ResetAllAnimationsFPS, zPAR_TYPE_VOID,     zPAR_TYPE_INSTANCE, 0 );
    parser->DefineExternal( "Mdl_SetAnimationFPS",       Mdl_SetAnimationFPS,       zPAR_TYPE_VOID,     zPAR_TYPE_INSTANCE, zPAR_TYPE_INT,      zPAR_TYPE_FLOAT,    0 );
    parser->DefineExternal( "Mdl_ResetAnimationFPS",     Mdl_ResetAnimationFPS,     zPAR_TYPE_VOID,     zPAR_TYPE_INSTANCE, zPAR_TYPE_INT,      0 );
    parser->DefineExternal( "Mdl_SetVisible",            Mdl_SetVisible,            zPAR_TYPE_VOID,     zPAR_TYPE_INSTANCE, zPAR_TYPE_INT,      0 );

    // NPC
    parser->DefineExternal( "Npc_SetAsHero",             Npc_SetAsHero,             zPAR_TYPE_VOID,     zPAR_TYPE_INSTANCE, 0 );
    parser->DefineExternal( "Npc_OpenInventory",         Npc_OpenInventory,         zPAR_TYPE_VOID,     zPAR_TYPE_INSTANCE, 0 );
    parser->DefineExternal( "Npc_OpenInventorySteal",    Npc_OpenInventorySteal,    zPAR_TYPE_VOID,     zPAR_TYPE_INSTANCE, 0 );
    parser->DefineExternal( "Npc_OpenInventoryTrade",    Npc_OpenInventoryTrade,    zPAR_TYPE_VOID,     zPAR_TYPE_INSTANCE, 0 );
    // NYX-CORE
    parser->DefineExternal("Npc_ChangeIntAttributeEx", Npc_ChangeIntAttributeEx, zPAR_TYPE_VOID,    zPAR_TYPE_INSTANCE, zPAR_TYPE_STRING, zPAR_TYPE_INT, 0);
    parser->DefineExternal("Npc_GetIntAttributeEx", Npc_GetIntAttributeEx, zPAR_TYPE_INT, zPAR_TYPE_INSTANCE, zPAR_TYPE_STRING, 0);
    parser->DefineExternal("Npc_GiveExperienceEx", Npc_GiveExperienceEx, zPAR_TYPE_VOID, zPAR_TYPE_INSTANCE, zPAR_TYPE_STRING, zPAR_TYPE_INT, 0);
    parser->DefineExternal("Npc_GetExperienceEx", Npc_GetExperienceEx, zPAR_TYPE_INT, zPAR_TYPE_INSTANCE, zPAR_TYPE_STRING, 0);
    parser->DefineExternal("Npc_SetTalentEx", Npc_SetTalentEx, zPAR_TYPE_VOID, zPAR_TYPE_INSTANCE, zPAR_TYPE_STRING, zPAR_TYPE_INT, 0);
    parser->DefineExternal("Npc_GetTalentEx", Npc_GetTalentEx, zPAR_TYPE_INT, zPAR_TYPE_INSTANCE, zPAR_TYPE_STRING, 0);

    // MOB
    parser->DefineExternal( "Mob_Destroy",               Mob_Destroy,               zPAR_TYPE_VOID,     zPAR_TYPE_INSTANCE, 0 );
    parser->DefineExternal( "Mob_RemoveItem",            Mob_RemoveItem,            zPAR_TYPE_VOID,     zPAR_TYPE_INSTANCE, zPAR_TYPE_INT,      0 );
    parser->DefineExternal( "Mob_RemoveItems",           Mob_RemoveItems,           zPAR_TYPE_VOID,     zPAR_TYPE_INSTANCE, zPAR_TYPE_INT,      zPAR_TYPE_INT,      0 );
    parser->DefineExternal( "Mob_InsertItem",            Mob_InsertItem,            zPAR_TYPE_VOID,     zPAR_TYPE_INSTANCE, zPAR_TYPE_INT,      0 );
    parser->DefineExternal( "Mob_InsertItems",           Mob_InsertItems,           zPAR_TYPE_VOID,     zPAR_TYPE_INSTANCE, zPAR_TYPE_INT,      zPAR_TYPE_INT,      0 );
    parser->DefineExternal( "Mob_GetLockCombination",    Mob_GetLockCombination,    zPAR_TYPE_STRING,   zPAR_TYPE_INSTANCE, 0 );
    parser->DefineExternal( "Mob_SetLockCombination",    Mob_SetLockCombination,    zPAR_TYPE_VOID,     zPAR_TYPE_INSTANCE, zPAR_TYPE_STRING,   0 );
    parser->DefineExternal( "Mob_IsLocked",              Mob_IsLocked,              zPAR_TYPE_INT,      zPAR_TYPE_INSTANCE, 0 );
    parser->DefineExternal( "Mob_SetLocked",             Mob_SetLocked,             zPAR_TYPE_VOID,     zPAR_TYPE_INSTANCE, zPAR_TYPE_INT,      0 );
    parser->DefineExternal( "Mob_GetKeyInstance",        Mob_GetKeyInstance,        zPAR_TYPE_INT,      zPAR_TYPE_INSTANCE, 0 );
    parser->DefineExternal( "Mob_SetKeyInstance",        Mob_SetKeyInstance,        zPAR_TYPE_VOID,     zPAR_TYPE_INSTANCE, zPAR_TYPE_INT,      0 );

    // OTHER
    static float fNan  = NAN;
    static void* pNull = Null;
    parser->DefineExternalVar( "NAN",  &fNan,  zPAR_TYPE_FLOAT,    1 );
    parser->DefineExternalVar( "NULL", &pNull, zPAR_TYPE_INSTANCE, 1 );
  }

  void GameLoop() {
    int loop_index = parser->GetIndex( "GameLoop" );
    if( loop_index != -1 )
      parser->CallFunc( loop_index );
  }

  void GameInit() {
    int init_index = parser->GetIndex( "GameInit" );
    if( init_index != -1 )
      parser->CallFunc( init_index );
  }
}
#include <UnionAfx.h>
#include "oCGameEx.h"
#include "oCNpcEx.h"

namespace Gothic_I_Classic {
  oCGameEx::oCGameEx() {
    // set additional HUD elements
    staminaBar = NULL;
    willpowerBar = NULL;
    madnessBar = NULL;
    toxinBar = NULL;
    radiationBar = NULL;
  }

  oCGameEx::~oCGameEx() {
    // deallocate additional HUD elements
    if (staminaBar) {
      screen->RemoveItem(staminaBar);
      delete staminaBar;
      staminaBar = NULL;
    }
    if (willpowerBar) {
      screen->RemoveItem(willpowerBar);
      delete willpowerBar;
      willpowerBar = NULL;
    }
    if (madnessBar) {
      screen->RemoveItem(madnessBar);
      delete madnessBar;
      madnessBar = NULL;
    }
    if (toxinBar) {
      screen->RemoveItem(toxinBar);
      delete toxinBar;
      toxinBar = NULL;
    }
    if (radiationBar) {
      screen->RemoveItem(radiationBar);
      delete radiationBar;
      radiationBar = NULL;
    }
    // deallocate global pointer to singleton instance
    //if (ogame_ex == this) {
    //  ogame_ex = NULL;
    //}
  }

  void oCGameEx::Done() {
    // deallocate additional HUD elements
    if (staminaBar) {
      screen->RemoveItem(staminaBar);
      delete staminaBar;
      staminaBar = NULL;
    }
    if (willpowerBar) {
      screen->RemoveItem(willpowerBar);
      delete willpowerBar;
      willpowerBar = NULL;
    }
    if (madnessBar) {
      screen->RemoveItem(madnessBar);
      delete madnessBar;
      madnessBar = NULL;
    }
    if (toxinBar) {
      screen->RemoveItem(toxinBar);
      delete toxinBar;
      toxinBar = NULL;
    }
    if (radiationBar) {
      screen->RemoveItem(radiationBar);
      delete radiationBar;
      radiationBar = NULL;
    }
  }

  void oCGameEx::Init() {
    /* 
    HUD bars 
    left (100, 7800 | 7600), body: ogame->hpBar, ogame_ex->staminaBar | ogame->swimBar
    center (2900, 7800 | 7600), env: ogame_ex->toxinBar, ogame_ex->radiationBar
    right (5700, 7800 | 7600), magic: ogame_ex->willpowerBar | ogame_ex->madnessBar, ogame->manaBar
    */

    // body
    staminaBar = new oCViewStatusBar();
    screen->InsertItem(staminaBar);
    staminaBar->Init(45, 7700, 1.0);
    staminaBar->SetTextures("BAR_back.tga", "BAR_tempmax.tga", "BAR_misc.tga");
    staminaBar->SetMaxRange(0.0, 30.0);
    screen->RemoveItem(staminaBar);

    toxinBar = new oCViewStatusBar();
    screen->InsertItem(toxinBar);
    toxinBar->Init(45, 7800, 1.0);
    toxinBar->SetTextures("BAR_back.tga", "BAR_tempmax.tga", "BAR_poison.tga");
    toxinBar->SetMaxRange(0.0, 30.0);
    screen->RemoveItem(toxinBar);

    // health bar (45, 7900, 1.0)

    // magic

    willpowerBar = new oCViewStatusBar();  // replaces madness
    screen->InsertItem(willpowerBar);
    willpowerBar->Init(5700, 7700, 1.0);
    willpowerBar->SetTextures("BAR_back.tga", "BAR_tempmax.tga", "BAR_will.tga");
    willpowerBar->SetMaxRange(0.0, 30.0);
    screen->RemoveItem(willpowerBar);

    madnessBar = new oCViewStatusBar();  // replaces willpower
    screen->InsertItem(madnessBar);
    madnessBar->Init(5700, 7700, 1.0);
    madnessBar->SetTextures("BAR_back.tga", "BAR_tempmax.tga", "BAR_madness.tga");
    madnessBar->SetMaxRange(0.0, 30.0);
    screen->RemoveItem(madnessBar);

    radiationBar = new oCViewStatusBar();
    screen->InsertItem(radiationBar);
    radiationBar->Init(5700, 7800, 1.0);
    radiationBar->SetTextures("BAR_back.tga", "BAR_tempmax.tga", "BAR_radiation.tga");
    radiationBar->SetMaxRange(0.0, 30.0);
    screen->RemoveItem(radiationBar);

    // mana bar
  }

  void OGameExInit() {
    ogame_ex = new oCGameEx();
    ogame_ex->Init();
  }

  void OGameExHudLoop() {
    oCNpcEx*& ptr_player = *(oCNpcEx**)0x008DBBB0;  // TODO: make new standard reference -> utils
    TNpcAttributes attr = ptr_player->attr;
    // compute bar values
    // TODO: health
    if (attr.Stamina != attr.StaminaMax) {  // stamina
      ogame_ex->staminaBar->SetMaxRange(0, attr.StaminaMax);
      ogame_ex->staminaBar->SetRange(0, attr.StaminaMax);
      ogame_ex->staminaBar->SetValue(attr.Stamina);
    }
    if (attr.Toxin != 0) {  // toxin
      ogame_ex->toxinBar->SetMaxRange(0, attr.ToxinMax);
      ogame_ex->toxinBar->SetRange(0, attr.ToxinMax);
      ogame_ex->toxinBar->SetValue(attr.Toxin);
    }
    // TODO: mana
    if (attr.Madness != 0) {  // madness
      ogame_ex->madnessBar->SetMaxRange(0, attr.MadnessMax);
      ogame_ex->madnessBar->SetRange(0, attr.MadnessMax);
      ogame_ex->madnessBar->SetValue(attr.Madness);
    }
    if (attr.Radiation != 0) {  // radiation
      ogame_ex->radiationBar->SetMaxRange(0, attr.RadiationMax);
      ogame_ex->radiationBar->SetRange(0, attr.RadiationMax);
      ogame_ex->radiationBar->SetValue(attr.Radiation);
    }
    // bar rendering left / body (back to front): stamina, toxin, health
    if (attr.Stamina != attr.StaminaMax) {
      screen->InsertItem(ogame_ex->staminaBar);
      ogame_ex->staminaBar->Render();
      screen->RemoveItem(ogame_ex->staminaBar);
    }
    if (attr.Toxin != 0) {
      screen->InsertItem(ogame_ex->toxinBar);
      ogame_ex->toxinBar->Render();
      screen->RemoveItem(ogame_ex->toxinBar);
    }
    // TODO: health bar
    // bar rendering right / mind (back to front): madness, radiation, mana
    if (attr.Madness != 0) {
      screen->InsertItem(ogame_ex->madnessBar);
      ogame_ex->madnessBar->Render();
      screen->RemoveItem(ogame_ex->madnessBar);
    }
    if (attr.Radiation != 0) {
      screen->InsertItem(ogame_ex->radiationBar);
      ogame_ex->radiationBar->Render();
      screen->RemoveItem(ogame_ex->radiationBar);
    }
    // TODO: mana bar
  }
}


/* externals to call in Application.cpp, forward to specific engine version */

void OGameEx_Init() {
  Gothic_I_Classic::OGameExInit();
}

void OGameEx_HudLoop() {
  Gothic_I_Classic::OGameExHudLoop();
}


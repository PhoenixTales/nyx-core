#include <UnionAfx.h>
#include "oCNpcEx.h"

#ifdef __G1
namespace Gothic_I_Classic {

    void PrintScreen() {
        oCNpc* focusNpc = player->GetFocusNpc();
        if (focusNpc) {
            zSTRING npcName = focusNpc->GetName(0);
            screen->PrintCXY(npcName);
        }
    }

    void PrintCharacterScreen() {
        /*
        Simple screen print of character statistics.
        */
        oCNpcEx*& ptr_player = *(oCNpcEx**)0x008DBBB0;  // TODO: make new standard reference
        // TODO: replace with zinput->KeyPressed()
        zCOLOR COLOR_DEBUG(255, 255, 255, 255);
        if (GetKeyState('P') & 0x8000/*Check if high-order bit is set (1 << 15)*/) {
          // base attributes
          screen->Print(  45,  100, "ATR_STRENGTH:     " + zSTRING(ptr_player->attr.Strength));
          screen->Print(  45,  240, "ATR_CONSTITUTION: " + zSTRING(ptr_player->attr.Constitution));
          screen->Print(  45,  380, "ATR_WILL:         " + zSTRING(ptr_player->attr.Willpower) + " / " + zSTRING(ptr_player->attr.WillpowerMax));
          screen->Print(  45,  520, "ATR_MADNESS:      " + zSTRING(ptr_player->attr.Madness) + " / " + zSTRING(ptr_player->attr.MadnessMax));
          // consumable attributes
          screen->Print(2045,  100, "ATR_NUTRITION:    " + zSTRING(ptr_player->attr.Nutrition) + " / " + zSTRING(ptr_player->attr.NutritionMax));
          screen->Print(2045,  240, "ATR_HITPOINTS:    " + zSTRING(ptr_player->attr.Hitpoints) + " / " + zSTRING(ptr_player->attr.HitpointsMax));
          screen->Print(2045,  380, "ATR_STAMINA:      " + zSTRING(ptr_player->attr.Stamina) + " / " + zSTRING(ptr_player->attr.StaminaMax));
          screen->Print(2045,  520, "ATR_MANA:         " + zSTRING(ptr_player->attr.Mana) + " / " + zSTRING(ptr_player->attr.ManaMax));
          screen->Print(2045,  660, "ATR_TOXIN:        " + zSTRING(ptr_player->attr.Toxin) + " / " + zSTRING(ptr_player->attr.ToxinMax));
          // player experience
          screen->Print(4045,  100, "EXP_MARTIALARTS:  " + zSTRING(ptr_player->exp.Martialarts));
          screen->Print(4045,  240, "EXP_MARKSMANSHIP: " + zSTRING(ptr_player->exp.Marksmanship));
          screen->Print(4045,  380, "EXP_THIEVERY:     " + zSTRING(ptr_player->exp.Thievery));
          screen->Print(4045,  520, "EXP_ARCANE:       " + zSTRING(ptr_player->exp.Arcane));
          screen->Print(4045,  640, "EXP_ATHLETICS:    " + zSTRING(ptr_player->exp.Athletics));
          screen->Print(4045,  780, "EXP_HUNTSMANSHIP: " + zSTRING(ptr_player->exp.Huntsmanship));
          screen->Print(4045,  920, "EXP_METALLURGY:   " + zSTRING(ptr_player->exp.Metallurgy));
          screen->Print(4045, 1060, "EXP_ARMORY:       " + zSTRING(ptr_player->exp.Armory));
          screen->Print(4045, 1200, "EXP_ALCHEMY:      " + zSTRING(ptr_player->exp.Alchemy));
          screen->Print(4045, 1340, "EXP_PHILOLOGY:    " + zSTRING(ptr_player->exp.Philology));
        }
        //if (zinput->KeyPressed('P')) {
        //    screen->PrintCXY("Key 'P' is pressed!");
        //}
    }

}
#endif

void LoopPrintScreen() {
    TEngineVersion engineVersion = Union.GetEngineVersion();

#ifdef __G1
    if (engineVersion == Engine_G1) {
        //Gothic_I_Classic::PrintScreen();
        Gothic_I_Classic::PrintCharacterScreen();
    }
#endif
}

#include "UnionAfx.h"
#include "Interface_HeaderInclusion.h"

#include "ParserExtender.h"


// Plugin Tutorial
string GetEngineVersionName(TEngineVersion version) {
    switch (version) {
    case Engine_G1:  return "Gothic I Classic";
    case Engine_G1A: return "Gothic I Addon";
    case Engine_G2:  return "Gothic II Classic";
    case Engine_G2A: return "Gothic II Addon";
    }
    return "Unknown";
}

// zParserExtender
extern bool ParseExternals = false;


void Game_Entry() {
}

extern void OGameEx_Init();
void Game_Init() {
  // Plugin Tutorial
  // We get a pointer to the current plugin and get its name
  const CPlugin* plugin = CPlugin::GetCurrentPlugin();
  string pluginName = plugin->GetName();
  // Get the instance version of the union and convert it to a text string.
  TVersion unionVersion = Union.GetUnionVersion();
  string unionVersionName = unionVersion.ToString();
  // Get the version of the engine and its name
  TEngineVersion engineVersion = Union.GetEngineVersion();
  string engineVersionName = GetEngineVersionName(engineVersion);
  // Show a message on the screen
  //Message::Info(string::Combine(
  //    "Plugin name: %s\nUnion version: %s\nEngine version: %s",
  //    pluginName,
  //    unionVersionName,
  //    engineVersionName
  //    ));

  // nyx-core
  OGameEx_Init();

  // zParserExtender
  ParseExternals = true;
#ifdef __G1
  if( Union.GetEngineVersion() == Engine_G1 ) {
    Gothic_I_Classic::ParseExternalScripts();
    Gothic_I_Classic::GameInit();
  }
#endif
//#ifdef __G1A
//  if( Union.GetEngineVersion() == Engine_G1A ) {
//    Gothic_I_Addon::ParseExternalScripts();
//    Gothic_I_Addon::GameInit();
//  }
//#endif
//#ifdef __G2
//  if( Union.GetEngineVersion() == Engine_G2 ) {
//    Gothic_II_Classic::ParseExternalScripts();
//    Gothic_II_Classic::GameInit();
//  }
//#endif
//#ifdef __G2A
//  if( Union.GetEngineVersion() == Engine_G2A ) {
//    Gothic_II_Addon::ParseExternalScripts();
//    Gothic_II_Addon::GameInit();
//  }
//#endif
  ParseExternals = false;
}

void Game_Exit() {
}

extern void OGameEx_HudLoop();
extern void LoopPrintScreen();
void Game_Loop() {
  // zParserExtender
#ifdef __G1
  if( Union.GetEngineVersion() == Engine_G1 )
    Gothic_I_Classic::GameLoop();
#endif
//#ifdef __G1A
//  if( Union.GetEngineVersion() == Engine_G1A )
//    Gothic_I_Addon::GameLoop();
//#endif
//#ifdef __G2
//  if( Union.GetEngineVersion() == Engine_G2 )
//    Gothic_II_Classic::GameLoop();
//#endif
//#ifdef __G2A
//  if( Union.GetEngineVersion() == Engine_G2A )
//    Gothic_II_Addon::GameLoop();
//#endif

  // nyx-core
  OGameEx_HudLoop();
  LoopPrintScreen();  // DEBUG
}

void Game_SaveBegin() {
}

void Game_SaveEnd() {
}

void LoadBegin() {
}

void LoadEnd() {
}

void Game_LoadBegin_NewGame() {
  LoadBegin();
}

void Game_LoadEnd_NewGame() {
  LoadEnd();
}

void Game_LoadBegin_SaveGame() {
  LoadBegin();
}

void Game_LoadEnd_SaveGame() {
  LoadEnd();
}

void Game_LoadBegin_ChangeLevel() {
  LoadBegin();
}

void Game_LoadEnd_ChangeLevel() {
  LoadEnd();
}

void Game_LoadBegin_Trigger() {
}

void Game_LoadEnd_Trigger() {
}

void Game_Pause() {
}

void Game_Unpause() {
}

// nyx-core
extern void GameGlobal_OnInitFactory();
void Game_DefineExternals() {
  // nyx-core
  GameGlobal_OnInitFactory();
  // zParserExtender
#ifdef __G1
  if( Union.GetEngineVersion() == Engine_G1 )
    Gothic_I_Classic::DefineExternals();
#endif
//#ifdef __G1A
//  if( Union.GetEngineVersion() == Engine_G1A )
//    Gothic_I_Addon::DefineExternals();
//#endif
//#ifdef __G2
//  if( Union.GetEngineVersion() == Engine_G2 )
//    Gothic_II_Classic::DefineExternals();
//#endif
//#ifdef __G2A
//  if( Union.GetEngineVersion() == Engine_G2A )
//    Gothic_II_Addon::DefineExternals();
//#endif
}



// please disable unused functions.
// write 'false' in 'Enabled' macro.
#define AppDefault True
CApplication* lpApplication = CApplication::CreateRefApplication (
  Enabled( AppDefault ) Game_Entry,
  Enabled( AppDefault ) Game_Init,
  Enabled( AppDefault ) Game_Exit,
  Enabled( AppDefault ) Game_Loop,
  Enabled( AppDefault ) Game_SaveBegin,
  Enabled( AppDefault ) Game_SaveEnd,
  Enabled( AppDefault ) Game_LoadBegin_NewGame,
  Enabled( AppDefault ) Game_LoadEnd_NewGame,
  Enabled( AppDefault ) Game_LoadBegin_SaveGame,
  Enabled( AppDefault ) Game_LoadEnd_SaveGame,
  Enabled( AppDefault ) Game_LoadBegin_ChangeLevel,
  Enabled( AppDefault ) Game_LoadEnd_ChangeLevel,
  Enabled( AppDefault ) Game_LoadBegin_Trigger,
  Enabled( AppDefault ) Game_LoadEnd_Trigger,
  Enabled( AppDefault ) Game_Pause,
  Enabled( AppDefault ) Game_Unpause,
  Enabled( AppDefault ) Game_DefineExternals
  );
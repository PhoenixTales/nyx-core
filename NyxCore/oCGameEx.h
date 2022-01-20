#ifndef __OCGAMEEX_H__VER0__
#define __OCGAMEEX_H__VER0__

namespace Gothic_I_Classic {

  class oCGameEx {
    /* 
    Extended oCGame class.
    Instantiated as singleton ogame_ex in global scope.
    Defines additional HUD elements.
    */
  public:
    oCViewStatusBar* staminaBar;
    oCViewStatusBar* willpowerBar;
    oCViewStatusBar* madnessBar;
    oCViewStatusBar* toxinBar;
    oCViewStatusBar* radiationBar;
    oCGameEx();
    virtual ~oCGameEx();
    void Done();
    void Init();
  };
  extern oCGameEx* ogame_ex = NULL;  // global reference to extended game object
}

#endif

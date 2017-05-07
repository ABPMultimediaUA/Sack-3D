
#ifndef MYEVENTRECEIVER_H
#define MYEVENTRECEIVER_H

#include <SDL.h>

class MyEventReceiver;
struct Key2Method{
  SDL_Keycode keyCode;
    void (MyEventReceiver::*p)();
};
class MyEventReceiver{
     public:
      MyEventReceiver();
        virtual ~MyEventReceiver(){}
        virtual bool OnEvent(SDL_Event *event);
    virtual bool IsKeyDown(SDL_Keycode keyCode)const;
    void ClickEspacio();
    void ClickEnter();
    void ClickQ();
        void ClickP();
    void ClickE();
    void ClickA();
        void ClickEscape();
    void ClickF12();
    private:
      //SDL_Event event;
      bool KeyIsDown(SDL_Keycode);
      const Key2Method keys[9] = {
              { SDLK_SPACE        , ClickEspacio    }
            , { SDLK_RETURN       , ClickEnter      }
            , { SDLK_q            , ClickQ          }
            , { SDLK_e            , ClickE        }
            , { SDLK_p            , ClickP          }
            , { SDLK_ESCAPE       , ClickEscape     }
            , { SDLK_a            , ClickA          }
            , { SDLK_F12          , ClickF12        }
            , { SDLK_F1           , 0               }
      };
};

#endif


#ifndef MYEVENTRECEIVER_H
#define MYEVENTRECEIVER_H

#include <SDL.h>


class MyEventReceiver{
     public:
      MyEventReceiver();
      virtual ~MyEventReceiver(){}
      virtual void OnEvent(SDL_Event *event);
    virtual bool IsKeyDown(SDL_Keycode keyCode)const;
    private:
      bool KeyIsDown[124];

};

#endif


#include "MyEventReceiver.h"
#include "IrrManager.h"
#include "Player.h"
#include "World.h"

bool MyEventReceiver::OnEvent(const irr::SEvent& event){
     if(event.EventType == irr::EET_KEY_INPUT_EVENT ){
         KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
          if(event.KeyInput.PressedDown == true){
            if(event.KeyInput.Key == irr::KEY_RETURN)
              World::Inst()->getPlayer(1)->usar();
               switch(event.KeyInput.Key){
                  case irr::KEY_SPACE:
                      World::Inst()->getPlayer(1)->saltar();
                  break;
                  case irr::KEY_KEY_Q:
                      World::Inst()->getPlayer(1)->fingirMuerte();
                  break;
                  case irr::KEY_KEY_E:
                      World::Inst()->getPlayer(1)->CogerTirar();
                  break;
                  case irr::KEY_ESCAPE:
                      IrrMngr::Inst()->Close();
                  break;
              }
          }
     }
}
bool MyEventReceiver::IsKeyDown(irr::EKEY_CODE keyCode) const{
return KeyIsDown[keyCode];
}
MyEventReceiver::MyEventReceiver(){
  for (irr::u32 i=0; i<irr::KEY_KEY_CODES_COUNT; ++i)KeyIsDown[i]= false;
}
MyEventReceiver::~MyEventReceiver(){}

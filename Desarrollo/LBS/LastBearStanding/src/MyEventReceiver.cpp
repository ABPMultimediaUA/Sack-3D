
#include "MyEventReceiver.h"
#include "IrrManager.h"
#include "Player.h"
#include "World.h"


const Key2Method MyEventReceiver::keys[7] = {
        { irr::KEY_SPACE    , ClickEspacio    }
      , { irr::KEY_RETURN   , ClickEnter      }
      , { irr::KEY_KEY_Q    , ClickQ          }
      , { irr::KEY_KEY_E    , ClickE          }
      , { irr::KEY_ESCAPE   , ClickEscape     }
      , { irr::KEY_F12      , ClickF12        }
      , { irr::KEY_ZOOM     , 0               }
  };

bool MyEventReceiver::OnEvent(const irr::SEvent& event){
    if(event.EventType == irr::EET_KEY_INPUT_EVENT ){
        KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
        if(event.KeyInput.PressedDown == true){
            const Key2Method * it = keys;
            while(it->keyCode != irr::KEY_ZOOM ){
                if(it->keyCode == event.KeyInput.Key){
                    (this->*it->Key2Method::p)();
                    break;
                }
                it++;
            }
        }
    }
    return true;
}
bool MyEventReceiver::IsKeyDown(irr::EKEY_CODE keyCode) const{
return KeyIsDown[keyCode];
}
MyEventReceiver::MyEventReceiver(){
  for (irr::u32 i=0; i<irr::KEY_KEY_CODES_COUNT; ++i)KeyIsDown[i]= false;
}
void MyEventReceiver::ClickEspacio(){
  int id = (*Client::Inst()->getIdCliente())-'0';
  World::Inst()->getPlayer(id)->saltar();
}
void MyEventReceiver::ClickEnter(){
  int id = (*Client::Inst()->getIdCliente())-'0';
  World::Inst()->getPlayer(id)->usar();
}
void MyEventReceiver::ClickQ(){
    int id = (*Client::Inst()->getIdCliente())-'0';
  World::Inst()->getPlayer(id)->fingirMuerte();
}
void MyEventReceiver::ClickE(){
    int id = (*Client::Inst()->getIdCliente())-'0';
  World::Inst()->getPlayer(id)->CogerTirar();
}
void MyEventReceiver::ClickEscape(){
  IrrMngr::Inst()->Close();
}
void MyEventReceiver::ClickF12(){
  IrrMngr::Inst()->SwitchDebugMode();
  World::Inst()->SwitchDebugMode();
}

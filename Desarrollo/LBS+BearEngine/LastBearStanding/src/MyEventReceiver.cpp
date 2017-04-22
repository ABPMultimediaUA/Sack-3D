
#include "MyEventReceiver.h"
#include "BearManager.h"
#include "Player.h"
#include "World.h"

bool MyEventReceiver::OnEvent(const irr::SEvent& event){
    if(event.EventType == irr::EET_KEY_INPUT_EVENT ){
        KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
        if(event.KeyInput.PressedDown == true){
            const Key2Method * it = keys;
            while(it->keyCode != irr::KEY_ZOOM ){
                if(it->keyCode == event.KeyInput.Key){
                    if(World::Inst()->getTimeMapa() > 3000)  (this->*it->Key2Method::p)();
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
void MyEventReceiver::ClickP(){
    //int id = (*Client::Inst()->getIdCliente())-'0';
    //std::cout<<"Posicon Plyaer: "<<World::Inst()->getPlayer(id)->getPosition().x<<" "<<World::Inst()->getPlayer(id)->getPosition().y<<std::endl;
    std::cout<<"Time de Mapa: "<<World::Inst()->getTimeMapa()<<std::endl;
}
void MyEventReceiver::ClickEscape(){
  BearMngr::Inst()->Close();
}
void MyEventReceiver::ClickF12(){
  BearMngr::Inst()->SwitchDebugMode();
  World::Inst()->SwitchDebugMode();
}

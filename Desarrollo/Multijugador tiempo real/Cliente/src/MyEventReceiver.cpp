
#include "MyEventReceiver.h"
#include "PhysicWorld.h"

bool MyEventReceiver::OnEvent(const irr::SEvent& event){
     if(event.EventType == irr::EET_KEY_INPUT_EVENT ){
         KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
          if(event.KeyInput.PressedDown == true){
               switch(event.KeyInput.Key){
                  case irr::KEY_SPACE:
                      PhysicWorld::Instance()->getPlayer(1)->saltar();
                  break;
                  case irr::KEY_KEY_G:
                      PhysicWorld::Instance()->GetWorld()->SetGravity(b2Vec2(70.0f, -30.0f));
                  break;
                  case irr::KEY_KEY_H:
                      PhysicWorld::Instance()->GetWorld()->SetGravity(b2Vec2(0.0f, -30.0f));
                  break;
                  case irr::KEY_KEY_Q:
                      PhysicWorld::Instance()->getPlayer(1)->fingirMuerte();
                  case irr::KEY_KEY_E:
                       if(PhysicWorld::Instance()->getPlayer(1)->getPuedoCoger() && !PhysicWorld::Instance()->getPlayer(1)->getCogiendo()){
                           PhysicWorld::Instance()->getPlayer(1)->setObjCogido(PhysicWorld::Instance()->getPlayer(1)->getObjPuedoCoger());
                           dynamic_cast<Usable*>(PhysicWorld::Instance()->getPlayer(1)->getObjCogido())->setCogido(true);
                           PhysicWorld::Instance()->getPlayer(1)->crearJoint();
                       }
                       else if(PhysicWorld::Instance()->getPlayer(1)->getCogiendo()){
                           PhysicWorld::Instance()->getPlayer(1)->romperJoint();
                       }
                  break;
                  case irr::KEY_RETURN:
                      if(PhysicWorld::Instance()->getPlayer(1)->getCogiendo()){
                           PhysicWorld::Instance()->getPlayer(1)->usar();
                      }
                  break;
                  case irr::KEY_ESCAPE:
                      IrrManager::Instance()->Close();
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

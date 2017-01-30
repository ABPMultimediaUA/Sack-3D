#include "MyEventReceiver.h"
#include "PhysicWorld.h"


bool MyEventReceiver::OnEvent(const SEvent& event){
     if(event.EventType == irr::EET_KEY_INPUT_EVENT ){
         KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
          if(event.KeyInput.PressedDown == true){
               switch(event.KeyInput.Key){

                  //BOTONES JUGADOR 1
                  case KEY_SPACE:
                      PhysicWorld::Instance()->getPlayer(1)->saltar();
                  break;
                  case KEY_KEY_G:
                      PhysicWorld::Instance()->GetWorld()->SetGravity(b2Vec2(70.0f/MPP, -30.0f/MPP));
                  break;
                  case KEY_KEY_H:
                      PhysicWorld::Instance()->GetWorld()->SetGravity(b2Vec2(0.0f, -30.0f/MPP));
                  break;
                  case KEY_KEY_Q:
                      PhysicWorld::Instance()->getPlayer(1)->fingirMuerte();
                  case KEY_KEY_E:
                       if(PhysicWorld::Instance()->getPlayer(1)->getPuedoCoger() && !PhysicWorld::Instance()->getPlayer(1)->getCogiendo()){
                           PhysicWorld::Instance()->getPlayer(1)->setObjCogido(PhysicWorld::Instance()->getPlayer(1)->getObjPuedoCoger());
                           dynamic_cast<Usable*>(PhysicWorld::Instance()->getPlayer(1)->getObjCogido())->setCogido(true);
                           PhysicWorld::Instance()->getPlayer(1)->crearJoint();
                       }
                       else if(PhysicWorld::Instance()->getPlayer(1)->getCogiendo()){
                           PhysicWorld::Instance()->getPlayer(1)->romperJoint();
                       }
                  break;
                  case KEY_RETURN:
                      if(PhysicWorld::Instance()->getPlayer(1)->getCogiendo()){
                           PhysicWorld::Instance()->getPlayer(1)->usar();
                  		}
                  break;

                  //BOTONES JUGADOR 2
                  case KEY_UP:
                      PhysicWorld::Instance()->getPlayer(2)->saltar();
                  break;
                  case KEY_RSHIFT:
                      PhysicWorld::Instance()->getPlayer(2)->fingirMuerte();
                  break;
                  case KEY_NUMPAD0:
                     if(PhysicWorld::Instance()->getPlayer(2)->getPuedoCoger() && !PhysicWorld::Instance()->getPlayer(2)->getCogiendo()){
                           PhysicWorld::Instance()->getPlayer(2)->crearJoint();
                           PhysicWorld::Instance()->getPlayer(2)->setObjCogido(PhysicWorld::Instance()->getPlayer(2)->getObjPuedoCoger());
                           dynamic_cast<Usable*>(PhysicWorld::Instance()->getPlayer(2)->getObjCogido())->setCogido(true);
                       }

                       else if(PhysicWorld::Instance()->getPlayer(2)->getCogiendo()){
                           PhysicWorld::Instance()->getPlayer(2)->romperJoint();
                       }
                  break;
                  case KEY_NUMPAD3:
                      if(PhysicWorld::Instance()->getPlayer(2)->getCogiendo()){
                           PhysicWorld::Instance()->getPlayer(2)->usar();
                  		}
                  break;
              }
          }
     }
}
bool MyEventReceiver::IsKeyDown(EKEY_CODE keyCode) const{
return KeyIsDown[keyCode];
}
MyEventReceiver::MyEventReceiver(){
  for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)KeyIsDown[i]= false;
}

MyEventReceiver::~MyEventReceiver(){}

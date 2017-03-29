#include "MyEventReceiver.h"
#include "PhysicWorld.h"
#include "cuboMierda.h"


bool MyEventReceiver::OnEvent(const SEvent& event){
     if (event.EventType == irr::EET_MOUSE_INPUT_EVENT){
          switch(event.MouseInput.Event){
               case EMIE_LMOUSE_LEFT_UP:
                   cuboMierda* cubo = new cuboMierda((event.MouseInput.X - 1366/2)/5, (-event.MouseInput.Y+720/2)/5 );
                   PhysicWorld::Instance()->GetCubos()->push_back(cubo);
               break;
               break;
          }
     }
     if(event.EventType == irr::EET_KEY_INPUT_EVENT ){
         KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
          if(event.KeyInput.PressedDown == true){
               switch(event.KeyInput.Key){

                //BOTONES JUGADOR 1
                  case KEY_SPACE:
                      PhysicWorld::Instance()->getPlayer(1)->saltar();
                  break;
                  case KEY_KEY_Q:
                      PhysicWorld::Instance()->getPlayer(1)->fingirMuerte();
                  case KEY_KEY_E:
                       if(PhysicWorld::Instance()->getPlayer(1)->getPuedoCoger() && !PhysicWorld::Instance()->getPlayer(1)->getCogiendo()){
                           PhysicWorld::Instance()->getPlayer(1)->crearJoint();
                           PhysicWorld::Instance()->getPlayer(1)->setObjCogido(PhysicWorld::Instance()->getPlayer(1)->getObjPuedoCoger());
                           dynamic_cast<Usable*>(PhysicWorld::Instance()->getPlayer(1)->getObjCogido())->setCogida(true);
                           std::cout<<"ESTOY COGIENDO"<<std::endl;
                       }

                       else if(PhysicWorld::Instance()->getPlayer(1)->getCogiendo()){
                           PhysicWorld::Instance()->getPlayer(1)->romperJoint();
                           //dynamic_cast<Usable*>(PhysicWorld::Instance()->getPlayer()->getObjCogido())->setCogida(false);
                           std::cout<<"NO ESTOY COGIENDO"<<std::endl;
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
                           dynamic_cast<Usable*>(PhysicWorld::Instance()->getPlayer(2)->getObjCogido())->setCogida(true);
                           std::cout<<"ESTOY COGIENDO"<<std::endl;
                       }

                       else if(PhysicWorld::Instance()->getPlayer(2)->getCogiendo()){
                           PhysicWorld::Instance()->getPlayer(2)->romperJoint();
                           std::cout<<"NO ESTOY COGIENDO"<<std::endl;
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

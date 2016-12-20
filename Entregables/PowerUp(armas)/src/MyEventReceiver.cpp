#include "MyEventReceiver.h"
#include "PhysicWorld.h"
#include "cuboMierda.h"


bool MyEventReceiver::OnEvent(const SEvent& event){
     if (event.EventType == irr::EET_MOUSE_INPUT_EVENT){
          //switch(event.MouseInput.Event){
               //case EMIE_LMOUSE_LEFT_UP:
                   cuboMierda* cubo = new cuboMierda((event.MouseInput.X - 1366/2)/5, (-event.MouseInput.Y+720/2)/5 );
                   PhysicWorld::Instance()->GetCubos()->push_back(cubo);
               //break;
               //break;
          //}
     }
     if(event.EventType == irr::EET_KEY_INPUT_EVENT ){
         KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
          if(event.KeyInput.PressedDown == true){
               switch(event.KeyInput.Key){
                  case KEY_SPACE:
                      PhysicWorld::Instance()->getPlayer()->saltar();
                  break;

                  case KEY_KEY_Q:
                      PhysicWorld::Instance()->getPlayer()->fingirMuerte();
                  break;

                  case KEY_KEY_E:
                       if(PhysicWorld::Instance()->getPlayer()->getPuedoCoger() && !PhysicWorld::Instance()->getPlayer()->getCogiendo()){
                           PhysicWorld::Instance()->getPlayer()->crearJoint();
                           PhysicWorld::Instance()->getPlayer()->setObjCogido(PhysicWorld::Instance()->getPlayer()->getObjPuedoCoger());
                           std::cout<<"ESTOY COGIENDO"<<std::endl;
                       }

                       else if(PhysicWorld::Instance()->getPlayer()->getCogiendo()){
                           PhysicWorld::Instance()->getPlayer()->romperJoint();
                           std::cout<<"NO ESTOY COGIENDO"<<std::endl;
                       }
                  break;
                  case KEY_RETURN:
                      if(PhysicWorld::Instance()->getPlayer()->getCogiendo()){
                           PhysicWorld::Instance()->getPlayer()->usar();
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

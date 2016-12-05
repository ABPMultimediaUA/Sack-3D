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
               if(event.KeyInput.PressedDown == true){
                    switch(event.KeyInput.Key){
                       case KEY_KEY_A:
                            PhysicWorld::Instance()->getPlayer()->mover(-1);
                       break;
                       case KEY_KEY_D:
                            PhysicWorld::Instance()->getPlayer()->mover(1);
                       break;
                       case KEY_SPACE:
                           if(!PhysicWorld::Instance()->getPlayer()->getSaltando() || !PhysicWorld::Instance()->getPlayer()->getDobleSaltando()){
                                if(PhysicWorld::Instance()->getPlayer()->getSaltando() && !PhysicWorld::Instance()->getPlayer()->getDobleSaltando()){
                                        PhysicWorld::Instance()->getPlayer()->setDobleSaltando(true);
                                }
                                PhysicWorld::Instance()->getPlayer()->saltar();
                           }
                       break;
                       case KEY_KEY_E:

                            if(PhysicWorld::Instance()->getPlayer()->puedoCoger && !PhysicWorld::Instance()->getPlayer()->cogiendo){
                                PhysicWorld::Instance()->getPlayer()->crearJoint(PhysicWorld::Instance()->getPlayer()->getBody(), PhysicWorld::Instance()->getArma()->getBody());
                                PhysicWorld::Instance()->getArma()->setCogido(true);
                                std::cout<<PhysicWorld::Instance()->getArma()->getCogido()<<std::endl;
                            }

                            else if(PhysicWorld::Instance()->getPlayer()->cogiendo){
                                PhysicWorld::Instance()->getPlayer()->romperJoint();
                                std::cout<<"NO ESTOY COGIENDO"<<std::endl;
                            }
                       break;
                       case KEY_RETURN:
                           if(PhysicWorld::Instance()->getPlayer()->cogiendo){
                                Bala* bala = new Bala(2000, 1000, 100);
                                PhysicWorld::Instance()->GetBalas()->push_back(bala);
                       		}
                       break;
                       case KEY_KEY_Q:
                            PhysicWorld::Instance()->getPlayer()->fingirMuerte();
                        break;
                   }
               }else{
                    b2Vec2 vel;
                    switch(event.KeyInput.Key){
                       case KEY_KEY_A:
                           PhysicWorld::Instance()->getPlayer()->mover(0);
                       break;
                       case KEY_KEY_D:
                           PhysicWorld::Instance()->getPlayer()->mover(0);
                       break;
               }
          }
     }
}
MyEventReceiver::MyEventReceiver(){}

MyEventReceiver::~MyEventReceiver(){}

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
                           PhysicWorld::Instance()->getPlayer()->saltar();
                       break;
                       case KEY_KEY_E:

                            if(PhysicWorld::Instance()->getPlayer()->puedoCoger && !PhysicWorld::Instance()->getPlayer()->cogiendo){
                                b2RevoluteJointDef jointDef;
                                jointDef.bodyA = PhysicWorld::Instance()->getPlayer()->getBody();
                                jointDef.bodyB = PhysicWorld::Instance()->getArma()->getBody();
                                //jointDef.collideConnected = false;
                                //jointDef.localAnchorB = bodyPersonaje->GetLocalCenter();
                                jointDef.localAnchorA.Set(16,16);
                                jointDef.localAnchorB.Set(0,0);
                                PhysicWorld::Instance()->joint = (b2RevoluteJoint*)PhysicWorld::Instance()->GetWorld()->CreateJoint(&jointDef);
                                PhysicWorld::Instance()->joint->EnableMotor(true);
                                PhysicWorld::Instance()->joint->SetMaxMotorTorque(50.3f);
                                PhysicWorld::Instance()->getPlayer()->cogiendo = true;
                                std::cout<<"ESTOY COGIENDO"<<std::endl;
                            }

                            else if(PhysicWorld::Instance()->getPlayer()->cogiendo){
                                PhysicWorld::Instance()->GetWorld()->DestroyJoint(PhysicWorld::Instance()->joint);
                                PhysicWorld::Instance()->joint = NULL;
                                b2Vec2 vel = PhysicWorld::Instance()->getPlayer()->getBody()->GetLinearVelocity();
                                vel.x +=400;
                                vel.y +=400;
                                vel.x *=400;
                                vel.y *=400;
                                PhysicWorld::Instance()->getArma()->getBody()->ApplyLinearImpulse( vel, PhysicWorld::Instance()->getArma()->getBody()->GetLocalCenter());
                                PhysicWorld::Instance()->getPlayer()->cogiendo = false;
                                std::cout<<"NO ESTOY COGIENDO"<<std::endl;
                            }
                       break;
                       case KEY_RETURN:
                           if(PhysicWorld::Instance()->getPlayer()->cogiendo){

                                Bala* bala = new Bala();

                                b2Vec2 vel = bala->getBody()->GetLinearVelocity();

                                vel.x = bala->velocidad;

                                bala->getBody()->SetLinearVelocity(vel);

                                PhysicWorld::Instance()->GetBalas()->push_back(bala);

                       		}
                       break;
                   }
               }
          else{
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

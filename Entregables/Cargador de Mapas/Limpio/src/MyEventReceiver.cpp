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
                  case KEY_SPACE:
                      PhysicWorld::Instance()->getPlayer()->saltar();
                  break;
                  
                  case KEY_KEY_M:
                      //IrrManager::Instance()->driver->beginScene(true, true,SColor(255, 217, 194, 140));
                      //std::cout<< PhysicWorld::Instance()->getMap()->getMapa()<<std::endl;
                      
                      PhysicWorld::Instance()->crearMapa(PhysicWorld::Instance()->getMap()->getMapa()+1);
                  break;
                  
                  case KEY_KEY_Q:
                      PhysicWorld::Instance()->getPlayer()->fingirMuerte();
                  break;
                  case KEY_KEY_E:
                       if(PhysicWorld::Instance()->getPlayer()->getPuedoCoger() && !PhysicWorld::Instance()->getPlayer()->getCogiendo()){
                           b2RevoluteJointDef jointDef;
                           jointDef.bodyA = PhysicWorld::Instance()->getPlayer()->getBody();
                           jointDef.bodyB = PhysicWorld::Instance()->getArma()->getBody();
                           //jointDef.collideConnected = false;
                           //jointDef.localAnchorB = bodyPersonaje->GetLocalCenter();
                           jointDef.localAnchorA.Set(5,3);
                           jointDef.localAnchorB.Set(0,0);
                           PhysicWorld::Instance()->joint = (b2RevoluteJoint*)PhysicWorld::Instance()->GetWorld()->CreateJoint(&jointDef);
                           PhysicWorld::Instance()->joint->EnableMotor(true);
                           PhysicWorld::Instance()->joint->SetMaxMotorTorque(50.3f);
                           PhysicWorld::Instance()->getPlayer()->setCogiendo(true);
                           std::cout<<"ESTOY COGIENDO"<<std::endl;
                       }

                       else if(PhysicWorld::Instance()->getPlayer()->getCogiendo()){
                           PhysicWorld::Instance()->GetWorld()->DestroyJoint(PhysicWorld::Instance()->joint);
                           PhysicWorld::Instance()->joint = NULL;
                           b2Vec2 vel = PhysicWorld::Instance()->getPlayer()->getBody()->GetLinearVelocity();
                           vel.x +=400;
                           vel.y +=400;
                           vel.x *=400;
                           vel.y *=400;
                           PhysicWorld::Instance()->getArma()->getBody()->ApplyLinearImpulse( vel, PhysicWorld::Instance()->getArma()->getBody()->GetLocalCenter());
                           PhysicWorld::Instance()->getPlayer()->setCogiendo(false);
                           std::cout<<"NO ESTOY COGIENDO"<<std::endl;
                       }
                  break;
                  case KEY_RETURN:
                      if(PhysicWorld::Instance()->getPlayer()->getCogiendo()){
                           Bala* bala = new Bala();
                           b2Vec2 vel = bala->getBody()->GetLinearVelocity();
                           vel.x = bala->velocidad;
                           bala->getBody()->SetLinearVelocity(vel);
                           PhysicWorld::Instance()->GetBalas()->push_back(bala);
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

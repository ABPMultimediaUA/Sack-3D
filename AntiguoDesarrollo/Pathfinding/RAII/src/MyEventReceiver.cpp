
#include "MyEventReceiver.h"
#include "PhysicWorld.h"

Nodo* objetivo;

bool MyEventReceiver::OnEvent(const irr::SEvent& event){
     if(event.EventType == irr::EET_KEY_INPUT_EVENT ){
         KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
          if(event.KeyInput.PressedDown == true){
            if(event.KeyInput.Key == irr::KEY_RETURN)
              PhysicWorld::Instance()->getPlayer(1)->usar();
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
                      PhysicWorld::Instance()->getPlayer(1)->CogerTirar();
                  break;
                  case irr::KEY_KEY_K:
                      objetivo = PhysicWorld::Instance()->GetMap()->getListaNodos()->buscaNumero(rand() % 18);
                      PhysicWorld::Instance()->GetMap()->calcularPathfinding(
                                                PhysicWorld::Instance()->getPlayer(1)->getBody()->GetPosition().x,
                                                PhysicWorld::Instance()->getPlayer(1)->getBody()->GetPosition().y,
                                                objetivo
                                                                    );
                  //break;
                  //case  irr::KEY_KEY_L:
                      PhysicWorld::Instance()->getPlayer(1)->muevo(PhysicWorld::Instance()->GetMap()->getListaPath()->getUltimo()->getPosicion().x, PhysicWorld::Instance()->GetMap()->getListaPath()->getUltimo()->getPosicion().y);
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

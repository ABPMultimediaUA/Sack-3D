#include "MyEventReceiver.h"
#include "PhysicWorld.h"
#include "cuboMierda.h"
#include "Map.h"


bool MyEventReceiver::OnEvent(const SEvent& event){

     if(event.EventType == irr::EET_KEY_INPUT_EVENT ){
         KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
          if(event.KeyInput.PressedDown == true){
               switch(event.KeyInput.Key){
                  case KEY_KEY_P:
                      PhysicWorld::Instance()->getMapa()->iniciarMatriz(
                            PhysicWorld::Instance()->getPlayer()->getPosition().X,
                            PhysicWorld::Instance()->getPlayer()->getPosition().Y,
                            PhysicWorld::Instance()->getObjetivo()->getPosition().X,
                            PhysicWorld::Instance()->getObjetivo()->getPosition().Y
                    );
                      PhysicWorld::Instance()->getMapa()->obtenerPathfinding();
                  break;
                  case KEY_SPACE:
                      PhysicWorld::Instance()->getPlayer()->moverJugador(PhysicWorld::Instance()->getMapa()->avanzarX(),  PhysicWorld::Instance()->getMapa()->avanzarY());
                  break;
                  case KEY_KEY_A:
                      PhysicWorld::Instance()->getObjetivo()->mover(1, -1);
                  break;
                  case KEY_KEY_D:
                      PhysicWorld::Instance()->getObjetivo()->mover(1, 1);
                  break;
                  case KEY_KEY_W:
                      PhysicWorld::Instance()->getObjetivo()->mover(2, 1);
                  break;
                  case KEY_KEY_S:
                      PhysicWorld::Instance()->getObjetivo()->mover(2, -1);
                  break;
                  case KEY_KEY_E:

                  break;
                  case KEY_RETURN:
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

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
                    b2Vec2 vel;
                    switch(event.KeyInput.Key){
                       case KEY_KEY_A:

                       break;
                       case KEY_KEY_D:
                       break;
                       case KEY_SPACE:
                       break;
                   }
               }
          else{
               b2Vec2 vel;
               switch(event.KeyInput.Key){
                       case KEY_KEY_A:
                       break;
                       case KEY_KEY_D:
                       break;
               }
          }
     }
}
MyEventReceiver::MyEventReceiver(){}

MyEventReceiver::~MyEventReceiver(){}

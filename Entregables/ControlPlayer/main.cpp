#include <iostream>
#include <irrlicht.h>
#include <Box2D/Box2D.h>
#include <Box2D/Common/b2Math.h>
#include <vector>

#define SCREENWIDTH 1366
#define SCREENHEIGHT 768

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

struct cubo{
    cubo(ISceneManager* smgr, int tam, vector3df pos){
        cubeNode = smgr->addCubeSceneNode(tam);
        cubeNode->setPosition(pos);
        smgr->getMeshManipulator()->setVertexColors(cubeNode->getMesh(), SColor(255, rand()%255, rand()%255, rand()%255));
    }
    IMeshSceneNode* cubeNode;
    b2Body *body;
};
IrrlichtDevice *device = 0;
b2Vec2 gravity(0.0f, -10.0f);
bool doSleep = true	;
b2World world(gravity, doSleep);
ISceneManager* smgr;
ICameraSceneNode* camera;
IMeshSceneNode* personajeNode;
b2Body *bodyPersonaje;

std::vector<cubo*> cubos;
class MyEventReceiver : public IEventReceiver{
     public:
     virtual bool OnEvent(const SEvent& event){
          if (event.EventType == irr::EET_MOUSE_INPUT_EVENT){
               switch(event.MouseInput.Event){
                    case EMIE_LMOUSE_LEFT_UP:
                         int tam = 16, x = (event.MouseInput.X - (SCREENWIDTH/2))/5, y = (-event.MouseInput.Y+(SCREENHEIGHT/2))/5;
                         cubo* cuboNuevo = new cubo(smgr, tam, vector3df(x, y ,0));
                         b2PolygonShape polyShape;
                         b2FixtureDef fixtureDef;
                         b2BodyDef bodyDef;
                         bodyDef.type = b2_dynamicBody;
                         bodyDef.position.Set(x, y);
                         cuboNuevo->body = world.CreateBody(&bodyDef);
                         polyShape.SetAsBox(tam/2, tam/2);
                         fixtureDef.shape = &polyShape;
                         fixtureDef.friction = 10.5f;
                         fixtureDef.restitution  = 0.9f;
                         fixtureDef.density  = 10.f;
                         cuboNuevo->body->CreateFixture(&fixtureDef);
                         cubos.push_back(cuboNuevo);
                    break;
               }
          }
          if(event.EventType == irr::EET_KEY_INPUT_EVENT ){
               if(event.KeyInput.PressedDown == true){
                    b2Vec2 vel;
                    vector3df target;
                    vector3df target2;
                    vector3df posicion;

                    switch(event.KeyInput.Key){
                       case KEY_KEY_A:
                           vel = bodyPersonaje->GetLinearVelocity();
                           vel.x = -40;
                           bodyPersonaje->SetLinearVelocity( vel );
                       break;
                       case KEY_KEY_D:
                           vel = bodyPersonaje->GetLinearVelocity();
                           vel.x = 40;
                           bodyPersonaje->SetLinearVelocity( vel );
                       break;
                       case KEY_SPACE:
                           vel = bodyPersonaje->GetLinearVelocity();
                           vel.y = 40;
                           bodyPersonaje->SetLinearVelocity( vel );
                       break;

                       case KEY_LEFT:
                       		target = camera->getTarget();
                       		target2 = camera->getPosition();
                       		target.X -=10;
                       		target2.X -=10;
                       		camera->setTarget(target);
                            camera->setPosition(target2);

                       break;
                       case KEY_RIGHT:
                       		target = camera->getTarget();
                       		target2 = camera->getPosition();
                       		target.X+=10;
                       		target2.X+=10;
                       		camera->setTarget(target);
                            camera->setPosition(target2);
                       break;
                       case KEY_UP:
                       		target = camera->getTarget();
                       		target.Y+=10;
                       		camera->setTarget(target);
                       break;
                       case KEY_DOWN:
                       		target = camera->getTarget();
                       		target.Y-=10;
                       		camera->setTarget(target);
                       break;
                   }
               }
          else{
                b2Vec2 vel;
               switch(event.KeyInput.Key){
                       case KEY_KEY_A:
                           vel = bodyPersonaje->GetLinearVelocity();
                           vel.x = 0;
                           bodyPersonaje->SetLinearVelocity( vel );
                       break;
                       case KEY_KEY_D:
                           vel = bodyPersonaje->GetLinearVelocity();
                           vel.x = 0;
                           bodyPersonaje->SetLinearVelocity( vel );
                       break;
               }
          }
     }
}
     MyEventReceiver(){}
};

int main(){
     bool es;
     MyEventReceiver receiver;
     device = createDevice( video::EDT_OPENGL, dimension2d<u32>(SCREENWIDTH,SCREENHEIGHT), 16, true, false, false, &receiver);
     device->setWindowCaption(L"Irrlicht/Box2D Sample");
     IVideoDriver* driver = device->getVideoDriver();
     smgr = device->getSceneManager();
     IGUIEnvironment* guienv = device->getGUIEnvironment();
     ITimer* timer = device->getTimer();
     guienv->addStaticText(L"Box2D integrated with Irrlicht", rect<s32>(10,10,130,22), true);

        camera = smgr->addCameraSceneNode(0, vector3df(0,0,-140), vector3df(0,0,0));

     smgr->addLightSceneNode(0, vector3df(0, 100, -100), video::SColorf(1, 1, 1), 40.f);

     b2BodyDef groundBodyDef;
     groundBodyDef.position.Set(0.0f, -80.0f);
     b2Body* groundBody = world.CreateBody(&groundBodyDef);
     b2PolygonShape groundBox;
     groundBox.SetAsBox(1290.0f, 0.1f);
     groundBody->CreateFixture(&groundBox, 0.0f);

     groundBodyDef.position.Set(0.0f, 100.0f);
     groundBody = world.CreateBody(&groundBodyDef);
     groundBox.SetAsBox(1290.0f, 0.1f);
     groundBody->CreateFixture(&groundBox, 0.0f);


     groundBodyDef.position.Set(-160.0f, -100.0f);
     groundBody = world.CreateBody(&groundBodyDef);
     groundBox.SetAsBox(0.1f, 1290.0f);
     groundBody->CreateFixture(&groundBox, 0.0f);

     groundBodyDef.position.Set(160.0f, -100.0f);
     groundBody = world.CreateBody(&groundBodyDef);
     groundBox.SetAsBox(0.1f, 1290.0f);
     groundBody->CreateFixture(&groundBox, 0.0f);


     personajeNode = smgr->addCubeSceneNode(32);
     personajeNode->setPosition(vector3df(0, 0 ,0));
     smgr->getMeshManipulator()->setVertexColors(personajeNode->getMesh(), SColor(255,255,0,0));

     b2PolygonShape polyShape;
     b2FixtureDef fixtureDef;
     b2BodyDef bodyDef;

     bodyDef.type = b2_dynamicBody;
     bodyDef.position.Set(0, 0);
     bodyPersonaje = world.CreateBody(&bodyDef);
     bodyPersonaje->SetFixedRotation(true);
     polyShape.SetAsBox(16,16);

     fixtureDef.shape = &polyShape;
     fixtureDef.friction = 0.0f;
     fixtureDef.restitution  = 0.f;
     fixtureDef.density  = 100.f;
     b2Fixture* personFixture = bodyPersonaje->CreateFixture(&fixtureDef);



     float32 timeStep = 1.0f / 120.0f;
     int32 velocityIterations = 6;
     int32 positionIterations = 6;
     f32 TimeStamp = timer->getTime();
     f32 DeltaTime = timer->getTime() - TimeStamp;
     while(device->run()){
          driver->beginScene(true, true, SColor(255,100,101,140));
          DeltaTime = timer->getTime() - TimeStamp;
          TimeStamp = timer->getTime();
          world.Step(DeltaTime*timeStep, velocityIterations, positionIterations);
          world.ClearForces();
          for(int i=0; i < cubos.size(); i++){
               cubos[i]->cubeNode->setPosition(vector3df(cubos[i]->body->GetPosition().x,cubos[i]->body->GetPosition().y,0));
               cubos[i]->cubeNode->setRotation(vector3df(0,0,cubos[i]->body->GetAngle()* 180 / 3.14159265));
          }
          personajeNode->setPosition(vector3df(bodyPersonaje->GetPosition().x,bodyPersonaje->GetPosition().y,0));

          smgr->drawAll();
          guienv->drawAll();
          driver->endScene();
       }
       device->drop();
       return 0;
    }

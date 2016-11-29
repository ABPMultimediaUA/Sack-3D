#include <iostream>
#include <irrlicht.h>
#include <Box2D/Box2D.h>
#include <Box2D/Common/b2Math.h>

#define SCREENWIDTH 1920
#define SCREENHEIGHT 1080

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
    b2World world(gravity);
    ISceneManager* smgr;
    ICameraSceneNode* camera;

    IMeshSceneNode* personajeNode;
    b2Body *bodyPersonaje;

    IMeshSceneNode* personajeNode2;
    b2Body *bodyPersonaje2;

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
                         fixtureDef.restitution  = 0.3f;
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
                           vel = bodyPersonaje2->GetLinearVelocity();
                           vel.x = -40;
                           bodyPersonaje2->SetLinearVelocity( vel );
                       break;
                       case KEY_RIGHT:
                           vel = bodyPersonaje2->GetLinearVelocity();
                           vel.x = 40;
                           bodyPersonaje2->SetLinearVelocity( vel );
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
                       case KEY_LEFT:
                           vel = bodyPersonaje2->GetLinearVelocity();
                           vel.x = 0;
                           bodyPersonaje2->SetLinearVelocity( vel );
                       break;
                       case KEY_RIGHT:
                           vel = bodyPersonaje2->GetLinearVelocity();
                           vel.x = 0;
                           bodyPersonaje2->SetLinearVelocity( vel );
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

     vector3df posCamera;
     vector3df lookAtCamera;

        camera = smgr->addCameraSceneNode(0, vector3df(0,0,-50), vector3df(0,0,0));

     smgr->addLightSceneNode(0, vector3df(0,50,-100), video::SColorf(1,1,1), 40.f);


     // ------------------------------------------------------------------------------------------------------------------------------------ //
     // -------------------------------------------------------- SUELO --------------------------------------------------------------------- //

     b2BodyDef groundBodyDef;
     groundBodyDef.position.Set(0.0f, -80.0f);
     b2Body* groundBody = world.CreateBody(&groundBodyDef);
     b2PolygonShape groundBox;
     groundBox.SetAsBox(300.0f, 0.1f);
     groundBody->CreateFixture(&groundBox, 0.0f);
     IMesh* cubeMesh;
     cubeMesh = smgr->getGeometryCreator()->createCubeMesh(vector3df(300.0f, 0.1f, 40.f));
     smgr->addMeshSceneNode(cubeMesh)->setPosition(vector3df(0.0f, -80.0f,0));
     smgr->getMeshManipulator()->setVertexColors(cubeMesh, SColor(255,100,255,0));

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

    // ------------------------------------------------------------------------------------------------------------------------------------ //
    // ----------------------------------------------------- PERSONAJE 1 ------------------------------------------------------------------ //

     personajeNode = smgr->addCubeSceneNode(10);
     personajeNode->setPosition(vector3df(0, 0 ,0));
     smgr->getMeshManipulator()->setVertexColors(personajeNode->getMesh(), SColor(255,255,0,0));

     b2PolygonShape polyShape;
     b2FixtureDef fixtureDef;
     b2BodyDef bodyDef;

     bodyDef.type = b2_dynamicBody;
     bodyDef.position.Set(0, 0);
     bodyPersonaje = world.CreateBody(&bodyDef);
     bodyPersonaje->SetFixedRotation(true);
     polyShape.SetAsBox(5,5);

     fixtureDef.shape = &polyShape;
     fixtureDef.friction = 0.0f;
     fixtureDef.restitution  = 0.3f;
     fixtureDef.density  = 100.f;
     b2Fixture* personFixture = bodyPersonaje->CreateFixture(&fixtureDef);

    // ------------------------------------------------------------------------------------------------------------------------------------ //
    // ----------------------------------------------------- PERSONAJE 2 ------------------------------------------------------------------ //

     personajeNode2 = smgr->addCubeSceneNode(10);
     personajeNode2->setPosition(vector3df(0, 0 ,0));
     smgr->getMeshManipulator()->setVertexColors(personajeNode2->getMesh(), SColor(255,0,255,0));

     b2PolygonShape polyShape2;
     b2FixtureDef fixtureDef2;
     b2BodyDef bodyDef2;

     bodyDef2.type = b2_dynamicBody;
     bodyDef2.position.Set(0, 0);
     bodyPersonaje2 = world.CreateBody(&bodyDef2);
     bodyPersonaje2->SetFixedRotation(true);
     polyShape2.SetAsBox(5,5);

     fixtureDef2.shape = &polyShape2;
     fixtureDef2.friction = 0.0f;
     fixtureDef2.restitution  = 0.3f;
     fixtureDef2.density  = 100.f;
     b2Fixture* personFixture2 = bodyPersonaje2->CreateFixture(&fixtureDef2);

    // ------------------------------------------------------------------------------------------------------------------------------------ //
    // ------------------------------------------------------------------------------------------------------------------------------------ //

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
          personajeNode2->setPosition(vector3df(bodyPersonaje2->GetPosition().x,bodyPersonaje2->GetPosition().y,0));

          posCamera.X = lookAtCamera.X = (personajeNode->getPosition().X + personajeNode2->getPosition().X)/2;
          posCamera.Y = lookAtCamera.Y = ((personajeNode->getPosition().Y + personajeNode2->getPosition().Y)/2);
          posCamera.Z = -50;
          lookAtCamera.Z = 0;

          camera->setTarget(lookAtCamera);
          camera->setPosition(posCamera);

          //std::cout <<"--------> " <<  << std::endl;
          float distancia = sqrt(pow((personajeNode->getPosition().X - personajeNode2->getPosition().X), 2));
          distancia += 10*distancia;

          f32 zoomFOV = atan2(distancia/2, 50);

          camera->setFOV(zoomFOV);

          smgr->drawAll();
          guienv->drawAll();
          driver->endScene();
       }
       device->drop();
       return 0;
    }

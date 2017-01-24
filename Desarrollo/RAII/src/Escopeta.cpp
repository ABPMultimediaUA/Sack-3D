#include "Escopeta.h"
#include "PhysicWorld.h"

Escopeta::Escopeta(int modelo,b2Vec2 pos){
    b2BodyDef bodyDef;
    restitution = 0.2f;
    density = 2.0f;
    friction = 0.5f;
    tam = irr::core::vector3df(10.f/MPP,3.f/MPP,1.f/MPP);
    timerIrr = IrrManager::Instance()->getTimer();
    timerescopeta = timerIrr->getTime();
    node = IrrManager::Instance()->addCubeSceneNode(tam,SColor(255, 0, 255, 0));
    node->setPosition(irr::core::vector3df(pos.X/MPP,pos.Y/MPP,0));
    bodyDef.position.Set(pos.X/MPP,pos.Y/MPP);
    bodyDef.type = b2_dynamicBody;
    body  = PhysicWorld::Instance()->GetWorld()->CreateBody(&bodyDef);
    InicializeFixtures(RELEASE);

    //b2PolygonShape polyShape;
    //polyShape.SetAsBox(tam.X/2.0f,tam.Y/2.0f);
    //fixtureDef.shape = &polyShape;
    //fixtureDef.friction = 0.5f;
    //fixtureDef.restitution  = 0.2f;
    //fixtureDef.density  = 2.0f;
    //b2Fixture* fixture = body->CreateFixture(&fixtureDef);
    //fixture->SetUserData((void*)ARMA);
    //body->SetFixedRotation(true);
    //polyShape.SetAsBox((tam.X*2.0),(tam.Y*2.0));
    //fixtureDef.isSensor = true;
    //b2Fixture* PistolaSensorFixture = body->CreateFixture(&fixtureDef);
    //PistolaSensorFixture->SetUserData((void*)SENSOR);

}
//---------------------------------------------------------------------------
/**
   Metodo que actualiza la posicion y rotacion del Pistola
*/
void Escopeta::actualiza(){
    if(cogido){
        node->setPosition(irr::core::vector3df(body->GetPosition().x+((5.0f/MPP)*dir),body->GetPosition().y,0));
    }
    else node->setPosition(irr::core::vector3df(body->GetPosition().x,body->GetPosition().y,0));
    node->setRotation(irr::core::vector3df(0,0,body->GetAngle()*RADTOGRAD));
}
//---------------------------------------------------------------------------
/**
   Metodo que ejecuta el usar de la clase
*/
void Escopeta::usar(){

    if(IrrManager::Instance()->getTime()-timerescopeta>cadencia && conUsos){
        for(int i=0; i<10; i++){
            float desvBala = rand()% 30;
            GameResource<Bala>* balaGR = PhysicWorld::Instance()->CreateBala(new Bala(irr::core::vector3df(body->GetPosition().x, body->GetPosition().y, 0), 100, 2, desvBala, dir));
            Bala* bala = balaGR->Get();
            b2Vec2 vel = bala->getBody()->GetLinearVelocity();
            vel.x = bala->velocidad;
            if(dir==1) bala->getBody()->SetLinearVelocity(vel);
            else bala->getBody()->SetLinearVelocity(-vel);
            PhysicWorld::Instance()->GetBalas()->push_back(bala);
        }
        timerescopeta = timerIrr->getTime();
        usos-=1;
        if(usos==0)conUsos=false;
    }
}
//---------------------------------------------------------------------------
/**
   Getters and setters
*/
void Escopeta::setCogido(bool aux){
    cogido= false;
    irr::core::vector3df tam2 = irr::core::vector3df(5,3,1);
    irr::core::vector3df tam = irr::core::vector3df(tam2.X/MPP,tam2.Y/MPP,tam2.Z/MPP);
    body->DestroyFixture(body->GetFixtureList());
    body->DestroyFixture(body->GetFixtureList());
    b2BodyDef bodyDef;
    b2FixtureDef fixtureDef;
    b2PolygonShape polyShape;
    b2Fixture* PistolaSensorFixture;
    b2Fixture* fixture;
    if(aux){
        polyShape.SetAsBox(tam.X/2.0f,tam.Y/2.0f);
        fixtureDef.shape = &polyShape;
        fixtureDef.density  = 0.1f;
        fixtureDef.isSensor = true;
        fixture = body->CreateFixture(&fixtureDef);
        fixture->SetUserData((void*)30);
        body->SetFixedRotation(true);
        polyShape.SetAsBox((tam.X/4.0f),(tam.Y/4.0f));
        fixtureDef.isSensor = true;
        b2Fixture* escopetaSensorFixture = body->CreateFixture(&fixtureDef);
        escopetaSensorFixture->SetUserData((void*)35);
    }
    else{
        b2PolygonShape polyShape;
        polyShape.SetAsBox(tam.X/2.0f,tam.Y/2.0f);
        fixtureDef.shape = &polyShape;
        fixtureDef.friction = 0.5f;
    fixtureDef.restitution  = 0.2f;
    fixtureDef.density  = 2.0f;
        fixture = body->CreateFixture(&fixtureDef);
        fixture->SetUserData((void*)30);
        body->SetFixedRotation(true);
        polyShape.SetAsBox((tam.X*2.0),(tam.Y*2.0));
        fixtureDef.isSensor = true;
        PistolaSensorFixture = body->CreateFixture(&fixtureDef);
        PistolaSensorFixture->SetUserData((void*)35);
    }
    cogido = aux;
}
bool Escopeta::getCogida(){return cogido;}
b2Body* Escopeta::getBody(){return body;}
bool Escopeta::getConUsos(){ return conUsos;}
//---------------------------------------------------------------------------
/**
   Destructor
*/
Escopeta::~Escopeta()
{
    //dtor
}

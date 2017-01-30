#include "ConstructorRed.h"

#include "PhysicWorld.h"
#include "IrrManager.h"

#define RADTOGRAD 180 / 3.14159265  ///< Conversor de radianes a grados

ConstructorRed::ConstructorRed(float xr, float yr)
{
    //ctor
    x = xr;
    y = yr;
    vivo = 1;
    vivoAntiguo = 1;
    direccion = 0;
    vector3df tam2 = vector3df(8, 16,4);
    tam = vector3df(tam2.X/MPP,tam2.Y/MPP,tam2.Z/MPP);
    node = IrrManager::Instance()->addCubeSceneNode(tam,SColor(255, 255, 124, 150));
    node->setPosition(vector3df(x,y,0));

    b2BodyDef bodyDef;
    b2FixtureDef fixtureDef;
    b2PolygonShape polyShape;

    bodyDef.position.Set(x,y);
    bodyDef.type = b2_dynamicBody;

    body  = PhysicWorld::Instance()->GetWorld()->CreateBody(&bodyDef);

    polyShape.SetAsBox(tam.X/2.0f,tam.Y/2.0f);
    fixtureDef.shape = &polyShape;
    fixtureDef.friction = 7.5f;
    fixtureDef.restitution  = 0.2f;
    fixtureDef.density  = 10.0f;
    b2Fixture* fixture = body->CreateFixture(&fixtureDef);
    fixture->SetUserData((void*)14);
    body->SetFixedRotation(true);

    polyShape.SetAsBox((tam.X/4),(tam.Y));
    //polyShape.SetAsBox(tam.X/4,tam.Y/4,b2Vec2(0,-tam.Y/2), 0);
    fixtureDef.isSensor = true;
    b2Fixture* personajeSensorFixture = body->CreateFixture(&fixtureDef);
    personajeSensorFixture->SetUserData((void*)66);
}

void ConstructorRed::teletransportar(){
    body->SetTransform(b2Vec2(x,y), body->GetAngle());
}

void ConstructorRed::actualiza(){
    //std::cout<<"ESTOY ACTUALIZANDO PLAYERRED4YYY->"<<y<<std::endl;
    float aux_x = x;
    float aux_y = y;

    teletransportar();
    node->setPosition(vector3df(body->GetPosition().x,body->GetPosition().y,0));
    node->setRotation(vector3df(0,0,body->GetAngle()* RADTOGRAD));
   // std::cout<<"ESPECIAL2->"<<PhysicWorld::Instance()->getPlayer()->getBody()->GetPosition().x<<std::endl;
   //std::cout<<"ESPECIAL2->"<<PhysicWorld::Instance()->getPlayer()->getBody()->GetPosition().y<<std::endl;

   if(vivoAntiguo != vivo){
        fingirMuerte();
        vivoAntiguo = vivo;
   }

}

//---------------------------------------------------------------------------
/**
   fingirMuerte
*/
void ConstructorRed::fingirMuerte(){
    if(vivo == 0){
        b2FixtureDef fixtureDef;
        b2FixtureDef fixtureDef2;
        b2CircleShape circleShape1;
        b2CircleShape circleShape2;

        body->DestroyFixture(body->GetFixtureList());
        body->DestroyFixture(body->GetFixtureList());
        body->SetFixedRotation(false);

        circleShape1.m_p.Set(0,-3.f/MPP);
        circleShape2.m_p.Set(0,3.f/MPP);
        circleShape1.m_radius = (tam.X)/2;
        circleShape2.m_radius = (tam.X)/2;

        fixtureDef.shape = &circleShape1;

        fixtureDef.friction = 0.9f;
        fixtureDef.restitution  = 0.3f;
        fixtureDef.density  = 1.f;
        personFixture = body->CreateFixture(&fixtureDef);
        personFixture->SetUserData((void*)14);

        fixtureDef2.shape = &circleShape2;

        fixtureDef2.friction = 0.9f;
        fixtureDef2.restitution  = 0.3f;
        fixtureDef2.density  = 1.f;
        b2Fixture* personFixture2 = body->CreateFixture(&fixtureDef2);
        personFixture2->SetUserData((void*)14);

        body->SetTransform( body->GetPosition(),0);
        body->SetAngularVelocity(0);

        if(direccion == 0 ){
        body->ApplyAngularImpulse(-1*0.0003f);
        std::cout<<"1->"<<std::endl;
        }else{
        body->ApplyAngularImpulse(1*0.0003f);
        std::cout<<"2->"<<std::endl;
        }
    }else{
        b2BodyDef bodyDef;
        b2FixtureDef fixtureDef;
        b2PolygonShape polyShape;

        body->DestroyFixture(body->GetFixtureList());
        body->DestroyFixture(body->GetFixtureList());
        body->SetFixedRotation(true);

        polyShape.SetAsBox((tam.X)/2,(tam.Y)/2);
        fixtureDef.shape = &polyShape;

        fixtureDef.friction = 7.5f;
        fixtureDef.restitution  = 0.2f;
        fixtureDef.density  = 10.0f;
        b2Fixture* fixture = body->CreateFixture(&fixtureDef);
        fixture->SetUserData((void*)14);

        polyShape.SetAsBox((tam.X)/4,(tam.Y)/4,b2Vec2(0,(-tam.Y)/2), 0);
        fixtureDef.isSensor = true;
        b2Fixture* personajeSensorFixture = body->CreateFixture(&fixtureDef);
        personajeSensorFixture->SetUserData((void*)66);

        body->SetTransform( body->GetPosition(),0);
        body->SetAngularVelocity(0);
        body->ApplyLinearImpulse(b2Vec2(0,10.0f/MPP),b2Vec2(0,0));
    }
}

void ConstructorRed::setx(long int aux){
    float aux_x = aux/10000.f;
    x=aux_x;
    //std::cout<<"ESTOY ACTUALIZANDO PLAYERRED3->"<<x<<std::endl;
}
void ConstructorRed::sety(long int aux){
    float aux_y = aux/10000.f;
    y=aux_y;
    //std::cout<<"ESTOY ACTUALIZANDO PLAYERRED3->"<<y<<std::endl;
}

void ConstructorRed::setVivo(int aux){
    vivo = aux;
}

void ConstructorRed::setDireccion(int aux){
    direccion = aux;
}

b2Body* ConstructorRed::getBody(){return body;}

ConstructorRed::~ConstructorRed()
{
    //dtor
}

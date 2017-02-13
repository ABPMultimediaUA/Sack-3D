#include "PlayerRed.h"

#include "PhysicWorld.h"
#include "IrrManager.h"


#define LEVANTADO        1
#define MUERTO_DORMIDO   2
#define AGACHADO         3
#define PLAYER           10
#define PIESPLAYER       100

#define RADTOGRAD 180 / 3.14159265  ///< Conversor de radianes a grados


PlayerRed::PlayerRed(char idr[], float xr, float yr)
{
    tam = irr::core::vector3df(.7f, 1.8f,.7f);
    x = xr;
    y = yr;
    strncpy(id, idr, sizeof(id));
    estado=LEVANTADO;
    estadoAntiguo=LEVANTADO;
    direccion = 0;
    node = IrrManager::Instance()->addCubeSceneNode(tam,irr::video::SColor(255, 255, 124, 150));
    node->setPosition(irr::core::vector3df(xr,yr,0));
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    body  = PhysicWorld::Instance()->GetWorld()->CreateBody(&bodyDef);
    body->SetFixedRotation(true);
    InicializeFixtures(LEVANTADO);
}
void PlayerRed::InicializeFixtures(int mode){
    switch(mode){
        case LEVANTADO:{

            b2FixtureDef fixtureDef;
            b2PolygonShape polyShape;
            body->SetAngularVelocity(0);
            body->SetTransform( body->GetPosition(),0);
            body->SetFixedRotation(true);
            body->ApplyLinearImpulse(b2Vec2(0,5.0f),b2Vec2(0,0));
            polyShape.SetAsBox(tam.X/2.0f,tam.Y/2.0f);
            fixtureDef.shape = &polyShape;
            fixtureDef.friction = 0;
            fixtureDef.restitution  = 0.2f;
            fixtureDef.density  = 10.0f;
            b2Fixture* fixture = body->CreateFixture(&fixtureDef);
            fixture->SetUserData((void*)18);
            polyShape.SetAsBox(tam.X/4,tam.Y/4,b2Vec2(0,-tam.Y/2), 0);
            fixtureDef.isSensor = true;
            b2Fixture* sensorFixture = body->CreateFixture(&fixtureDef);
            sensorFixture->SetUserData((void*)19);
        break;}
        case MUERTO_DORMIDO:{
            b2FixtureDef fixtureDef;
            b2FixtureDef fixtureDef2;
            b2CircleShape circleShape1;
            b2CircleShape circleShape2;
            fixtureDef.friction = 1.f; fixtureDef.restitution = 0.5f; fixtureDef.density = 1;
            body->SetFixedRotation(false);
            circleShape1.m_p.Set(0,-0.2f);
            circleShape2.m_p.Set(0,0.2f);
            circleShape1.m_radius = (tam.X)/2;
            circleShape2.m_radius = (tam.X)/2;
            fixtureDef.shape = &circleShape1;
            /*
            fixtureDef.friction =friction;
            fixtureDef.restitution  = restitution;
            fixtureDef.density  = density;
            */
            personFixture = body->CreateFixture(&fixtureDef);
            personFixture->SetUserData((void*)18);
            fixtureDef2.shape = &circleShape2;
            fixtureDef2.friction = 1.f;
            fixtureDef2.restitution  = 0.5f;
            fixtureDef2.density  = 1;
            b2Fixture* personFixture2 = body->CreateFixture(&fixtureDef2);
            personFixture2->SetUserData((void*)18);
            circleShape1.m_radius = 1;
            fixtureDef2.isSensor = true;
            fixtureDef2.filter.maskBits = 1;
            fixtureDef2.filter.categoryBits = 2;
            b2Fixture* areaFixure = body->CreateFixture(&fixtureDef2);
            areaFixure->SetUserData((void*)19);
            body->SetTransform( body->GetPosition(),0);
            body->SetAngularVelocity(0);
            if(body->GetLinearVelocity().x > 0 )body->ApplyAngularImpulse(-0.5f);
            else body->ApplyAngularImpulse(0.5f);
        break;}
        case AGACHADO:{
        break;}
    }
}
void PlayerRed::DestroyFixtures(){
    for (b2Fixture* f = body->GetFixtureList(); f;){
        b2Fixture* fixtureToDestroy = f;
        f = f->GetNext();
        body->DestroyFixture( fixtureToDestroy );
    }
}

void PlayerRed::teletransportar(){
    body->SetTransform(b2Vec2(x,y), body->GetAngle());
}

void PlayerRed::actualiza(){
    /*td::cout<<"ESTOY ACTUALIZANDO PLAYERRED4YYY->"<<y<<std::endl;
    std::cout<<"ESTOY ACTUALIZANDO PLAYERRED4XXX->"<<x<<std::endl;*/
    float aux_x = x;
    float aux_y = y;

    teletransportar();
    node->setPosition(vector3df(body->GetPosition().x,body->GetPosition().y,0));
    node->setRotation(vector3df(0,0,body->GetAngle()* RADTOGRAD));
    //std::cout<<"ESPECIAL2->"<<PhysicWorld::Instance()->getPlayer()->getBody()->GetPosition().x<<std::endl;
   //std::cout<<"ESPECIAL2->"<<PhysicWorld::Instance()->getPlayer()->getBody()->GetPosition().y<<std::endl;
    //std::cout<<"ACTUALIZO"<<x<<std::endl;
   if(estado != estadoAntiguo){
        fingirMuerte();
        estadoAntiguo = estado;
   }

}

void PlayerRed::mover(){

    body->SetLinearVelocity(b2Vec2 (direccion*vel, body->GetLinearVelocity().y));

}
void PlayerRed::saltar(int i){
    if(i==1){
        b2Vec2 velV = body->GetLinearVelocity();
        velV.y = salto;
        body->SetLinearVelocity(velV);
    }
    else if(i==2){
        b2Vec2 velV = body->GetLinearVelocity();
        velV.y = salto*3/4;
        body->SetLinearVelocity(velV);
    }
}



void PlayerRed::fingirMuerte(){
    DestroyFixtures();
    if(estado==2){
        InicializeFixtures(MUERTO_DORMIDO);
    }
    else{
        InicializeFixtures(LEVANTADO);
    }
}

void PlayerRed::setx(long int aux){
    float aux_x = aux/1000000.f;
    x=aux_x;
    //std::cout<<"ESTOY ACTUALIZANDO PLAYERRED3->"<<x<<std::endl;
}
void PlayerRed::sety(long int aux){
    float aux_y = aux/1000000.f;
    y=aux_y;
    //std::cout<<"ESTOY ACTUALIZANDO PLAYERRED3->"<<y<<std::endl;
}

void PlayerRed::setEstado(int aux){
    estado = aux;
}

void PlayerRed::setDireccion(int aux){
    direccion = aux;
}

void PlayerRed::setId(char aux[]){
    strncpy(id, aux, sizeof(id));
}

char* PlayerRed::getId(){return id;
}



b2Body* PlayerRed::getBody(){return body;}


PlayerRed::~PlayerRed()
{
    //dtor
}

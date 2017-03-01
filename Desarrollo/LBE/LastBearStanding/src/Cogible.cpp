#include "Cogible.h"
#include "World.h"

Cogible::Cogible(Spawner* expo, b2Vec2 pos){
    if(expo == NULL)expuesto = false;
    pos.x += (tam.X/2);
    pos.y  = -1*(pos.y-(tam.Y/2));
    expositor = expo;
    b2BodyDef bodyDef;
    bodyDef.position.Set(pos.x,pos.y);
    bodyDef.type = b2_dynamicBody;
    body  = World::Inst()->GetWorld()->CreateBody(&bodyDef);
    body->SetFixedRotation(true);
}
Cogible::~Cogible(){
    if(body){
        World::Inst()->GetWorld()->DestroyBody(body);
        body = NULL;
    }
}
void Cogible::DestroyFixtures(){
	for (b2Fixture* f = body->GetFixtureList(); f;){
	    b2Fixture* fixtureToDestroy = f;
	    f = f->GetNext();
	    body->DestroyFixture( fixtureToDestroy );
	}
}
void Cogible::InicializeFixtures(int mode){
	b2FixtureDef fixtureDef;
    b2PolygonShape polyShape;
    polyShape.SetAsBox(tam.X/2.0f,tam.Y/2.0f);
    fixtureDef.shape = &polyShape;
    fixtureDef.friction = friction;
    fixtureDef.restitution  = restitution;
    fixtureDef.density  = density;
    fixtureDef.filter.categoryBits = M_COGIBLE;
    fixtureDef.filter.maskBits = M_SUELO|M_TELEPORT|M_MUELLE|M_COGIBLE;
    if(mode == RELEASE){
        b2Fixture* fixture = body->CreateFixture(&fixtureDef);
        fixture->SetUserData((void*)DATA_COGIBLE);
        polyShape.SetAsBox((tam.X*2.0f),(tam.Y*2.0f));
        body->SetFixedRotation(false);
    }
    else{
        body->SetAngularVelocity(0);
        body->SetFixedRotation(true);
        body->SetTransform( body->GetPosition(),0);
    }
    fixtureDef.isSensor = true;
    fixtureDef.filter.categoryBits = M_COGIBLESENSOR;
    fixtureDef.filter.maskBits = M_PLAYER;
    b2Fixture* sensorFixture = body->CreateFixture(&fixtureDef);
    sensorFixture->SetUserData((void*)DATA_COGIBLE_SENSOR);
}
void Cogible::actualiza(){
    if(cogido)node->setPosition(irr::core::vector3df(body->GetPosition().x+((.5f)*dir),body->GetPosition().y,-.4f));
    else node->setPosition(irr::core::vector3df(body->GetPosition().x,body->GetPosition().y,-.4f));
    node->setRotation(irr::core::vector3df(0,0,body->GetAngle()*RADTOGRAD));
    if(teletransportado)teletransportar();
}
void Cogible::setCogido(bool aux){
	DestroyFixtures();
    if(aux){
        InicializeFixtures(CATCH);
        if(expuesto){
            expositor->soltar();
            expuesto = false;
        }
    }
    else InicializeFixtures(RELEASE);
    cogido = aux;
}
void Cogible::teletransportar(){
    teletransportado = false;
    if(dir != 0) nextPos.x += (dir*2);
    else nextPos.x += 1.5f;
    velActual = body->GetLinearVelocity();
    body->SetTransform(b2Vec2(nextPos.x,nextPos.y), body->GetAngle());
    body->SetLinearVelocity(velActual);
}
void Cogible::setExpositor(Spawner* aux){expositor=aux;}
Spawner* Cogible::getExpositor(){return expositor;}
int Cogible::getIdCogible(){};

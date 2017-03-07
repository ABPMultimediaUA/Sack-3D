#include "Cogible.h"
#include "Spawner.h"
#include "World.h"

int Cogible::contID = 0;
Cogible::Cogible(Spawner* expo, b2Vec2 pos, irr::core::vector3df tam, irr::video::SColor color)
:GameObject(pos,tam,color){
    idCogible = contID;
    std::cout<<idCogible<<std::endl;
    contID++;
    autoDestruir = false;
    cogido = false;
    teletransportado = false;
    dir = 1;
    expuesto = false;
    restitution = 0.2f;
    density = 2.0f;
    friction = 0.8f;
    if(expo == NULL)expuesto = false;
    expositor = expo;
    b2BodyDef bodyDef;
    bodyDef.position.Set(pos.x+(m_tam.X/2),-1*(pos.y-(m_tam.Y/2)));
    bodyDef.type = b2_dynamicBody;
    m_pBody  = m_pWorld->GetWorld()->CreateBody(&bodyDef);
    m_pBody->SetFixedRotation(true);
}
Cogible::~Cogible(){}
void Cogible::DestroyFixtures(){
	for (b2Fixture* f = m_pBody->GetFixtureList(); f;){
	    b2Fixture* fixtureToDestroy = f;
	    f = f->GetNext();
	    m_pBody->DestroyFixture( fixtureToDestroy );
	}
}
void Cogible::InicializeFixtures(int mode){
	b2FixtureDef fixtureDef;
    b2PolygonShape polyShape;
    polyShape.SetAsBox(m_tam.X/2.0f,m_tam.Y/2.0f);
    fixtureDef.shape = &polyShape;
    fixtureDef.friction = friction;
    fixtureDef.restitution  = restitution;
    fixtureDef.density  = density;
    fixtureDef.filter.categoryBits = M_COGIBLE;
    fixtureDef.filter.maskBits = M_SUELO|M_TELEPORT|M_MUELLE|M_COGIBLE;
    if(mode == RELEASE){
        b2Fixture* fixture = m_pBody->CreateFixture(&fixtureDef);
        fixture->SetUserData((void*)DATA_COGIBLE);
        polyShape.SetAsBox((m_tam.X*2.0f),(m_tam.Y*2.0f));
        m_pBody->SetFixedRotation(false);
    }
    else{
        m_pBody->SetAngularVelocity(0);
        m_pBody->SetFixedRotation(true);
        m_pBody->SetTransform( m_pBody->GetPosition(),0);
    }
    fixtureDef.isSensor = true;
    fixtureDef.filter.categoryBits = M_COGIBLESENSOR;
    fixtureDef.filter.maskBits = M_PLAYER;
    b2Fixture* sensorFixture = m_pBody->CreateFixture(&fixtureDef);
    sensorFixture->SetUserData((void*)DATA_COGIBLE_SENSOR);
}
void Cogible::actualiza(){
    if(cogido)m_pNode->setPosition(irr::core::vector3df(m_pBody->GetPosition().x+((.5f)*dir),m_pBody->GetPosition().y,-.4f));
    else m_pNode->setPosition(irr::core::vector3df(m_pBody->GetPosition().x,m_pBody->GetPosition().y,-.4f));
    m_pNode->setRotation(irr::core::vector3df(0,0,m_pBody->GetAngle()*RADTOGRAD));
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
    velActual = m_pBody->GetLinearVelocity();
    m_pBody->SetTransform(b2Vec2(nextPos.x,nextPos.y), m_pBody->GetAngle());
    m_pBody->SetLinearVelocity(velActual);
}
void     Cogible::setDireccion(int d){if(d != 0) dir = d;}
int     Cogible::getDireccion(){return dir;}
void     Cogible::setExpositor(Spawner* aux){expositor=aux;}
void     Cogible::setNextPos(b2Vec2 pos){teletransportado=true; nextPos = pos;}
void     Cogible::setExpuesto(bool aux){expuesto = aux;}
Spawner* Cogible::getExpositor(){return expositor;}
bool     Cogible::getCogido(){return cogido;}
bool     Cogible::getAutoDestruir(){return autoDestruir;}
int      Cogible::getIdCogible(){return idCogible;}
bool     Cogible::getExpuesto(){return expuesto;}

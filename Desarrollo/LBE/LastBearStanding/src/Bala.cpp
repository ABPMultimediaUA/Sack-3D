
#include "Bala.h"
#include "World.h"

Bala::Bala( b2Vec2 pos,  int tiempoVidaP, int velocidad, float deviacionP, int dir,int tipo):
GameObject(pos,irr::core::vector3df(.4f, .2f,.2f),irr::video::SColor(255, 255,0 ,0)),dir(dir),tiempoVida(tiempoVidaP),desviacion(deviacionP){
    destruir = false;
    b2BodyDef bodyDef;
    b2FixtureDef fixtureDef;
    b2PolygonShape polyShape;
    timer2Kill = m_pIrrMngr->getTimer();
    time2Kill = timer2Kill->getTime();
    bodyDef.position.Set(pos.x+(m_tam.X/2)+dir,-1*(pos.y-(m_tam.Y/2)));
    bodyDef.type = b2_dynamicBody;
    bodyDef.bullet = true;
    m_pBody  = m_pWorld->GetWorld()->CreateBody(&bodyDef);
    m_pBody->SetGravityScale( 0 );
    polyShape.SetAsBox((m_tam.X)/2.f,(m_tam.Y)/2.f);
    fixtureDef.shape = &polyShape;
    fixtureDef.filter.categoryBits = M_BALA;
    fixtureDef.filter.maskBits = M_SUELO|M_TELEPORT|M_PLAYER;
    balaFixture = m_pBody->CreateFixture(&fixtureDef);
    b2Fixture* balaSensorFixture = m_pBody->CreateFixture(&fixtureDef);
    balaSensorFixture->SetUserData((void*)DATA_BALA);
    if(dir>0)velo.x = velocidad;
    else     velo.x = -velocidad;
    if(desviacion != 0 )velo.y = (((rand()% 10000) / 10000.0)*desviacion)-(desviacion/2);
    m_pBody->SetLinearVelocity(velo);
    teletransportado = false;
}
Bala::~Bala(){}
void Bala::actualiza(){
    if(teletransportado) teletransportar();
    m_pNode->setPosition(irr::core::vector3df(m_pBody->GetPosition().x,m_pBody->GetPosition().y,0));
    if(m_pIrrMngr->getTime()-time2Kill>tiempoVida){destruir = true;}
}
void Bala::teletransportar(){
    teletransportado = false;
    nextPos.x += dir;
    m_pBody->SetTransform(nextPos, m_pBody->GetAngle());
    m_pBody->SetLinearVelocity(velo);
}

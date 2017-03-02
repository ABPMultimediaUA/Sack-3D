
#include "Bala.h"
#include "PhysicWorld.h"
#include "IrrManager.h"

Bala::Bala( irr::core::vector3df pos,  int tiempoVidaP, int velocidad, float deviacionP, int dir,int tipo):
tiempoVida(tiempoVidaP),desviacion(deviacionP){
    switch(tipo){
        case 0: { tam = irr::core::vector3df(.4f, .2f,.2f); break;}
        case 1: { tam = irr::core::vector3df(.08f, .08f,.08f); break;}
        case 2: { tam = irr::core::vector3df(.4f, .2f,.2f); break;}
        case 3: { tam = irr::core::vector3df(.4f, .2f,.2f); break;}
    }
    b2BodyDef bodyDef;
    b2FixtureDef fixtureDef;
    b2PolygonShape polyShape;
    timerIrr = IrrManager::Instance()->getTimer();
    timerbala = timerIrr->getTime();
    node = IrrManager::Instance()->addCubeSceneNode(tam, irr::video::SColor(255, 255,0 ,0));
    node->setPosition(pos);
    bodyDef.position.Set(pos.X+((2)*dir),pos.Y);
    bodyDef.type = b2_dynamicBody;
    body  = PhysicWorld::Instance()->GetWorld()->CreateBody(&bodyDef);
    body->SetGravityScale( 0 );
    polyShape.SetAsBox((tam.X)/2,(tam.Y)/2);
    fixtureDef.shape = &polyShape;
    balaFixture = body->CreateFixture(&fixtureDef);
    b2Fixture* balaSensorFixture = body->CreateFixture(&fixtureDef);
    balaSensorFixture->SetUserData((void*)40);
    b2Vec2 velo;
    if(dir>0)velo.x = velocidad;
    else     velo.x = -velocidad;
    if(desviacion != 0 )velo.y = (((rand()% 10000) / 10000.0)*desviacion)-(desviacion/2);
    body->SetLinearVelocity(velo);

}
void Bala::actualiza(){
    if(teletransportado) teletransportar();
    node->setPosition(irr::core::vector3df(body->GetPosition().x,body->GetPosition().y,0));
}
void Bala::teletransportar(){
    teletransportado = false;
    nextPos.x += (1*10);
    body->SetTransform(nextPos, body->GetAngle());
}
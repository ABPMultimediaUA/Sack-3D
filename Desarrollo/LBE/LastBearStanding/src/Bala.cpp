
#include "Bala.h"
#include "World.h"
#include "IrrManager.h"

Bala::Bala( irr::core::vector3df pos,  int tiempoVidaP, int velocidad, float deviacionP, int dir,int tipo):
dir(dir),tiempoVida(tiempoVidaP),desviacion(deviacionP){
    switch(tipo){
        case 0: { tam = irr::core::vector3df(.4f, .2f,.2f);    break;}
        case 1: { tam = irr::core::vector3df(.2f, .2f,.2f);    break;}
        case 2: { tam = irr::core::vector3df(.4f, .2f,.2f);    break;}
        case 3: { tam = irr::core::vector3df(.4f, .2f,.2f);    break;}
    }
    b2BodyDef bodyDef;
    b2FixtureDef fixtureDef;
    b2PolygonShape polyShape;
    timer2Kill = IrrMngr::Inst()->getTimer();
    time2Kill = timer2Kill->getTime();
    node = IrrMngr::Inst()->addCubeSceneNode(tam, irr::video::SColor(255, 255,0 ,0));
    node->setPosition(pos);
    bodyDef.position.Set(pos.X+((2)*dir),pos.Y);
    bodyDef.type = b2_dynamicBody;
    body  = World::Inst()->GetWorld()->CreateBody(&bodyDef);
    body->SetGravityScale( 0 );
    polyShape.SetAsBox((tam.X)/2,(tam.Y)/2);
    fixtureDef.shape = &polyShape;
    fixtureDef.filter.categoryBits = M_BALA;
    fixtureDef.filter.maskBits = M_SUELO|M_TELEPORT|M_PLAYER;
    balaFixture = body->CreateFixture(&fixtureDef);
    b2Fixture* balaSensorFixture = body->CreateFixture(&fixtureDef);
    balaSensorFixture->SetUserData((void*)DATA_BALA);
    if(dir>0)velo.x = velocidad;
    else     velo.x = -velocidad;
    if(desviacion != 0 )velo.y = (((rand()% 10000) / 10000.0)*desviacion)-(desviacion/2);
    body->SetLinearVelocity(velo);

}
Bala::~Bala(){
    if(node)node->remove();
    if(body)World::Inst()->GetWorld()->DestroyBody(body);
}
void Bala::actualiza(){
    if(teletransportado) teletransportar();
    node->setPosition(irr::core::vector3df(body->GetPosition().x,body->GetPosition().y,0));
    if(IrrMngr::Inst()->getTime()-time2Kill>tiempoVida){destruir = true;}
}
void Bala::teletransportar(){
    teletransportado = false;
    nextPos.x += dir;
    body->SetTransform(nextPos, body->GetAngle());
    body->SetLinearVelocity(velo);
}

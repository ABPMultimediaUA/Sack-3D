#include "PlayerRed.h"
#include "World.h"
#include "IrrManager.h"


PlayerRed::PlayerRed(b2Vec2 pos, int mando, char idr[]):Player(pos,mando){
    strncpy(id, idr, sizeof(id));
    estadoAntiguo=LEVANTADO;
}
void PlayerRed::mover(int mov){
    if(primera){
        //setPos();
        primera=false;
    }
    if(moviendo == 1){direccion = moviendo = mov;}
    else if(moviendo == -1){direccion = moviendo = mov;}
    else{moviendo = mov;}
    body->SetLinearVelocity(b2Vec2 (moviendo*vel, body->GetLinearVelocity().y));
    if(cogiendo) objCogido->setDireccion(direccion);
}

void PlayerRed::actualiza(){
    //Player::actualiza();
    node->setPosition(irr::core::vector3df(body->GetPosition().x,body->GetPosition().y,0));
    node->setRotation(irr::core::vector3df(0,0,body->GetAngle()*RADTOGRAD));
    mover(moviendo);
    if(estado != estadoAntiguo){
            std::cout<<"estaaaaaaaaaaaaaado"<<std::endl;
        fingirMuerte();
        estadoAntiguo = estado;
    }
}

void PlayerRed::setPos(){
    body->SetTransform(b2Vec2(x,y), body->GetAngle());
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

#include "PlayerRed.h"
#include "World.h"
#include "IrrManager.h"


PlayerRed::PlayerRed(b2Vec2 pos, int mando, char idr[]):Player(pos,mando){
    strncpy(id, idr, sizeof(id));
    estadoAntiguo=LEVANTADO;
}
void PlayerRed::mover(){
    if(primera){
        teletransportar();
        primera=false;
    }
    if(moviendo == 1){direccion = moviendo;}
    else if(moviendo == -1){direccion = moviendo;}
    body->SetLinearVelocity(b2Vec2 (moviendo*vel, body->GetLinearVelocity().y));
    if(cogiendo) objCogido->setDireccion(direccion);
}

void PlayerRed::actualiza(){
    Player::actualiza();
    if(estado != estadoAntiguo){
        fingirMuerte();
        estadoAntiguo = estado;
    }
}

//void PlayerRed::saltar(int i){
//    if(i==1){
//        b2Vec2 velV = body->GetLinearVelocity();
//        velV.y = salto;
//        body->SetLinearVelocity(velV);
//    }
//    else if(i==2){
//        b2Vec2 velV = body->GetLinearVelocity();
//        velV.y = salto*3/4;
//        body->SetLinearVelocity(velV);
//    }
//}

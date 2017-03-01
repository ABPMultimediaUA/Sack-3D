#include "PlayerRed.h"
#include "World.h"


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
    //if(paraMorir)morir();
    node->setPosition(irr::core::vector3df(body->GetPosition().x,body->GetPosition().y,0));
    node->setRotation(irr::core::vector3df(0,0,body->GetAngle()*RADTOGRAD));
    mover(moviendo);
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

void PlayerRed::CogerTirar(int idCogible){
    if(idCogible!=-1){
                for (int i = 0; i <World::Inst()->GetCogibles().size(); ++i){
                    if(World::Inst()->GetCogibles().at(i)->getIdCogible()==idCogible){
                      objCogido = World::Inst()->GetCogibles().at(i);
                    }
                }
                std::cout<<"Cogible es "<<idCogible<<std::endl;
                objCogido = objPuedoCoger;
                objCogido->setCogido(true);
                b2RevoluteJointDef jointDef;
                jointDef.bodyA = body;
                jointDef.bodyB = objPuedoCoger->getBody();
                jointDef.localAnchorA.Set(0,0.3f);
                jointDef.localAnchorB.Set(0,0);
                joint = (b2RevoluteJoint*)World::Inst()->GetWorld()->CreateJoint(&jointDef);
                joint->EnableMotor(true);
                cogiendo = true;
    }else{
                Soltar();
    }
}

void PlayerRed::morirRed(){
    paraMorir = false;
    if(cogiendo) Soltar();
    DestroyFixtures();
    estado = MUERTO_DORMIDO;
    InicializeFixtures(MUERTO_DORMIDO);
    muerto = true;
}




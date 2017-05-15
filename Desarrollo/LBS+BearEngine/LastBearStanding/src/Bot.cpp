#include "PhysicBody/PBDeadPlayer.h"
#include "PhysicBody/PBAlivePlayer.h"
#include "Bot.h"
#include "World.h"
#include "Usable.h"
#include "PathFinding/Lista.h"
#include "PathFinding/Nodo.h"
#include <ctime>
#include <stdlib.h>

Bot::Bot(b2Vec2 pos, int mando, char *texture, char idr[]):Player( pos, texture, mando){
    strncpy(id, idr, sizeof(id));
    enMuelle = false;
    salto = 7.0f;
    vel = 2.5f;
    mandobusco=mando;
    estadoBot = 0;
    cogido = false;
    lastDir = 0;
}


void Bot::InicializaVariables(){
    //std::cout<<"Soy Bot: "<<mando<<std::endl;

    players = World::Inst()->GetPlayers();
    spawners = World::Inst()->GetSpawners();
    nodos = World::Inst()->GetNodos();
    Nodo* aux  = NULL;

    /*for(int i = 0; i< nodos.size(); i++){
        if(mando == 1) std::cout<<"NODO: "<<nodos.at(i)->getNumero()<<" POS: "<<nodos.at(i)->getPosicion().x<<" "<<nodos.at(i)->getPosicion().y<<std::endl;
    }*/
    posicionSpawn = getSpawnCercano(m_gameObject.GetPosition().x, m_gameObject.GetPosition().y);
    //std::cout<<"POS Spawn: "<<posicionSpawn.x<<" "<<posicionSpawn.y<<std::endl;
    for(int i = 0; i< nodos.size(); i++){
        b2Vec2 posNodo = nodos.at(i)->getPosicion();

        if( abs(posNodo.x-posicionSpawn.x) <= 0.1 && abs( posNodo.y-posicionSpawn.y)<= 0.1)
            aux = nodos.at(i);
    }

    Nodo* aux2 = getMas(m_gameObject.GetPosition().x, m_gameObject.GetPosition().y);
    //std::cout<<"Nodos: "<<aux<<" "<<aux2<<std::endl;

    if(aux && aux2) 
        calcularPathfinding(aux2, aux);

    if(pathfinding && pathfinding->getTamanyo() != 0)
        muevo(pathfinding->getUltimo()->getPosicion().x,pathfinding->getUltimo()->getPosicion().y);
}

void Bot::actualiza(MyEventReceiver *events){
    Player::actualiza();
    //std::cout<<"BOT: "<<mando<<" POS: "<<m_gameObject.GetPosition().x<< " "<<m_gameObject.GetPosition().y<<std::endl;

    switch(estadoBot){

        case 0: {
            buscaArma();
            break;
        }
        case 1: {
            buscaJugador();
            break;
        }
        case 2: {
          break;
        }
        case 3: {
          break;
        }
    }
}

void Bot::buscaArma(){
    if(cogiendo) estadoBot = 1;

    else if(pathfinding->getTamanyo()<1 && World::Inst()->getVivos() >1){
        despega();
        CogerTirar();

        if(cogiendo) estadoBot = 1;
        else if(World::Inst()->getVivos() >1){
            posicionSpawn.y = 0;
            posicionSpawn = getSpawnCercano(m_gameObject.GetPosition().x, m_gameObject.GetPosition().y);
            if(posicionSpawn.y != 0){
                Nodo* aux = NULL;
                b2Vec2 cont;
                for(int i = 0; i< nodos.size(); i++){
                    cont = nodos.at(i)->getPosicion();

                    if(cont == posicionSpawn){
                        aux = nodos.at(i);
                    }

                }

                //std::cout<<"SOY BOT "<<mando<<" y BUSCO ARMA"<<std::endl;
                //if(mando == 1) std::cout<<"SOY BOT: "<<mando<<std::endl;
                //if(mando == 1) std::cout<<" INI AND AUX "<<nodoFinIni<<" "<<aux<<std::endl;

                calcularPathfinding(nodoFinIni,aux);


                if(pathfinding->getTamanyo()>1 && players.at(mando)->getMuerto() == false)
                    pathfinding->remove(pathfinding->getUltimo()->getPosicion());

                else if(pathfinding->getTamanyo()>0 && players.at(mando)->getMuerto() == false)
                    colisionConNodo(pathfinding->getUltimo()->getNumero());

                if(pathfinding->getTamanyo() != 0 && World::Inst()->getVivos() >1)
                    muevo(pathfinding->getUltimo()->getPosicion().x,pathfinding->getUltimo()->getPosicion().y);
            }
        }

    }
}

void Bot::buscaJugador(){
    if(cogiendo){
          Usable* us= dynamic_cast<Usable*>(objCogido);
          if(us){
              if(us->getUsos()<1){
                  CogerTirar();
                  estadoBot = 0;
              }
          }


    }
    else if(!cogiendo){
        estadoBot = 0;
    }
    if(cogiendo && mando != mandobusco && players.at(mandobusco)->getMuerto()==false
          && abs(players.at(mandobusco)->GetPosition().x - m_gameObject.GetPosition().x)<3
          && abs(players.at(mandobusco)->GetPosition().y - m_gameObject.GetPosition().y)<0.2  ){

          usar();
    }
    else if(cogiendo && World::Inst()->getVivos() >1 && pathfinding->getTamanyo()<1){
        Nodo* temp;
        int distancia = 5000;

        for(int i = 0; i<players.size(); i++){

            if(players.at(i)->getMando() != mando && players.at(i)->getMuerto() == false ){
                int distancia2 = abs(m_gameObject.GetPosition().x - players.at(i)->GetPosition().x)
                          + abs(m_gameObject.GetPosition().y - players.at(i)->GetPosition().y);
                if(distancia > distancia2){
                    //if(mando == 3) std::cout<<"Distancia entre bots: "<<distancia2<<std::endl;
                    distancia = distancia2;
                    mandobusco = i;
                }
            }
        }
        temp = getCercanoTotal(players.at(mandobusco)->GetPosition().x,players.at(mandobusco)->GetPosition().y);

        //std::cout<<"SOY BOT "<<mando<<" y BUSCO JUGADOR: "<<mandobusco<<std::endl;
        calcularPathfinding(nodoFinIni,temp);

        if(pathfinding->getTamanyo()>1 && players.at(mando)->getMuerto() == false)
            pathfinding->remove(pathfinding->getUltimo()->getPosicion());

        else if(pathfinding->getTamanyo()>0 && players.at(mando)->getMuerto() == false)
            colisionConNodo(pathfinding->getUltimo()->getNumero());

        if(pathfinding->getTamanyo() != 0 && World::Inst()->getVivos() >1)
            muevo(pathfinding->getUltimo()->getPosicion().x,pathfinding->getUltimo()->getPosicion().y);
    }
}

void Bot::colisionConNodo(int nodo){

    if(pathfinding->getUltimo() && pathfinding->getUltimo()->getNumero() == nodo ){
        //std::cout<<"COLISION BOT: "<<mando<<" NODO: "<<nodo<<std::endl;
        pathfinding->remove(pathfinding->getUltimo()->getPosicion());
        //if(pathfinding->getTamanyo() != 0 && World::Inst()->getVivos() >1)
            //muevo(pathfinding->getUltimo()->getPosicion().x,pathfinding->getUltimo()->getPosicion().y);
    }
}


void Bot::mover(MyEventReceiver *events ){
    if(muerto || fingiendoMuerte){
        return;
    }
    direccion = dir = 0;
    if(moviendo == true){
        if((abs(m_gameObject.GetPosition().x - nodox) >= 0.2)
        && (abs(m_gameObject.GetPosition().x - nodox) <= 2.6)
        && (abs(m_gameObject.GetPosition().y) - abs(nodoy) >= 0.2)
        && World::Inst()->getVivos() >1){
            saltar();
        }
        if( (abs(m_gameObject.GetPosition().x - nodox) < 0.08) ){
            if(pathfinding->getTamanyo() == 1){saltando = false;}

            if((!saltando || enMuelle) &&  pathfinding->getTamanyo() >= 1){
              if(pathfinding->getTamanyo() != 0 && World::Inst()->getVivos() >1){
                  muevo(pathfinding->getUltimo()->getPosicion().x,pathfinding->getUltimo()->getPosicion().y);
              }
            }
        }
        else if(m_gameObject.GetPosition().x > nodox){
          direccion = lastDir = dir = -1;
      }
        else if(m_gameObject.GetPosition().x < nodox){
          direccion = lastDir = dir = 1;
      }
    }
    if(direccion != direccionA){
        direccionA = direccion;
        m_pClient->enviarMoviendo(dir, mando);
    }
    if(lastDir ==  1)m_gameObject.SetXRotation(0);
    if(lastDir == -1)m_gameObject.SetXRotation(180);

    m_gameObject.SetLinearVelocity(b2Vec2 (dir*vel,m_gameObject.GetLinearVelocity().y));
    if(cogiendo) objCogido->setDireccion(lastDir);
}

void Bot::muevo(float x, float y){
    float posX =  2.0f*x;
    float posY = -2.0f*y;
    nodox = posX;
    nodoy = posY;
    moviendo = true;
    dir = 0;
    saltando = false;
    dobleSaltando = false;
    enMuelle = false;
}

void Bot::calcularPathfinding(Nodo* inicial, Nodo* objetivo){
     Nodo* aux;
     Nodo* nodoInicial = inicial;
     Nodo* nodoDestino = objetivo;
     Nodo* nodoActual;

     //std::cout<<std::endl;
     //std::cout<<"Empieza la la construccion del pathfinding"<<std::endl;
     //std::cout<<"Soy el BOT numero: "<<mando<<std::endl;

     if(nodoInicial == NULL || nodoDestino == NULL){
      //std::cout<<"Inicial: "<<nodoInicial<<" Destino: "<<nodoDestino<<std::endl;
        //std::cout<<"NODO INICIAL O DESTINO ES IGUAL A NULL"<<std::endl;
        return;
     }

     Lista listaAbierta;
     Lista listaCerrada;


     //std::cout<<"Nodo inicial: "<<nodoInicial->getNumero()<<" Datos["<<nodoInicial->getPosicion().x<<" "<<nodoInicial->getPosicion().y<<"]"<<std::endl;
     //std::cout<<"Nodo destino: "<<nodoDestino->getNumero()<<" Datos["<<nodoDestino->getPosicion().x<<" "<<nodoDestino->getPosicion().y<<"]"<<std::endl;
    // std::cout<<std::endl;

     if(nodoInicial->getPosicion().x == nodoDestino->getPosicion().x && nodoInicial->getPosicion().y == nodoDestino->getPosicion().y){
          pathfinding = new Lista();
          pathfinding->insertar(nodoInicial);
          //std::cout<<"<<<<<<<<<PATHFINDING>>>>>>>>>"<<std::endl;
          nodoFinIni= pathfinding->getHead();
          //pathfinding->imprimirLista();
     }
     else if(nodoInicial->getPosicion().x != nodoDestino->getPosicion().x || nodoInicial->getPosicion().y != nodoDestino->getPosicion().y){
           nodoActual = new Nodo(nodoInicial->getPosicion(), glm::vec3(0.1f,0.1f,0.1f), nodoInicial->getNumero(), 0, NULL);
           listaAbierta.insertar(nodoActual);
           while( listaAbierta.getTamanyo() > 0 && listaAbierta.buscaNodo2( nodoDestino->getPosicion().x, nodoDestino->getPosicion().y ) == NULL) {

               //listaAbierta.imprimirLista();
               //std::cout<<"NODO ACTUAL: "<<nodoActual->getNumero()<<std::endl;

               nodoActual = listaAbierta.getMenorCosto();
               listaAbierta.remove(nodoActual->getPosicion());

               nodoActual->setNext(NULL);
               listaCerrada.insertar(nodoActual);
               for(int i = 0; i<buscaNumero(nodoActual->getNumero())->getAdyacentes().size(); i++){

                   if(listaCerrada.buscaNumero( buscaNumero(nodoActual->getNumero())->getAdyacentes()[i] ) == NULL
                       && listaAbierta.buscaNumero( buscaNumero(nodoActual->getNumero())->getAdyacentes()[i] ) == NULL){
                           int numero = buscaNumero(nodoActual->getNumero())->getAdyacentes()[i];
                           b2Vec2 posicion;
                           posicion.x = buscaNumero(numero)->getPosicion().x;
                           posicion.y = buscaNumero(numero)->getPosicion().y;
                           int coste = abs(posicion.x-nodoDestino->getPosicion().x) + abs(posicion.y -nodoDestino->getPosicion().y);
                           Nodo* aux = new Nodo (posicion, glm::vec3(0.1f,0.1f,0.1f),  numero, coste, nodoActual);
                           listaAbierta.insertar(aux);
                       }
               }
           }
           nodoActual = listaAbierta.buscaNodo2(nodoDestino->getPosicion().x, nodoDestino->getPosicion().y);
           pathfinding = new Lista();
           while(nodoActual!=NULL){
               pathfinding->insertar(nodoActual);
               nodoActual = nodoActual->getPadre();
           }
           //std::cout<<"<<<<<<<<<PATHFINDING>>>>>>>>>"<<std::endl;
           nodoFinIni= pathfinding->getHead();
           //pathfinding->imprimirLista();
           //std::cout<<std::endl;
     }
}

b2Vec2 Bot::getSpawnCercano(float x, float y){

    float pos2 = -10*(y/2);
    int posY = (int) pos2;
    float buscoY = posY/10.0f;

    float buscoX = x/2;

    b2Vec2 pos;
    float dif = 50;

    //std::cout<<"Posicion Bot "<<mando<<": "<<buscoX<<" "<<buscoY<<std::endl;

    for(int i = 0; i< spawners.size(); i++){
        float coste = abs(spawners.at(i)->GetPosition().x - buscoX) + abs(spawners.at(i)->GetPosition().y-buscoY);
        //std::cout<<"Spawn: "<<i<< " coste: "<<coste<<std::endl;
        if(coste<dif && spawners.at(i)->GetCogiendo() == true){
            //std::cout<<"Numero Spawn: "<<i<<std::endl;
            dif = coste;
            pos = spawners.at(i)->GetPosition();
            pos.y = pos.y - 0.065;
        }
    }

    return pos;
}

Nodo *Bot::getMas(float x, float y){
    /*if(mando == 2){
        std::cout<<"Pos entra: "<<x<<" "<<y<<std::endl;
    }*/
    float pos2 = -10*(y/2);
    int posY = (int) pos2;
    float buscoY = posY/10.0f;
    int vamos1 = 10*buscoY;

    float buscoX = x/2;

    Nodo *aux = NULL;
    float dif = 50;

    for(int i = 0; i< nodos.size(); i++){
        int vamos2 = 10*nodos.at(i)->getPosicion().y;
        //if(mando == 2) std::cout<<"NODO EN Y: "<<vamos2<<" BUSOC Y: "<<vamos1<<std::endl;
        if(abs(vamos2 - vamos1)<=1){
            float coste = abs(nodos.at(i)->getPosicion().x - buscoX);
            //std::cout<<"NODO NUM: "<<nodos.at(i)->getNumero()<<" coste: "<<coste<<std::endl;
            if(coste<dif){

                dif = coste;
                aux = nodos.at(i);
            }
        }
    }
    //std::cout<<"NODO QUE SALE: "<<aux<<std::endl;
    return aux;
}

Nodo *Bot::getCercanoTotal(float x, float y){
    //std::cout<<"Pos entra: "<<x<<" "<<y<<std::endl;
    float pos2 = -10*(y/2);
    int posY = (int) pos2;
    float buscoY = posY/10.0f;

    float buscoX = x/2;
    //std::cout<<"Pos busco: "<<buscoX<<" "<<buscoY<<std::endl;
    Nodo *aux = NULL;
    int dif = 200;

    for(int i = 0; i< nodos.size(); i++){
      int coste = abs(nodos.at(i)->getPosicion().y - buscoY) + abs(nodos.at(i)->getPosicion().x - buscoX);
      //std::cout<<"COSTE: "<<coste<<" NODO: "<<nodos.at(i)->getNumero()<<std::endl;
      if(coste<dif){
          dif = coste;
          aux = nodos.at(i);
      }
    }
    return aux;
}

Nodo* Bot::buscaNumero(int num){
    Nodo *aux = NULL;

    for(int i = 0; i< nodos.size(); i++){
      if(nodos.at(i)->getNumero() == num) return nodos.at(i);
    }
    return aux;
}

void Bot::saltar(){

    if(muerto || fingiendoMuerte)
        return;
    if(!saltando){
      //float gapY = abs(m_gameObject.GetPosition().y - nodoy);
      //float gapX = abs(m_gameObject.GetPosition().x - nodox);
      //salto = (gapY*3);
      //std::cout<<"gapX: "<<gapX<<" gapY: "<<gapY<<" salto: "<<salto<<std::endl;
      b2Vec2 velV = m_gameObject.GetLinearVelocity();
      velV.y = salto;
      m_gameObject.SetLinearVelocity(velV);
      m_pClient->enviarSalto(1, mando);
    }
}


void Bot::morir(){
    if(!muerto && World::Inst()->getVivos() >1){
      //std::cout<<"******************************SOY BOT: "<<mando<<" Y MUERO"<<std::endl;
        paraMorir = false;
                BloodExplosion();
        if(cogiendo) Soltar();
        estado = MUERTO_DORMIDO;
        m_id = m_gameObject.SetMode(new PBDeadPlayer);
        if(direccion > 0 )
            m_gameObject.SetAngularVelocity(-0.5f);
        else
            m_gameObject.SetAngularVelocity(0.5f);
        muerto = true;
        m_pClient->enviarMuerto(mando);
    }
}

void Bot::despega(){
    if(!puedoCoger && !saltando){
      b2Vec2 velV = m_gameObject.GetLinearVelocity();
      velV.y = 4.0;
      m_gameObject.SetLinearVelocity(velV);
      m_pClient->enviarSalto(1, mando);
    }
}

void Bot::imprimirNodos(){
    for(int i = 0; i< nodos.size(); i++){
        std::cout<<" Nodo: "<<nodos.at(i)->getNumero()<<std::endl;
    }
}

void Bot::teletransportar(){
    pathfinding->remove(pathfinding->getUltimo()->getPosicion());
    if(pathfinding->getTamanyo() != 0)
        muevo(pathfinding->getUltimo()->getPosicion().x,pathfinding->getUltimo()->getPosicion().y);

    teletransportado = false;
    if(dir != 0) nextPos.x += (dir*2);
    else nextPos.x += 1.5f;

    velActual = m_gameObject.GetLinearVelocity();
    m_gameObject.SetPosition(b2Vec2(nextPos.x,nextPos.y));
    m_gameObject.SetRotation(m_gameObject.GetRotation());
    m_gameObject.SetLinearVelocity(velActual);
}

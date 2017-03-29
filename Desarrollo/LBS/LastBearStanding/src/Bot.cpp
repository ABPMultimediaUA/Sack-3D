#include "PhysicBody/PBDeadPlayer.h"
#include "PhysicBody/PBAlivePlayer.h"
#include "Bot.h"
#include "World.h"
#include "Usable.h"
#include "PathFinding/Lista.h"
#include "PathFinding/Nodo.h"
#include <ctime>
#include <stdlib.h>

Bot::Bot(b2Vec2 pos, int mando,irr::video::SColor color):Player( pos,  mando,color){
    enMuelle = false;
    salto = 20.0f;
    vel = 5;
    mandobusco=mando;
    estadoBot = 0;
}


void Bot::InicializaVariables(){
    players = World::Inst()->GetPlayers();
    spawners = World::Inst()->GetSpawners();
    nodos = World::Inst()->GetNodos();
    Nodo* aux ;
    posicionSpawn = getSpawnCercano();

    for(int i = 0; i< nodos.size(); i++){
        if(nodos.at(i)->getPosicion() ==  posicionSpawn )
            aux = nodos.at(i);
    }

    std::cout<<"Soy bot "<<mando<<" y voy a ir al spawn nodo "<<aux->getNumero()<<std::endl;
    Nodo* aux2 = getMas(m_gameObject.GetPosition().x, m_gameObject.GetPosition().y);
    calcularPathfinding(aux2, aux);
    if(pathfinding->getTamanyo() != 0)
        muevo(pathfinding->getUltimo()->getPosicion().x,pathfinding->getUltimo()->getPosicion().y);
}

void Bot::actualiza(){
    Player::actualiza();
    //if(mando==3) std::cout<<"Estado:: "<<estadoBot<<std::endl;

    switch(estadoBot){

        case 0: {
            //Estado de buscar Arma o huir sin estar armado
            buscaArma();
            break;
        }
        case 1: {
            //Estado de buscar jugador o huir estando armado
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

    else if(pathfinding->getTamanyo()<1){
        CogerTirar();

        if(cogiendo) estadoBot = 1;
        else if(World::Inst()->getVivos() >1){
            posicionSpawn.y = 0;
            posicionSpawn = getSpawnCercano();
            if(posicionSpawn.y != 0){
                Nodo* aux;
                for(int i = 0; i< nodos.size(); i++){
                    if(nodos.at(i)->getPosicion() ==  posicionSpawn )
                        aux = nodos.at(i);
                }

                //std::cout<<"SOY BOT "<<mando<<" y BUSCO ARMA"<<std::endl;
                calcularPathfinding(nodoFinIni,aux);

                if(pathfinding->getTamanyo()>1 && players.at(mando)->getMuerto() == false) pathfinding->remove(pathfinding->getUltimo()->getPosicion());
                else if(players.at(mando)->getMuerto() == false) colisionConNodo(pathfinding->getUltimo()->getNumero());

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
    if(mando != mandobusco && players.at(mandobusco)->getMuerto()==false
          && abs(players.at(mandobusco)->GetPosition().x - m_gameObject.GetPosition().x)<8
          && abs(players.at(mandobusco)->GetPosition().y - m_gameObject.GetPosition().y)<2  ){

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
        if(pathfinding->getTamanyo()>1 && players.at(mando)->getMuerto() == false) pathfinding->remove(pathfinding->getUltimo()->getPosicion());
        else if(players.at(mando)->getMuerto() == false) colisionConNodo(pathfinding->getUltimo()->getNumero());

        //pathfinding->imprimirLista();
        if(pathfinding->getTamanyo() != 0 && World::Inst()->getVivos() >1)
            muevo(pathfinding->getUltimo()->getPosicion().x,pathfinding->getUltimo()->getPosicion().y);
    }
}

void Bot::colisionConNodo(int nodo){
    if(pathfinding->getUltimo() && pathfinding->getUltimo()->getNumero() == nodo ){

        pathfinding->remove(pathfinding->getUltimo()->getPosicion());
        //if(pathfinding->getTamanyo() != 0 && World::Inst()->getVivos() >1)
            //muevo(pathfinding->getUltimo()->getPosicion().x,pathfinding->getUltimo()->getPosicion().y);
    }
}


void Bot::mover(){
    if(muerto || fingiendoMuerte){
        return;
    }
    direccion = dir = 0;
    if(moviendo == true){
        if((abs(m_gameObject.GetPosition().x - nodox) >= 1)
        && (abs(m_gameObject.GetPosition().x - nodox) <= 8)
        && (abs(m_gameObject.GetPosition().y) - abs(nodoy) >= 1)){
            //salto = (abs(m_gameObject.GetPosition().y) - abs(nodoy)) *4;
            saltar();
        }
        if( (abs(m_gameObject.GetPosition().x - nodox) < 0.5) ){
            if(pathfinding->getTamanyo() == 1){saltando = false;}

            if((!saltando || enMuelle) &&  pathfinding->getTamanyo() >= 1){
            //  pathfinding->remove(pathfinding->getUltimo()->getPosicion());
              if(pathfinding->getTamanyo() != 0 && World::Inst()->getVivos() >1)
                  muevo(pathfinding->getUltimo()->getPosicion().x,pathfinding->getUltimo()->getPosicion().y);
            }
        }
        else if(m_gameObject.GetPosition().x > nodox){direccion = dir = -1;}
        else if(m_gameObject.GetPosition().x < nodox){direccion = dir = 1;}
    }
    if(direccion != direccionA){
        direccionA = direccion;
        m_pClient->enviarMoviendo(dir, mando);
        //std::cout<<"ENVIOMOV"<<dir<<std::endl;
    }
    m_gameObject.SetLinearVelocity(b2Vec2 (dir*vel,m_gameObject.GetLinearVelocity().y));
    if(cogiendo) objCogido->setDireccion(dir);
}

void Bot::muevo(int x, int y){
    float ancho = ( 125.135 - 1.865 ) /(61*2);
    float alto = ( -68.585 +60.585 ) /(4*2);
    float posX= ancho * x;
    float posY= alto*y;
    nodox = posX;
    nodoy = posY;
    moviendo = true;
    dir = 0;
    saltando = false;
    dobleSaltando = false;
    enMuelle = false;
}

b2Vec2 Bot::getSpawnCercano(){
    b2Vec2 pos;
    int distancia=1000;
    for(int i = 0; i<spawners.size(); i++){

        int aux= abs(spawners.at(i)->GetPosition().x - m_gameObject.GetPosition().x)
               + abs(spawners.at(i)->GetPosition().y - ((-1)*m_gameObject.GetPosition().y));

        if(distancia> aux  && spawners.at(i)->GetCogiendo() == true){
            distancia = aux;
            pos = spawners.at(i)->GetPosition();
        }
    }
    return pos;
}

void Bot::calcularPathfinding(Nodo* inicial, Nodo* objetivo){

     Nodo* aux;
     Nodo* nodoInicial = inicial;
     Nodo* nodoDestino = objetivo;
     Nodo* nodoActual;
     if(nodoInicial == NULL || nodoDestino == NULL){
        std::cout<<"NODO INICIAL ES IGUAL A NULL"<<std::endl;
        return;
     }

     Lista listaAbierta;
     Lista listaCerrada;

     std::cout<<std::endl;
     std::cout<<"Empieza la la construccion del pathfinding"<<std::endl;
     std::cout<<"Soy el BOT numero: "<<mando<<std::endl;
     std::cout<<"Nodo inicial: "<<nodoInicial->getNumero()<<" Datos["<<nodoInicial->getPosicion().x<<","<<nodoInicial->getPosicion().y<<"]"<<std::endl;
     std::cout<<"Nodo destino: "<<nodoDestino->getNumero()<<" Datos["<<nodoDestino->getPosicion().x<<","<<nodoDestino->getPosicion().y<<"]"<<std::endl;
     std::cout<<std::endl;

     if(nodoInicial->getPosicion().x == nodoDestino->getPosicion().x && nodoInicial->getPosicion().y == nodoDestino->getPosicion().y){
          pathfinding = new Lista();
          pathfinding->insertar(nodoInicial);
          std::cout<<"<<<<<<<<<PATHFINDING>>>>>>>>>"<<std::endl;
          nodoFinIni= pathfinding->getHead();
          pathfinding->imprimirLista();
     }
     else if(nodoInicial->getPosicion().x != nodoDestino->getPosicion().x || nodoInicial->getPosicion().y != nodoDestino->getPosicion().y){
           nodoActual = new Nodo(nodoInicial->getPosicion(), irr::core::vector3df(0.1f,0.1f,0.1f), nodoInicial->getNumero(), 0, NULL);
           listaAbierta.insertar(nodoActual);
           while( listaAbierta.getTamanyo() > 0 && listaAbierta.buscaNodo2( nodoDestino->getPosicion().x, nodoDestino->getPosicion().y) == NULL) {
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
                           Nodo* aux = new Nodo (posicion, irr::core::vector3df(0.1f,0.1f,0.1f),  numero, coste, nodoActual);
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
           std::cout<<"<<<<<<<<<PATHFINDING>>>>>>>>>"<<std::endl;
           //pathfinding->remove(pathfinding->getUltimo()->getPosicion());
           nodoFinIni= pathfinding->getHead();
           pathfinding->imprimirLista();
           std::cout<<std::endl;
     }
}

Nodo *Bot::getMas(float x, float y){
    float pos = x + 0.3;
    int posX = (int) pos;
    float pos2 = -1* (y - 0.9);
    int posY = (int) pos2;
    Nodo *aux = NULL;
    int dif = 200;

    for(int i = 0; i< nodos.size(); i++){
        if(nodos.at(i)->getPosicion().y <= posY){

            int coste = abs(nodos.at(i)->getPosicion().y - posY) + abs(nodos.at(i)->getPosicion().x - posX);
            if(coste<dif){
                dif = coste;
                aux = nodos.at(i);
            }
        }
    }
    return aux;
}

Nodo *Bot::getCercanoTotal(float x, float y){
    //std::cout<<"Pos entra: "<<x<<" "<<y<<std::endl;
    float pos = x + 0.3;
    int posX = (int) pos;
    float pos2 = -1* (y - 0.9);
    int posY = (int) pos2;
    //std::cout<<"Pos busco: "<<posX<<" "<<posY<<std::endl;
    Nodo *aux = NULL;
    int dif = 200;

    for(int i = 0; i< nodos.size(); i++){
      int coste = abs(nodos.at(i)->getPosicion().y - posY) + abs(nodos.at(i)->getPosicion().x - posX);
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
        //if(abs(m_gameObject.GetPosition().y) - abs(nodoy) >= 7) salto = 15;
        //else                                                    salto = 12;
        b2Vec2 velV = m_gameObject.GetLinearVelocity();
        velV.y = salto;
        m_gameObject.SetLinearVelocity(velV);
        m_pClient->enviarSalto(1, mando);
    }
}

void Bot::morir(){
    if(!muerto && World::Inst()->getVivos() >1){std::cout<<"SOY BOT: "<<mando<<" Y MUERO"<<std::endl;
        paraMorir = false;
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

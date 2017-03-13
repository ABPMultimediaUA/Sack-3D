#include "Bot.h"
#include "World.h"
#include "PathFinding/Lista.h"
#include <ctime>
#include <stdlib.h>

Bot::Bot(b2Vec2 pos, int mando,irr::video::SColor color, char idr[]):Player( pos,  mando,color){
    enMuelle = false;
    salto = 18.0f;
    vel = 6;
    prueba = false;
    strncpy(id, idr, sizeof(id));
    direccion = 0;
    direccionA = 0;
}
void Bot::InicializaVariables(){
    srand(time(0));
    lista = World::Inst()->getListaNodos();
    std::cout<<"Soy el BOT numero: "<<mando<<std::endl;
    std::cout<<"Lista de nodos del Mapa"<<std::endl;
    lista->imprimirLista();
    calcularPathfinding(lista->buscaNumero(rand() % lista->getTamanyo()));
    muevo(pathfinding->getUltimo()->getPosicion().x,pathfinding->getUltimo()->getPosicion().y);
}
void Bot::actualiza(){
    Player::actualiza();
    if((!saltando || enMuelle) && (pathfinding->getTamanyo() < 1)){
        calcularPathfinding(lista->buscaNumero(rand() % lista->getTamanyo()));
    }
}
void Bot::mover(){
    if(muerto || fingiendoMuerte){
        return;
    }
    direccion = dir = 0;
     if(moviendo == true){
        if((abs(m_pBody->GetPosition().x - nodox) >= 1)
        && (abs(m_pBody->GetPosition().x - nodox) <= 8)
        && (abs(m_pBody->GetPosition().y) - abs(nodoy) >= 5)){
            saltar();
        }
        if( (abs(m_pBody->GetPosition().x - nodox) <= 1)){
            if(pathfinding->getTamanyo() == 1){saltando = false;}
            if((!saltando || enMuelle) &&  pathfinding->getTamanyo() >= 1){
              pathfinding->remove(pathfinding->getUltimo()->getPosicion());
              if(pathfinding->getTamanyo() != 0) {muevo(pathfinding->getUltimo()->getPosicion().x,pathfinding->getUltimo()->getPosicion().y);}
            }
        }
        else if(m_pBody->GetPosition().x > nodox){direccion = dir = -1;}
        else if(m_pBody->GetPosition().x < nodox){direccion = dir = 1;}
    }
    if(direccion != direccionA){
        direccionA = direccion;
        m_pClient->enviarMoviendo(dir, mando);
        //std::cout<<"ENVIOMOV"<<dir<<std::endl;
    }
    m_pBody->SetLinearVelocity(b2Vec2 (dir*vel, m_pBody->GetLinearVelocity().y));
    if(cogiendo) objCogido->setDireccion(dir);
}

void Bot::muevo(int x, int y){
    float ancho = ( 125.135 - 1.865 ) /(61*2);
    float alto = ( -68.585 +60.585 ) /(4*2);
    float posX= ancho * y;
    float posY= alto*x;
    nodox = posX;
    nodoy = posY;
    moviendo = true;
    dir = 0;
    saltando = false;
    dobleSaltando = false;
    enMuelle = false;
}


void Bot::calcularPathfinding(Nodo* objetivo){
   Nodo* aux;
   Nodo* nodoInicial = lista->getMas(m_pBody->GetPosition().x, m_pBody->GetPosition().y);


  Nodo* nodoDestino = objetivo;
  Nodo* nodoActual;
  if(nodoInicial == NULL) return;
  if(prueba == false){
    prueba = true;
  }
  else{    if(nodoInicial->getPosicion().y != head->getPosicion().y) return;
  }

  Lista listaAbierta;
  Lista listaCerrada;

  std::cout<<std::endl;
  std::cout<<"Empieza la la construccion del pathfinding"<<std::endl;
  std::cout<<"Soy el BOT numero: "<<mando<<std::endl;
  std::cout<<"Nodo inicial: "<<nodoInicial->getNumero()<<" Datos["<<nodoInicial->getPosicion().x<<","<<nodoInicial->getPosicion().y<<"]"<<std::endl;
  std::cout<<"Nodo destino: "<<nodoDestino->getNumero()<<" Datos["<<nodoDestino->getPosicion().x<<","<<nodoDestino->getPosicion().y<<"]"<<std::endl;
  std::cout<<std::endl;

  if(nodoInicial->getPosicion().x != nodoDestino->getPosicion().x || nodoInicial->getPosicion().y != nodoDestino->getPosicion().y){
        nodoActual = new Nodo(nodoInicial->getPosicion(), nodoInicial->getNumero(), 0, NULL);
        listaAbierta.insertar(nodoActual);
        while( listaAbierta.getTamanyo() > 0 && listaAbierta.buscaNodo2( nodoDestino->getPosicion().x, nodoDestino->getPosicion().y) == NULL) {
            nodoActual = listaAbierta.getMenorCosto();
            listaAbierta.remove(nodoActual->getPosicion());

            nodoActual->setNext(NULL);
            listaCerrada.insertar(nodoActual);
            for(int i = 0; i<lista->buscaNumero(nodoActual->getNumero())->getAdyacentes().size(); i++){

                if(listaCerrada.buscaNumero( lista->buscaNumero(nodoActual->getNumero())->getAdyacentes()[i] ) == NULL
                    && listaAbierta.buscaNumero( lista->buscaNumero(nodoActual->getNumero())->getAdyacentes()[i] ) == NULL){
                        int numero = lista->buscaNumero(nodoActual->getNumero())->getAdyacentes()[i];
                        b2Vec2 posicion;
                        posicion.x = lista->buscaNumero(numero)->getPosicion().x;
                        posicion.y = lista->buscaNumero(numero)->getPosicion().y;
                        int coste = abs(posicion.x-nodoDestino->getPosicion().x) + abs(posicion.y -nodoDestino->getPosicion().y);
                        Nodo* aux = new Nodo (posicion, numero, coste, nodoActual);
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
        head = pathfinding->getHead();
        std::cout<<"<<<<<<<<<PATHFINDING>>>>>>>>>"<<std::endl;
        pathfinding->imprimirLista();
        std::cout<<std::endl;
  }
}

void Bot::saltar(){
    std::cout<<mando<<std::endl;
    if(muerto)
        return;
    if(fingiendoMuerte){
        b2Vec2 velV;
        velV.x = 0;
        velV.y = 2;
        m_pBody->SetLinearVelocity(velV);
        m_pBody->ApplyAngularImpulse(rand()%4 - 2);
        return;
    }
    if(!saltando){
        b2Vec2 velV = m_pBody->GetLinearVelocity();
        velV.y = salto;
        m_pBody->SetLinearVelocity(velV);
        m_pClient->enviarSalto(1, mando);
    }
    else if(!dobleSaltando){
        b2Vec2 velV = m_pBody->GetLinearVelocity();
        velV.y = salto*3/4;
        m_pBody->SetLinearVelocity(velV);
        dobleSaltando = true;
        m_pClient->enviarSalto(2, mando);
    }
}

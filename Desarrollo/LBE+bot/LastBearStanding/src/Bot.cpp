#include "Bot.h"
#include "World.h"
#include "PathFinding/Lista.h"

Bot::Bot(b2Vec2 pos, int mando):Player( pos,  mando){
    enMuelle = false;
     salto = 18.0f;
}
void Bot::InicializaVariables(){
    lista = World::Inst()->getListaNodos();
    lista->imprimirLista();
    calcularPathfinding(lista->buscaNumero(rand() % 6 + 4));
    muevo(pathfinding->getUltimo()->getPosicion().x,pathfinding->getUltimo()->getPosicion().y);
}
void Bot::actualiza(){
    Player::actualiza();
    if((pathfinding->getTamanyo() == 1)){
        calcularPathfinding(lista->buscaNumero(rand() % lista->getTamanyo()));
    }
}
void Bot::mover(){
    if(muerto || fingiendoMuerte){
        return;
    }
    dir = 0;
    if(mando == 1 && moviendo == true){
        //std::cout<<(abs(body->GetPosition().y) - abs(nodoy) >= 5)<<std::endl;
        if((abs(body->GetPosition().x - nodox) <= 8)
        && (abs(body->GetPosition().y) - abs(nodoy) >= 5)){
            saltar();
        }
        if( abs(body->GetPosition().x - nodox) <= 2){
            if((!saltando || enMuelle) &&  pathfinding->getTamanyo() > 1){
                pathfinding->remove(pathfinding->getUltimo()->getPosicion());
                pathfinding->imprimirLista();
                muevo(pathfinding->getUltimo()->getPosicion().x,pathfinding->getUltimo()->getPosicion().y);
            }
            if(!(pathfinding->getTamanyo() > 1)){
                saltando = false;
                dobleSaltando = false;
                enMuelle = false;
            }
        }
        else if(body->GetPosition().x > nodox){dir = -1;}
        else if(body->GetPosition().x < nodox){dir = 1;}
    }

    body->SetLinearVelocity(b2Vec2 (dir*vel, body->GetLinearVelocity().y));
    if(cogiendo) objCogido->setDireccion(dir);
}

void Bot::muevo(int x, int y){
    float ancho = ( 125.135 - 1.865 ) /61; //ancho del tiled
    float alto = ( -68.585 +60.585 ) /4; //alto del tiled
    float posX= ancho * y;
    float posY= alto*x;
    saltando = false;
    dobleSaltando = false;
    enMuelle = false;
    nodox = posX;
    nodoy = posY;
    moviendo = true;
    dir = 0;
}


void Bot::calcularPathfinding(Nodo* objetivo){

  Nodo* aux;
  Nodo* nodoInicial = lista->getMas(body->GetPosition().x, body->GetPosition().y);
  Nodo* nodoDestino = objetivo;
  Nodo* nodoActual;

  /*
  Lista* listaAbierta = new Lista();
  Lista* listaCerrada = new Lista();
  */
  Lista listaAbierta;
  Lista listaCerrada;

  std::cout<<std::endl;
  std::cout<<"Empieza la la construccion del pathfinding"<<std::endl;
  std::cout<<nodoInicial<<nodoDestino<<std::endl;
  std::cout<<"Nodo inicial: "<<nodoInicial->getNumero()<<" Datos["<<nodoInicial->getPosicion().x<<","<<nodoInicial->getPosicion().y<<"]"<<std::endl;
  std::cout<<"Nodo destino: "<<nodoDestino->getNumero()<<" Datos["<<nodoDestino->getPosicion().x<<","<<nodoDestino->getPosicion().y<<"]"<<std::endl;
  std::cout<<std::endl;

  //START A*
  if(nodoInicial->getPosicion().x != nodoDestino->getPosicion().x || nodoInicial->getPosicion().y != nodoDestino->getPosicion().y){

        nodoActual = new Nodo(nodoInicial->getPosicion(), nodoInicial->getNumero(), 0, NULL);
        listaAbierta.insertar(nodoActual);

        while( listaAbierta.getTamanyo() > 0 && listaAbierta.buscaNodo2( nodoDestino->getPosicion().x, nodoDestino->getPosicion().y) == NULL) {

            nodoActual = listaAbierta.getMenorCosto();
            listaAbierta.remove(nodoActual->getPosicion());
            nodoActual->setNext(NULL);
            listaCerrada.insertar(nodoActual);

            for(int i = 0; i<lista->buscaNumero(nodoActual->getNumero())->getAdyacentes().size(); i++){

                if(listaCerrada.buscaNumero( lista->buscaNumero(nodoActual->getNumero())->getAdyacentes()[i] ) ==NULL
                    && listaAbierta.buscaNumero( lista->buscaNumero(nodoActual->getNumero())->getAdyacentes()[i] ) == NULL){
                        int numero = lista->buscaNumero(nodoActual->getNumero())->getAdyacentes()[i];
                        b2Vec2 posicion;
                        posicion.x = lista->buscaNumero(numero)->getPosicion().x;
                        posicion.y = lista->buscaNumero(numero)->getPosicion().y;
                        int coste = abs(posicion.x-nodoDestino->getPosicion().x) + abs(posicion.y -nodoDestino->getPosicion().y);
                        Nodo* aux = new Nodo (posicion, numero, coste, nodoActual);
                        listaAbierta.insertar(aux);
                    }
            }   //end for
        }       //end while end pathfinding

        nodoActual = listaAbierta.buscaNodo2(nodoDestino->getPosicion().x, nodoDestino->getPosicion().y);
        pathfinding = new Lista();

        //save pathfinding List
        while(nodoActual!=NULL){
            pathfinding->insertar(nodoActual);
            nodoActual = nodoActual->getPadre();
        }

        std::cout<<"<<<<<<<<<PATHFINDING>>>>>>>>>"<<std::endl;
        pathfinding->imprimirLista();
        std::cout<<std::endl;
  } //end if
}


 //Lista listaCerrada;
 //Lista listaAbierta;
 //GameResource<Nodo> aux;
 //Nodo* nodoInicial = lista->getMas(body->GetPosition().x, body->GetPosition().y);
 //std::cout<<std::endl;
 //std::cout<<"Empieza la la construccion del pathfinding"<<std::endl;
 //std::cout<<std::endl;
 //std::cout<<"Nodo inicial: "<<nodoInicial->getNumero()<<" Datos["<<nodoInicial->getPosicion().x<<","<<nodoInicial->getPosicion().y<<"]"<<std::endl;
 //std::cout<<"Nodo destino: "<<objetivo->getNumero()<<" Datos["<<objetivo->getPosicion().x<<","<<objetivo->getPosicion().y<<"]"<<std::endl;
 //std::cout<<std::endl;

 ////START A*
 //if(nodoInicial->getPosicion().x != objetivo->getPosicion().x || nodoInicial->getPosicion().y != objetivo->getPosicion().y){
 //      GameResource<Nodo> nodoActual;
 //      nodoActual.Reset(new Nodo(nodoInicial->getPosicion(), nodoInicial->getNumero(), 0, NULL));
 //      listaAbierta.insertar(nodoActual.Get());
 //      while( listaAbierta.getTamanyo() > 0 && listaAbierta.buscaNodo2( objetivo->getPosicion().x, objetivo->getPosicion().y) == NULL) {
 //          nodoActual.Reset(listaAbierta.getMenorCosto());
 //          listaAbierta.remove(nodoActual.Get()->getPosicion());
 //          nodoActual.Get()->setNext(NULL);
 //          listaCerrada.insertar( nodoActual.Get());
 //          for(int i = 0; i<lista->buscaNumero(nodoActual.Get()->getNumero())->getAdyacentes().size(); i++){
 //              if(listaCerrada.buscaNumero( lista->buscaNumero(nodoActual.Get()->getNumero())->getAdyacentes()[i] ) ==NULL
 //                  && listaAbierta.buscaNumero( lista->buscaNumero(nodoActual.Get()->getNumero())->getAdyacentes()[i] ) == NULL){
 //                  int numero = lista->buscaNumero(nodoActual.Get()->getNumero())->getAdyacentes()[i];
 //                  b2Vec2 posicion;
 //                  posicion.x = lista->buscaNumero(numero)->getPosicion().x;
 //                  posicion.y = lista->buscaNumero(numero)->getPosicion().y;
 //                  int coste = abs(posicion.x-objetivo->getPosicion().x) + abs(posicion.y -objetivo->getPosicion().y);
 //                  aux.Reset(new Nodo (posicion, numero, coste, nodoActual.Get()));
 //                  listaAbierta.insertar(aux.Get());
 //              }
 //          }
 //      }
 //      nodoActual.Reset(listaAbierta.buscaNodo2(objetivo->getPosicion().x, objetivo->getPosicion().y));
 //      pathfinding.Reset(new Lista);

 //      //save pathfinding List
 //      while(nodoActual.Get()!=NULL){
 //          pathfinding.Get()->insertar(nodoActual.Get());
 //          nodoActual.Reset(nodoActual.Get()->getPadre());
 //      }

 //      std::cout<<"<<<<<<<<<PATHFINDING>>>>>>>>>"<<std::endl;
 //      pathfinding.Get()->imprimirLista();
 //      std::cout<<std::endl;
 //} //end if

#include "Map.h"
#include "IrrManager.h"
#include "Platform.h"
#include "PhysicWorld.h"
#include "GameResource.h"
#include <sstream>

#define PLAYER       1
#define MUELLE       2
#define TELEPORT     3
#define PLATAFORMA   4
#define ARMA         5
#define NODO         6
#define PISTOLA      1
#define ESCOPETA     2
#define GRANADA      3

Map::Map(irr::core::stringw file){

     int capa = 0;
     int player = 1;
     int maph = 36;
     int mapw = 64;
     nodoActual = nullptr;
     irr::io::IXMLReader* xml = IrrManager::Instance()->createXMLReader(file);
     nodos = new Lista();

     while (xml->read()){


          if(irr::core::stringw("objectgroup") == xml->getNodeName() && xml->getAttributeValue(L"name")){
               if     (irr::core::stringw("Colisiones")   == xml->getAttributeValue(L"name")) capa = PLATAFORMA;
               else if(irr::core::stringw("Muelles")      == xml->getAttributeValue(L"name")) capa = MUELLE;
               else if(irr::core::stringw("Teleports")    == xml->getAttributeValue(L"name")) capa = TELEPORT;
               else if(irr::core::stringw("Armas")        == xml->getAttributeValue(L"name")) capa = ARMA;
               else if(irr::core::stringw("Players")      == xml->getAttributeValue(L"name")) capa = PLAYER;
               else if(irr::core::stringw("Nodos")        == xml->getAttributeValue(L"name")) capa = NODO;
          }


          else{
               int x = xml->getAttributeValueAsInt(L"x");
               int y = xml->getAttributeValueAsInt(L"y");
               int width = xml->getAttributeValueAsInt(L"width");
               int height = xml->getAttributeValueAsInt(L"height");
               if (xml->getNodeType() == irr::io::EXN_ELEMENT && irr::core::stringw("object") == xml->getNodeName()){
                    switch(capa){
                         case PLATAFORMA:{
                                   Platform(irr::core::vector3df(x+(width/2),-1*(y+(height/2)),0),irr::core::vector3df(width, height, 2),irr::video::SColor(255, 186, 141, 5));
                         break;}
                         case PLAYER:{
                                   PhysicWorld::Instance()->CreatePlayer(new Player(b2Vec2(x+(width/2),-1*(y-(height/2))),player));
                                   player++;
                         break;}
                         case NODO:{

                          int n;
                          std::wstring ads;
                          do{
                              n = xml->getAttributeValueAsInt(L"name");
                              //Crear el nodo
                              Nodo *a = new Nodo(b2Vec2((y-2)/2, (x/2)), n, 0, nullptr);
                              //meter nodos adyacentes
                              ads = xml->getAttributeValue(L"type");
                              std::string A( ads.begin(), ads.end() );
                              std::istringstream ss(A);
                              std::string token;
                              while(std::getline(ss, token, ',')) {
                                  int integer = atoi( token.c_str() );
                                  a->addAdyacente(integer);
                              }
                              nodos->insertar(a);


                          }while(irr::core::stringw("object") != xml->getNodeName());

                        break;}
                         case TELEPORT:{
                                   int id = 0, partner = 0;
                                   do{
                                        if(irr::core::stringw("property") == xml->getNodeName()){
                                             if     (irr::core::stringw("Id") == xml->getAttributeValue(L"name")){
                                                  id = xml->getAttributeValueAsInt(L"value");
                                             }
                                             else if(irr::core::stringw("Partner") == xml->getAttributeValue(L"name")){
                                                  partner = xml->getAttributeValueAsInt(L"value");
                                             }
                                        }
                                        xml->read();
                                   }while(irr::core::stringw("object") != xml->getNodeName());
                                   PhysicWorld::Instance()->CreateTeleport(new Teleport(id, partner, irr::core::vector3df(x+(width/2),-1*(y-(height/2)),0)));
                         break;}
                         case MUELLE:{
                                   int fuerza = 80;
                                   do{
                                        if(irr::core::stringw("property") == xml->getNodeName()){
                                             if     (irr::core::stringw("Fuerza") == xml->getAttributeValue(L"name")){
                                                  fuerza = xml->getAttributeValueAsFloat(L"value");
                                             }
                                        }
                                        xml->read();
                                   }while(irr::core::stringw("object") != xml->getNodeName());
                                   PhysicWorld::Instance()->CreateMuelle(new Muelle(fuerza,  irr::core::vector3df(x+(width/2),-1*(y-(height/2)),0)));
                         break;}
                         case ARMA:{
                              int tipo, modelo;
                              do{
                                   if(irr::core::stringw("property") == xml->getNodeName()){
                                        if     (irr::core::stringw("Tipo") == xml->getAttributeValue(L"name")){
                                             tipo = xml->getAttributeValueAsFloat(L"value");
                                        }
                                        else if(irr::core::stringw("Modelo") == xml->getAttributeValue(L"name")){
                                             modelo = xml->getAttributeValueAsFloat(L"value");
                                        }
                                   }
                                   xml->read();
                              }while(irr::core::stringw("object") != xml->getNodeName());
                              switch(tipo){
                                   case PISTOLA:{
                                        PhysicWorld::Instance()->GetCogibles()->push_back(PhysicWorld::Instance()->CreatePistola(
                                             new Pistola(modelo,b2Vec2(x+(width/2),-1*(y-(height/2)))))->Get()
                                        );
                                   break;}
                                   case ESCOPETA:{
                                        PhysicWorld::Instance()->GetCogibles()->push_back(PhysicWorld::Instance()->CreateEscopeta(
                                             new Escopeta(modelo,b2Vec2(x+(width/2),-1*(y-(height/2)))))->Get()
                                        );
                                   break;}
                                   case GRANADA:{
                                        PhysicWorld::Instance()->GetCogibles()->push_back(PhysicWorld::Instance()->CreateGranada(
                                             new Granada(modelo,b2Vec2(x+(width/2),-1*(y-(height/2)))))->Get()
                                        );
                                   break;}
                              }
                    break;}
                    }
               }
          }
     }
}


//funcion que calcula los nodos de partida y destino e imprime el pathfingin

void Map::calcularPathfinding(float x, float y, Nodo* objetivo){

  Nodo* aux;
  nodoInicial = nodos->getMas(x, y);
  nodoDestino = objetivo;

  listaAbierta = new Lista();
  listaCerrada = new Lista();

  std::cout<<std::endl;
  std::cout<<"Empieza la la construccion del pathfinding"<<std::endl;
  std::cout<<std::endl;
  std::cout<<"Nodo inicial: "<<nodoInicial->getNumero()<<" Datos["<<nodoInicial->getPosicion().x<<","<<nodoInicial->getPosicion().y<<"]"<<std::endl;
  std::cout<<"Nodo destino: "<<nodoDestino->getNumero()<<" Datos["<<nodoDestino->getPosicion().x<<","<<nodoDestino->getPosicion().y<<"]"<<std::endl;
  std::cout<<std::endl;

  //START A* 
  if(nodoInicial->getPosicion().x != nodoDestino->getPosicion().x && nodoInicial->getPosicion().y != nodoDestino->getPosicion().y){

        nodoActual = new Nodo(nodoInicial->getPosicion(), nodoInicial->getNumero(), 0, nullptr);
        listaAbierta->insertar(nodoActual);

        while( listaAbierta->getTamanyo() > 0 && listaAbierta->buscaNodo2( nodoDestino->getPosicion().x, nodoDestino->getPosicion().y) == nullptr) {

            nodoActual = listaAbierta->getMenorCosto();
            listaAbierta->remove(nodoActual->getPosicion());
            nodoActual->setNext(nullptr);
            listaCerrada->insertar(nodoActual);

            for(int i = 0; i<nodos->buscaNumero(nodoActual->getNumero())->getAdyacentes().size(); i++){

                if(listaCerrada->buscaNumero( nodos->buscaNumero(nodoActual->getNumero())->getAdyacentes()[i] ) ==nullptr
                    && listaAbierta->buscaNumero( nodos->buscaNumero(nodoActual->getNumero())->getAdyacentes()[i] ) == nullptr)

                        comprobar(i);
            }   //end for
        }       //end while end pathfinding

        nodoActual = listaAbierta->buscaNodo2(nodoDestino->getPosicion().x, nodoDestino->getPosicion().y);
        pathfinding = new Lista();

        //save pathfinding List
        while(nodoActual!=nullptr){
            pathfinding->insertar(nodoActual);
            nodoActual = nodoActual->getPadre();
        }

        std::cout<<"<<<<<<<<<PATHFINDING>>>>>>>>>"<<std::endl;
        pathfinding->imprimirLista();
        std::cout<<std::endl;
  } //end if
}

void Map::comprobar(int i){
    int numero = nodos->buscaNumero(nodoActual->getNumero())->getAdyacentes()[i];
    b2Vec2 posicion;
    posicion.x = nodos->buscaNumero(numero)->getPosicion().x;
    posicion.y = nodos->buscaNumero(numero)->getPosicion().y;
    int coste = abs(posicion.x-nodoActual->getPosicion().x) + abs(posicion.y -nodoActual->getPosicion().y);
    Nodo* aux = new Nodo (posicion, numero, coste, nodoActual);
    listaAbierta->insertar(aux);
}


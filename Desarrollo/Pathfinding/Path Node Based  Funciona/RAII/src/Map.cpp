#include "Map.h"
#include "IrrManager.h"
#include "Platform.h"
#include "PhysicWorld.h"
#include "GameResource.h"

#define PLAYER       1
#define MUELLE       2
#define TELEPORT     3
#define PLATAFORMA   4
#define ARMA         5
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

     while (xml->read()){

          if(irr::core::stringw("data") == xml->getNodeName()  && xml->getAttributeValue(L"encoding")){

              for(int i =0; i< maph; i++){
                  for(int j=0; j<mapw; j++){
                      matriz[i][j]=0;
                  }
              }
              char cadena[15000];
              char separador[] = ",";
              char *trozo = NULL;

              do{
                  wcstombs(cadena, xml-> getNodeData(), 15000);
                  int fila = 0; //maximo 36
                  int columna = 0; //maximo 64

                  trozo = strtok (cadena, separador);//separamos por coma y la recorremos
                  int numero = 0;
                  nodos = new Lista();

                  while(trozo!=nullptr && fila<maph && columna <mapw){
                      if(atoi(trozo) == 651716){
                          std::cout<<"soy nodo: "<<numero<<" "<<fila<<" "<<columna<<std::endl;
                          posicion.x = fila;
                          posicion.y = columna;
                          nodoActual = new Nodo (posicion, numero, 0, nullptr);
                          nodos->insertar(nodoActual);
                          numero ++;
                      }

                      matriz[fila][columna] = atoi(trozo);
                      trozo = strtok( NULL, separador);
                      columna++;

                      if(columna == 64){
                          columna = 0;
                          fila++;
                      }
                  }//fin while

                  nodos->imprimirLista();

                  xml->read();

                 }while(irr::core::stringw("data") != xml->getNodeName());



                 //std::cout<<"matri:: "<<matriz[0][0]<<std::endl;
                 //std::cout<<"matri:: "<<matriz[35][63]<<std::endl;
          }
          if(irr::core::stringw("objectgroup") == xml->getNodeName() && xml->getAttributeValue(L"name")){
               if     (irr::core::stringw("Colisiones")   == xml->getAttributeValue(L"name")) capa = PLATAFORMA;
               else if(irr::core::stringw("Muelles")      == xml->getAttributeValue(L"name")) capa = MUELLE;
               else if(irr::core::stringw("Teleports")    == xml->getAttributeValue(L"name")) capa = TELEPORT;
               else if(irr::core::stringw("Armas")        == xml->getAttributeValue(L"name")) capa = ARMA;
               else if(irr::core::stringw("Players")      == xml->getAttributeValue(L"name")) capa = PLAYER;
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

    //nodoCercano(1.865, -68.585);
}


//funcion que calcula los nodos de partida y destino e imprime el pathfingin

void Map::nodoCercano(float x, float y, Nodo* objetivo){
  std::cout<<"Empieza la la construccion del pathfinding"<<std::endl;
  nodoInicial = nullptr;
  nodoDestino = nullptr;
  nodoInicial = nodos->getMas(x, y);
  //nodoDestino = nodos->getMas(nodoFinx, nodoFiny);
  nodoDestino = objetivo;

  std::cout<<"Nodo destino: "<<nodoDestino->getNumero()<<std::endl;

  Nodo* aux;

  listaAbierta = new Lista();
  listaCerrada = new Lista();

  if(nodoInicial->getDatos().x == nodoDestino->getDatos().x && nodoInicial->getDatos().y == nodoDestino->getDatos().y){
    std::cout<<"Nodo Iincial y Nodo Destino son iguales, no hay pathfinding disponible"<<std::endl;
  }
  else{//comienza pathfinding algoritmo A*

    nodoActual = new Nodo(nodoInicial->getDatos(), nodoInicial->getNumero(), 0, nullptr);
    listaAbierta->insertar(nodoActual);

    //añadimos primeros nodos a la lista abierta
    for(int i = 0; i<18; i++){
        if(mAdyacencia[nodoActual->getNumero()][i]!=0 && mAdyacencia[nodoActual->getNumero()][i]!=1){
            b2Vec2 posicion;
            posicion.x = nodos->buscaNumero(i)->getDatos().x;
            posicion.y = nodos->buscaNumero(i)->getDatos().y;
            int numero = i;
            int coste = nodos->buscaNumero(i)->getNumero();
            aux = new Nodo (posicion, numero, coste, nodoActual);
            listaAbierta->insertar(aux);
        }
    }

    listaAbierta->remove(nodoActual->getDatos());
    listaCerrada->insertar(nodoActual);

    while( listaAbierta->getTamanyo() > 0 && listaAbierta->buscaNodo( nodoDestino->getDatos().x, nodoDestino->getDatos().y) == false) {

        nodoActual = listaAbierta->getMenorCosto();
        listaAbierta->remove(nodoActual->posicion);
        nodoActual->setNext(nullptr);
        listaCerrada->insertar(nodoActual);

        posicion = nodoActual->getDatos();
        int i = posicion.x;
        int j = posicion.y;

        for(int i = 0; i<18; i++){
            if(mAdyacencia[nodoActual->getNumero()][i]!=0 && mAdyacencia[nodoActual->getNumero()][i]!=1
              && listaCerrada->buscaNodo(nodos->buscaNumero(i)->getDatos().x, nodos->buscaNumero(i)->getDatos().y)==false){

                if(listaAbierta->buscaNodo(nodos->buscaNumero(i)->getDatos().x, nodos->buscaNumero(i)->getDatos().y)==false){
                    b2Vec2 posicion;
                    posicion.x = nodos->buscaNumero(i)->getDatos().x;
                    posicion.y = nodos->buscaNumero(i)->getDatos().y;
                    int numero = i;
                    int coste = nodos->buscaNumero(i)->getNumero();
                    aux = new Nodo (posicion, numero, coste, nodoActual);
                    listaAbierta->insertar(aux);
                }
            }
        }

    }
    //fin pathfinding;
    
    nodoActual = listaAbierta->buscaNodo2(nodoDestino->getDatos().x, nodoDestino->getDatos().y);
    camino = new Lista();
    pathfinding = new Lista();
    //almacenamos camino en lista
    while(nodoActual!=nullptr){
        camino->insertar(nodoActual);
        nodoActual = nodoActual->getPadre();
    }
    
    pathfinding = camino;
    std::cout<<"<<<<<<<<<PATHFINDING>>>>>>>>>"<<std::endl;
    pathfinding->imprimirLista();
    std::cout<<std::endl;

  }






}


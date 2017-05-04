
#include "Map.h"
#include "BearManager.h"
#include "Platform.h"
#include "Spawner.h"
#include "Muelle.h"
#include "Teleport.h"
#include "Cogible.h"
#include "Pistola.h"
#include "Escopeta.h"
#include "Granada.h"
#include "Bot.h"
#include "PathFinding/Nodo.h"
#include "PathFinding/Lista.h"
#include "GameObject.h"
#include "PhysicBody/PBDeadPlayer.h"
#include "SDL.h"

Map::Map(const char* doc){
    player = false;
    numPlayer = 0;
    playerRed = 0;
    int a=0;
    nodos.Reset(new Lista());

    const char* layer = "0";
    tinyxml2::XMLDocument xml_doc;
    tinyxml2::XMLError eResult= xml_doc.LoadFile(doc);
    if(eResult != tinyxml2::XML_SUCCESS){
        std::cout<<"ERROR al abrir fichero"<<std::endl;
    }

     tinyxml2::XMLElement *mapa = xml_doc.FirstChildElement("map");
    //ATRIBUTOS DEL MAPA
    /*
    mapa->QueryAttribute("width", &m_width);
    mapa->QueryAttribute("height", &m_height);
    mapa->QueryAttribute("tilewidth", &tilewidth);
    mapa->QueryAttribute("tileheight", &tileheight);
    */

    tinyxml2::XMLElement *objectgroups = mapa->FirstChildElement("objectgroup");
    while(objectgroups){
      layer = objectgroups->Attribute("name");
      leerObjGroup(layer, objectgroups);

      objectgroups = objectgroups->NextSiblingElement("objectgroup");
    }
    timeEspera = SDL_GetTicks();

}

int Map::getTime(){
    int time = (int) SDL_GetTicks()-timeEspera;
    return time;
}

Lista* Map::getListaNodos(){
  return nodos.Get();
}
void Map::AddSpawner(){
     posi.y=posi.y-0.035f;
     World::Inst()->AddSpawner(new  Spawner(name,typeInt,posi));
}
void Map::AddPlatform(){
    World::Inst()->AddPlatform(new Platform(false,posi, glm::vec3(width/10.f, height/10.f, 2/10.f)));
}
void Map::AddMuelle(){
     World::Inst()->AddMuelle(new Muelle(typeInt, b2Vec2(x,y)));
}
void Map::AddTeleport(){
    posi.y=posi.y-0.15f;
     World::Inst()->AddTeleport(new Teleport(name, typeInt, posi));
}
void Map::AddArma(){
    switch(name){
         case 1:{
              World::Inst()->AddCogible(new  Pistola(NULL, typeInt,posi));
         break;}
         case 2:{
              World::Inst()->AddCogible(new Escopeta(NULL, typeInt,posi));
         break;}
         case 3:{
              World::Inst()->AddCogible(new  Granada(NULL, typeInt,posi));
         break;}
    }
 }
void Map::AddPlayer(){
    int id = (*Client::Inst()->getIdCliente())-'0';
    if(numPlayer == id){
      World::Inst()->AddPlayer(new Player(posi,numPlayer));
   }
   if(playerRed < Client::Inst()->getNumPlayersRed()){
       for(int i=0;i<Client::Inst()->getNumPlayersRed()&&playerRed<Client::Inst()->getNumPlayersRed();i++){
        if(numPlayer==(*Client::Inst()->playersRed[i].id)-'0'){
        World::Inst()->AddPlayer(new PlayerRed(b2Vec2(x,y),(*Client::Inst()->playersRed[i].id)-'0', Client::Inst()->playersRed[i].id));
        playerRed++;
        }
      }
   }
   else{
      if(numPlayer > Client::Inst()->getNumPlayersRed()){
          if(id == 0){
              char aux[30];
              sprintf(aux, "%.0f", (float)numPlayer);
              World::Inst()->AddPlayer(new Bot(posi,numPlayer, aux));
          }else{
              char aux[30];
              sprintf(aux, "%.0f", (float)numPlayer);
              World::Inst()->AddPlayer(new PlayerRed(posi,numPlayer, aux));
          }
      }
   }
   numPlayer++;
}
void Map::AddPincho(){
     World::Inst()->AddPlatform(new Platform(true,posi, glm::vec3(width/10.f, height/10.f, 2/10.f)));
}
void Map::AddNodo(){

    posi.y=posi.y-0.1;
    Nodo *a = World::Inst()->AddNodo(new Nodo(posi,glm::vec3(0.15f, 0.1f, 1), name, 0, NULL));
    char * token;
    char str[100];
    strcpy(str, typeString);
    token = strtok (str,",");
    while (token != NULL){
        int i = atoi(token);
        a->addAdyacente(i);
        token = strtok (NULL, ",");
    }
    nodos.Get()->insertar(a);
}


void Map::leerObjGroup(const char* layer, tinyxml2::XMLElement *objgroup){
    tinyxml2::XMLElement *objeto = objgroup->FirstChildElement("object");
    while(objeto){
        leerElement(objeto);
        const Layer2Method * it = layers;
        while(it->layer != "0"){
             if(strcmp(it->layer, layer) == 0 ){
                 (this->*it->Layer2Method::p)();
                 break;
             }
             it++;
        }

        objeto = objeto->NextSiblingElement("object");
    }

}

void Map::leerElement(tinyxml2::XMLElement *element){
    /*
    //variables de los object
    float x, y, height, width;
    const char * name;
    const char * type;
    */

    element->QueryAttribute("x", &x);
    element->QueryAttribute("y", &y);
    element->QueryAttribute("height", &height);
    element->QueryAttribute("width", &width);
    posi = b2Vec2(x/10.0f, y/10.0f);
    if(element->Attribute("name") != 0){
        element->QueryAttribute("name", &name);
    }
    if(element->Attribute("type") != 0){
        if(strlen(element->Attribute("type")) == 1){
            element->QueryAttribute("type", &typeInt);
        }
        else{
            this->typeString=element->Attribute("type");
        }
    }
}



#include "PathFinding/Lista.h"
#include "PathFinding/Nodo.h"
#include <iostream>

Lista::Lista(){
    head = NULL;
    tamanyo = 0;
}
Lista::~Lista(){}
void Lista::setHead(Nodo *nodo){
    head = nodo;
    head->setNext(NULL);
}
Nodo *Lista::getHead(){
    return head;
}
Nodo *Lista::getUltimo(){
    Nodo *aux;
    aux = head;
    if(aux){
        while(aux->getNextNodo() != NULL){
            aux = aux->getNextNodo();
        }
    }
    return aux;
}
int Lista::getTamanyo(){
    return tamanyo;
}
void Lista::imprimirListaAdyacentes(){
    Nodo* temp = getHead();
    while (temp!=NULL){
        std::cout<<"  Nodo: "<<temp->getNumero()<<" : ";
        std::cout<<std::endl;
        cercanos = temp->getAdyacentes();
        for(int i=0; i<cercanos.size(); i++){
            std::cout<<" "<<cercanos[i]<<std::endl;
        }
        std::cout<<std::endl;
        temp = temp->getNextNodo();
    }
    std::cout<<std::endl;
}
void Lista::imprimirLista(){
    Nodo* temp = getHead();
    while (temp!=NULL){
        std::cout<<"  Nodo: "<<temp->getNumero()<<" : ";
        temp = temp->getNextNodo();
    }
    std::cout<<std::endl;
}
Nodo *Lista::buscaNumero(int i){
    Nodo* temp = getHead();
    while(temp!=NULL){
        if(i == temp->getNumero())
            return temp;
        temp = temp->getNextNodo();
    }
    return NULL;
}

Nodo *Lista::getCercanoTotal(float x, float y){
    //std::cout<<"Pos entra: "<<x<<" "<<y<<std::endl;
    float pos = x + 0.3;
    int posX = (int) pos;
    float pos2 = -1* (y - 0.9);
    int posY = (int) pos2;        

    //std::cout<<"Pos busco: "<<posX<<" "<<posY<<std::endl;
    Nodo *aux = head;
    Nodo *aux2 = NULL;
    int dif = 2000;
    while(aux!=NULL){
        int coste = abs(aux->getPosicion().y - posY) + abs(aux->getPosicion().x - posX);
        //std::cout<<"COSTE: "<<coste<<" NODO: "<<aux->getNumero()<<std::endl;
        if(coste<dif){
            dif = coste;
            aux2 = aux;
        }
        aux = aux->getNextNodo();
    }
    return aux2;

    /*float pos = x + 0.3;
    int posX = (int) pos;
    float pos2 = -1* (y - 0.9);
    int posY = (int) pos2;
    Nodo *aux = this->head;
    Nodo *aux2 = NULL;
    int dif = 200;

    while(aux!=NULL){
        int coste = abs(aux->getPosicion().y - posY) + abs(aux->getPosicion().x - posX);

        if(coste<dif){
            aux2 = aux;
            dif = abs(aux->getPosicion().y - posY) + abs(aux->getPosicion().x - posX);
        }
        aux = aux->getNextNodo();
    }
    return aux2;*/
}

Nodo *Lista::getMas(float x, float y){
    float pos = x + 0.3;
    int posX = (int) pos;
    float pos2 = -1* (y - 0.9);
    int posY = (int) pos2;        

    Nodo *aux = head;
    Nodo *aux2 = NULL;
    int dif = 200;
    while(aux!=NULL){
        if(aux->getPosicion().y == posY){
            if(abs(aux->getPosicion().x - posX)< dif){
                aux2 = aux;
                dif = abs(aux->getPosicion().x - posX);
            }
        }
        aux = aux->getNextNodo();
    }
    return aux2;
}
Nodo *Lista::getMenorCosto(){
    Nodo *aux;
    Nodo *retur;
    if(getHead()!=NULL){
        aux = getHead();
        retur = getHead();
        int costo = getHead()->getCostoTotal();
        if(aux){
            while(aux->getNextNodo() != NULL){
                if(costo > aux->getCostoTotal() ){
                    costo = aux->getCostoTotal();
                    retur = aux;
                }
            aux = aux->getNextNodo();
            }
        }
        return retur;
    }
    return NULL;
}
void *Lista::remove (b2Vec2 posicion){
    Nodo* temp = getHead();
    Nodo* temp1 = getHead()->getNextNodo();
    if(temp->getPosicion() == posicion){
        head = temp1;
        tamanyo--;
    }else{
        while(temp1!=NULL){
            if(temp1->getPosicion() == posicion){
                Nodo* aux = temp1;
                temp->setNext(temp1->getNextNodo());
                tamanyo--;
            }
            temp = temp->getNextNodo();
            temp1 = temp1->getNextNodo();
        }
    }
}
void *Lista::insertar(Nodo *nodo){
    Nodo  *aux;
    aux = getHead();
    if(!aux){
        setHead(nodo);
        nodo->setNext(NULL);
        tamanyo++;
    }
    else{
        while(aux->getNextNodo() != NULL){
            aux = aux->getNextNodo();
        }
        aux->setNext(nodo);
        nodo->setNext(NULL);
        tamanyo ++;
    }
    return 0;
}
Nodo *Lista::buscaNodo2(float x, float y){
    Nodo *aux;
    aux = head;
    while(aux!=NULL){
        if(aux->getPosicion().x == x && aux->getPosicion().y == y){
            return aux;
        }
        aux = aux->getNextNodo();
    }
    return NULL;
}


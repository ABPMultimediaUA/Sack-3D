#ifndef NODO_H
#define NODO_H

#include <Box2D/Box2D.h>
#include <irrlicht.h>
#include <iostream>
#include <vector>

class Nodo{
    private:
        Nodo* nodoPadre;
        int coste;
        Nodo* nextNodo;
        int numero;
        std::vector<int> Adyacentes;
        b2Vec2 posicion; //DATO: posicion del nodo

    public:

        Nodo(b2Vec2 posicion, int num, int coste, Nodo *nodoPadre){
            this->posicion = posicion;
            this->numero = num;
            this->nextNodo = NULL;
            this->nodoPadre = nodoPadre;
            if(nodoPadre != NULL)
                coste = coste + this->nodoPadre->getCostoTotal();
            this->coste = coste;
        }

        void setPadre(Nodo *nodo, int g){
            this->nodoPadre = nodo;
            coste = g;
            if(nodoPadre != NULL)
                coste = coste + this->nodoPadre->getCostoTotal();
            this->coste = coste;
        }

        void setNext(Nodo *nodo){
            this->nextNodo = nodo;
        }
        b2Vec2 getPosicion(){
            return this->posicion;
        }
        Nodo *getPadre(){
            return this->nodoPadre;
        }
        int getCostoTotal(){
            return this->coste;
        }
        int getNumero(){
            return this->numero;
        }
        Nodo *getNextNodo(){
            return this->nextNodo;
        }
        void addAdyacente (int n){
            Adyacentes.push_back(n);
        }
        std::vector<int> getAdyacentes(){
            return this->Adyacentes;
        }

        virtual ~Nodo(){}

};

#endif // NODO_H


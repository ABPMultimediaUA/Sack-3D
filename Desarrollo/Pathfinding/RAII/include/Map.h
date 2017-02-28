
#ifndef MAP_H
#define MAP_H

#include <irrlicht.h>
#include "Lista.h"
#include "Nodo.h"

class Map{
    public:
        Map(irr::core::stringw file);
        Lista* getListaNodos(){ return nodos; }
        Lista* getListaPath(){ return pathfinding; }
        void comprobar(int i);
        void calcularPathfinding(float x, float y, Nodo* objetivo);
        virtual ~Map(){}
    private:
        Lista *nodos;
        Lista *pathfinding;
        Lista *listaAbierta;
        Lista *listaCerrada;

        Nodo* nodoActual;
        Nodo* nodoInicial;
        Nodo* nodoDestino;

        b2Vec2 posicion;
        b2Vec2 posicionI;
        b2Vec2 posicionF;

};

#endif

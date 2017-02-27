
#ifndef MAP_H
#define MAP_H

#include <irrlicht.h>
#include "Lista.h"
#include "Nodo.h"

class Map{
    public:
        Map(irr::core::stringw file);
        void obtenerPathfinding();
        int distanciaManhattan(b2Vec2 posicion1, b2Vec2 posicion2);
        Lista* getListaNodos(){ return nodos; }
        Lista* getListaPath(){ return pathfinding; }
        void comprobar(int i, int j, int peso, Nodo *nodoActual, Nodo *nodoFin);
        void nodoCercano(float x, float y, Nodo* objetivo);
        virtual ~Map(){}
    private:
        Lista *nodos;
        Lista *camino;
        Lista *pathfinding;
        Lista *pathfindingfinal;
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

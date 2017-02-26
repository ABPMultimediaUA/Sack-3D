
#ifndef MAP_H
#define MAP_H

#include <irrlicht.h>
#include "Lista.h"
#include "Nodo.h"

class Map{
    public:
        Map(irr::core::stringw file);
        void obtenerPathfinding();
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
        int matriz[36][64];
        int mAdyacencia[18][18]={
            //     0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17
            /* 0*/{1, 9, 0, 7, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            /* 1*/{9, 1, 0, 0, 0, 0, 0,13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            /* 2*/{0, 0, 1,18, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,20, 0, 0, 0},
            /* 3*/{7, 0,18, 1, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            /* 4*/{0, 0, 0, 6, 1, 9, 0, 0, 0, 0,10, 0, 0, 0, 0, 0, 0, 0},
            /* 5*/{0, 0, 0, 0, 9, 1, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            /* 6*/{0, 0, 0, 0, 0, 0, 1, 2, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0},
            /* 7*/{0, 0, 0, 0, 0, 6, 2, 1,18, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            /* 8*/{0, 0, 0, 0, 0, 0, 0,18, 1, 0, 0, 0, 0, 9, 0, 0, 0, 0},
            /* 9*/{0, 0, 0, 0, 0, 0, 0, 0, 0, 1,13, 0, 0, 0, 0, 8, 0, 0},
            /*10*/{0, 0, 0, 0, 0, 0, 0, 0, 0,13, 1, 8, 0, 0, 0, 0, 0, 0},
            /*11*/{0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 8, 1, 0, 0, 0, 0,10, 0},
            /*12*/{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 1,21, 0, 0, 6, 0},
            /*13*/{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,21, 1, 0, 0, 0, 6},
            /*14*/{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 5, 0, 0},
            /*15*/{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 1,27, 0},
            /*16*/{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0,27, 1,25},
            /*17*/{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0,25, 1},
        };

};

#endif

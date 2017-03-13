#ifndef BOT_H
#define BOT_H

#include "World.h"

class Lista;
class Nodo;
class Bot: public Player{
    public:
        Bot(b2Vec2 pos, int mando,irr::video::SColor color, char idr[]);
        virtual ~Bot(){}
        void actualiza();
        void muevo(int x, int y);
        void mover();
        virtual void saltar();
        void InicializaVariables();
        void calcularPathfinding(Nodo* objetivo);
    private:
		bool enMuelle;
        bool prueba;
        int direccion;
        int direccionA;
        float nodox;
        float nodoy;
        Nodo* head;
        Lista *lista;
        Lista* pathfinding;
};

#endif // BOT_H

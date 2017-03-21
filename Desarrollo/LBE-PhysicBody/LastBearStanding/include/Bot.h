#ifndef BOT_H
#define BOT_H

#include "World.h"

class Lista;
class Nodo;
class Bot: public Player{
    public:
        Bot(b2Vec2 pos, int mando,irr::video::SColor color);
        virtual ~Bot();
        virtual void actualiza();
        virtual void muevo(int x, int y);
        virtual void mover();
        virtual void InicializaVariables();
        virtual void calcularPathfinding(Nodo* objetivo);
    private:
		bool enMuelle;
        bool prueba;
        float nodox;
        float nodoy;
        Nodo* head;
        Lista *lista;
        Lista* pathfinding;
};

#endif // BOT_H

#ifndef BOT_H
#define BOT_H

#include "Player.h"
#include "GameResource.h"

class Lista;
class Nodo;
class Bot: public Player{
    public:
        Bot(b2Vec2 pos, int mando);
        virtual ~Bot(){}
        void actualiza();
        void muevo(int x, int y);
        void mover();
        void InicializaVariables();
        void calcularPathfinding(Nodo* objetivo);
    private:
		bool enMuelle;
        float nodox;
        float nodoy;
        Lista *lista;
        //GameResource<Lista> pathfinding;
        Lista* pathfinding;
};

#endif // BOT_H

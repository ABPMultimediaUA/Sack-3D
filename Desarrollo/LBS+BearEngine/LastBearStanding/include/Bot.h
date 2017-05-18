#ifndef BOT_H
#define BOT_H


#include "PathFinding/Nodo.h"
#include "Player.h"
#include "Spawner.h"
#include "World.h"

class Lista;
class Nodo;
class Bot: public Player{
    public:
        Bot(b2Vec2 pos, int mando, char *texture, char idr[]);
        virtual ~Bot(){}
        b2Vec2 getSpawnCercano(float x, float y);
        void buscaArma();
        void colisionConNodo(int nodo);
        void buscoSpawn();
        void buscaJugador();
        void cambiarDireccion(int direccion);
        Nodo* getMas(float x, float y);
        Nodo* getCercanoTotal(float x, float y);
        Nodo* buscaNumero(int i);
        void despega();
        virtual void teletransportar();
        virtual void actualiza(MyEventReceiver *events);
        virtual void muevo(float x, float y);
        virtual void mover(MyEventReceiver *events = NULL);
        //virtual void CogerTirar();
        virtual void morir();
        void imprimirNodos();
        virtual void saltar();
        virtual void InicializaVariables();
        virtual void calcularPathfinding(Nodo* inicial, Nodo* objetivo);
    private:
        int LEVEL;
        float limitX;
        float limitY;
        bool saltito;

        int estadoBot;
        int mandobusco;
        int spawnbusco;
        b2Vec2 posicionSpawn;
        bool enMuelle;
        bool primera;
        int direccion;
        int direccionA;
        int lastDir;
        Nodo* nodoFinIni;
        float nodox;
        float nodoy;
        Lista *lista;
        Lista *spawn;
        Lista* pathfinding;
        std::vector<Player*> players;
        std::vector<Nodo*> nodos;
        std::vector<Spawner*> spawners;
};

#endif // BOT_H

#ifndef PLAYERRED_H
#define PLAYERRED_H
//---------------------------------------------------------------------------
#include <Box2D/Box2D.h>
#include <irrlicht.h>
#include "Cogible.h"


using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;


class PlayerRed
{
    public:
        PlayerRed(char idr[], float xr, float yr);
        void InicializeFixtures(int mode);
        void actualiza();
        b2Body* getBody();
        b2Vec2 getPosition(){return body->GetPosition();}
        virtual ~PlayerRed();
        char* getId();
        void Soltar();
        void mover();
        void DestroyFixtures();
        void setx(long int aux);
        void sety(long int aux);
        void setEstado(int aux);
        void setDireccion(int aux);
        void setMoviendo(int aux);
        void setId(char aux[]);
        void teletransportar();
        void fingirMuerte();
        void CogerTirar(int i);
        void saltar(int i);
        int getMuerto(){return muerto;}
        void setMuerto(int i){muerto = i;}
        void usar();
        //void dispararPistola(long int x, long int y, int direc);
        IMeshSceneNode* node;
	    b2Body* body;

    protected:

        int muerto;
        char id[30];
        float vel = 7;
        float salto = 15.0f;
        float x;
        float y;
        int estado;
        int estadoAntiguo;
        int direccion;
        int moviendo;
        bool cogiendo;
        bool primera = true;
        Cogible* objCogido;
        b2RevoluteJoint* joint;
        vector3df tam;
        b2Fixture* personFixture;                ///<

    private:
};

#endif // PLAYERRED_H

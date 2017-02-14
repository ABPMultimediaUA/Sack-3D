#ifndef COGIBLE_H
#define COGIBLE_H

#include <Box2D/Box2D.h>
#include <irrlicht.h>

#define RADTOGRAD        180 / 3.14159265
#define CATCH            1
#define RELEASE          2
#define ARMA             30
#define SENSOR           35
#define PLAYER           10
#define PIESPLAYER       100

class Cogible{
    public:
        Cogible(b2Vec2 pos);
        virtual ~Cogible();
        virtual void DestroyFixtures();
        virtual void InicializeFixtures(int mode);
        virtual void actualiza();
        virtual void setDireccion(int);
        virtual int  getDireccion();
        virtual b2Body* getBody();
        virtual bool getCogido();
       // virtual void setIdCogible();
        virtual int getIdCogible();
        virtual bool getAutoDestruir();
        virtual void setCogido(bool aux);
    protected:
        irr::scene::IMeshSceneNode* node;
        b2Body* body;
        irr::core::vector3df tam;
        bool autoDestruir = false;
        bool cogido = false;
        int dir = 1;
        float restitution = 0.2f;
        float density = 2.0f;
        float friction = 0.8f;
};

#endif

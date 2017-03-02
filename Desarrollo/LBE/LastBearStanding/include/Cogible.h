#ifndef COGIBLE_H
#define COGIBLE_H

#include <Box2D/Box2D.h>
#include <irrlicht.h>

#define RADTOGRAD        180 / 3.14159265
#define CATCH            1
#define RELEASE          2

class Spawner;
class Cogible{
    public:
        Cogible(Spawner* expo,b2Vec2 pos);
        virtual ~Cogible();
        virtual void DestroyFixtures();
        virtual void InicializeFixtures(int mode);
        virtual void actualiza();
        virtual void teletransportar();
        virtual void setDireccion(int d){if(d != 0) dir = d;}
        virtual int  getDireccion(){return dir;}
        virtual b2Body* getBody(){return body;}
        virtual irr::scene::IMeshSceneNode* getNode(){return node;}

        virtual bool getCogido(){return cogido;}
        virtual bool getAutoDestruir(){return autoDestruir;}
        virtual void setCogido(bool aux);
        virtual void setExpositor(Spawner* aux);
        virtual Spawner* getExpositor();
        virtual int getIdCogible();
        virtual void setNextPos(b2Vec2 pos){teletransportado=true; nextPos = pos;}
        virtual void setExpuesto(bool aux){expuesto = aux;}
        virtual bool getExpuesto(){return expuesto;}
    protected:
        irr::scene::IMeshSceneNode* node;
        Spawner* expositor;
        b2Body* body;
        irr::core::vector3df tam;
        bool autoDestruir ;
        bool cogido ;
        bool teletransportado ;
        b2Vec2 nextPos;
        int dir ;
        bool expuesto;
        float restitution;
        float density ;
        float friction ;
        b2Vec2 velActual;
};

#endif

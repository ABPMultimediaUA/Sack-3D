#ifndef COGIBLE_H
#define COGIBLE_H

#include "GameObject.h"

#define RADTOGRAD        180 / 3.14159265
#define CATCH            1
#define RELEASE          2

class Spawner;
class Cogible: public GameObject{
    public:
        Cogible(Spawner* expo,b2Vec2 pos, irr::core::vector3df tam, irr::video::SColor color);
        virtual ~Cogible();
        virtual void DestroyFixtures();
        virtual void InicializeFixtures(int mode);
        virtual void actualiza();
        virtual void teletransportar();
        virtual void setDireccion(int d);
        virtual int  getDireccion();
        virtual bool getCogido();
        virtual bool getAutoDestruir();
        virtual void setCogido(bool aux);
        virtual void setExpositor(Spawner* aux);
        virtual Spawner* getExpositor();
        virtual int getIdCogible();
        virtual void setNextPos(b2Vec2 pos);
        virtual void setExpuesto(bool aux);
        virtual bool getExpuesto();
        static int contID;
    protected:
        Spawner* expositor;
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
        int idCogible;
};

#endif

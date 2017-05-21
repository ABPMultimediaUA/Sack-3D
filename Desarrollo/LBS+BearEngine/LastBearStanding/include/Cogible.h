#ifndef COGIBLE_H
#define COGIBLE_H

#include "PhysicBody/PhysicBody.h"
#include "GameResource.h"
#include <Box2D/Box2D.h>
#include "GameObject.h"

class Spawner;
class World;
class BearMngr;


class Cogible{
    public:
        Cogible(PhysicBody* physicBody ,Spawner* expo,b2Vec2 pos, glm::vec3 tam,  char *model = "BearEngine/res/cubo.obj", char *texture = NULL, int idc=0);
        virtual ~Cogible();
        virtual void actualiza();
        virtual void teletransportar();
        virtual void setDireccion(int d);
        virtual int  getDireccion();
        virtual b2Vec2 GetLinearVelocity();
        virtual float  GetRotation();
        virtual b2Vec2  GetPosition();
        virtual bool getCogido();
        virtual bool getAutoDestruir();
        virtual void setCogido(bool aux);
        virtual void setExpositor(Spawner* aux);
        virtual void SetAngularVelocity(float imp);
        virtual void SetLinearVelocity(b2Vec2 vel);
        virtual Spawner* getExpositor();
        virtual int GetId();
        virtual int GetIdc();
        virtual void setNextPos(b2Vec2 pos);
        virtual void setExpuesto(bool aux);
        virtual bool getExpuesto();
    protected:
        GameObject m_gameObject;
        World *m_pWorld;
        BearMngr *m_pBearMngr;
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
        int m_id;
        int id;
};

#endif

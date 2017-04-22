#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "IrrManager.h"
#include <Box2D/Box2D.h>
#include "GameResource.h"

class World;
class PhysicBody;


const float RadToGrad = 180.f / 3.14159265f;

class GameObject{
    public:
        GameObject();
        virtual int Inicialize(PhysicBody *physicBody,uint16 category, uint16 mask, int userdata, b2Vec2 pos, irr::core::vector3df tam, irr::video::SColor color,char *texture = NULL);
        virtual int Inicialize(PhysicBody *physicBody,b2Vec2 pos, irr::core::vector3df tam, irr::video::SColor color,char *texture = NULL);
        virtual ~GameObject();
        virtual void Update();
        virtual irr::scene::IMeshSceneNode* getNode();
        virtual int   SetMode(PhysicBody* body);
        virtual void   SetVisible(bool visible);
        virtual void   SetGravity(float gravity);
        virtual b2Vec2 GetPosition();
        virtual float    GetRotation();
        virtual b2Vec2 GetLinearVelocity();
        virtual int    GetId();
        virtual void   SetFixedRotation(bool fixed);
        virtual void   SetRotation(float angle);
        virtual void   SetAngularVelocity(float imp);
        virtual void   SetLinearVelocity(b2Vec2 vel);
        virtual void   SetPosition(b2Vec2 pos);
        virtual void   SetMargin(b2Vec2 margin);
        virtual void   Catch(int id);
        virtual void   Release();
        virtual PhysicBody* GetBody();
    private:
        GameResource<PhysicBody> m_GRphysicBody;
        PhysicBody *m_pPhysicBody;
        irr::scene::IMeshSceneNode* m_pNode;
        irr::core::vector3df m_tam;
        IrrMngr *m_pIrrMngr;
        World *m_pWorld;
        b2Vec2 m_margin;
        b2Vec2 m_pos;
        int m_id;
};

#endif // GAMEOBJECT_H

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "BearManager.h"
#include <Box2D/Box2D.h>
#include "GameResource.h"

class World;
class PhysicBody;
class TNodo;


const float RadToGrad = 180.f / 3.14159265f;

class GameObject{
    public:
        GameObject();
        virtual int Inicialize(PhysicBody *physicBody, uint16 category, uint16 mask, int userdata, b2Vec2 pos, glm::vec3 tam,  char *model = NULL, char *texture = NULL, bool shader = 1);
        virtual int Inicialize(PhysicBody *physicBody, b2Vec2 pos, glm::vec3 tam, char *model = NULL, char *texture = NULL, bool shader = 1);
        virtual ~GameObject();
        virtual void Update();
        virtual void AddModel(char* model);
        virtual void NextFrame();
        virtual void ResetAnimacion();
        virtual int   SetMode(PhysicBody* body);
        virtual void   SetVisible(bool visible);
        virtual void   SetGravity(float gravity);
        virtual b2Vec2 GetPosition();
        virtual float    GetRotation();
        virtual b2Vec2 GetLinearVelocity();
        virtual int    GetId();
        virtual float  GetZ();
        virtual void   SetFixedRotation(bool fixed);
        virtual void   SetRotation(float angle);
        virtual void   SetAngularVelocity(float imp);
        virtual void   SetLinearVelocity(b2Vec2 vel);
        virtual void   SetPosition(b2Vec2 pos);
        virtual void   SetZ(float  z);
        virtual void   SetMargin(b2Vec2 margin);
        virtual void   SetXRotation(int rot);
        virtual void   Catch(int id);
        virtual void   Release();
        virtual PhysicBody* GetBody();
    private:
        GameResource<PhysicBody> m_GRphysicBody;
        PhysicBody *m_pPhysicBody;
        glm::vec3 m_tam;
        TNodo* m_bearNodo;
        BearMngr *m_pBearMngr;
        World *m_pWorld;
        b2Vec2 m_margin;
        b2Vec2 m_pos;
        int m_id;
        float m_z;
};

#endif // GAMEOBJECT_H

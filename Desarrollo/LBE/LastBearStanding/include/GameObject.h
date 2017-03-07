#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "IrrManager.h"
#include <Box2D/Box2D.h>

class World;
class GameObject{
    public:
        GameObject(b2Vec2 pos, irr::core::vector3df tam, irr::video::SColor color);
        virtual ~GameObject();
        virtual b2Body* getBody();
        virtual irr::scene::IMeshSceneNode* getNode();
    protected:
        irr::scene::IMeshSceneNode* m_pNode;
        irr::core::vector3df m_tam;
        IrrMngr *m_pIrrMngr;
        World *m_pWorld;
        b2Body* m_pBody;
        b2Vec2 m_pos;
};

#endif // GAMEOBJECT_H

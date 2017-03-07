#include "GameObject.h"
#include "World.h"

GameObject::GameObject(b2Vec2 pos, irr::core::vector3df tam, irr::video::SColor color)
:m_tam(tam),m_pos(pos){
    m_pWorld   = World::Inst();
    m_pIrrMngr = IrrMngr::Inst();
    m_pNode    = m_pIrrMngr->addCubeSceneNode(tam,color);
    m_pNode->setPosition(irr::core::vector3df(pos.x+(m_tam.X/2), -1*(pos.y-(m_tam.Y/2)),0));
    m_pNode->setMaterialTexture(0,m_pIrrMngr->getDriver()->getTexture("media/texture.jpg"));
    m_pNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
}
GameObject::~GameObject(){
    if(m_pNode)m_pNode->remove();
}
b2Body* GameObject::getBody(){
	return m_pBody;
}
irr::scene::IMeshSceneNode* GameObject::getNode(){
	return m_pNode;
}

#include "GameObject.h"
#include "World.h"
#include <iostream>

GameObject::GameObject():m_margin(b2Vec2(0,0)){
    m_pWorld   = World::Inst();
    m_pIrrMngr = IrrMngr::Inst();
    m_GRphysicBody.Reset(NULL);
    m_pPhysicBody = NULL;
    m_pNode = NULL;
    m_id = -1;
}
GameObject::~GameObject(){
    if(m_pNode)m_pNode->remove();
}
int GameObject::Inicialize(PhysicBody *physicBody, uint16 category, uint16 mask, int userdata, b2Vec2 pos, irr::core::vector3df tam, irr::video::SColor color){
    m_tam = tam;
    m_pos.x = pos.x*2.0f;
    m_pos.y = pos.y*2.0f;
    m_GRphysicBody.Reset(physicBody);
    m_pPhysicBody = m_GRphysicBody.Get();
    m_pPhysicBody->SetCategory(category);
    m_pPhysicBody->SetUserData(userdata);
    m_pPhysicBody->SetMask(mask);
    m_id = m_pPhysicBody->Inicialize(m_pos, b2Vec2(tam.X,tam.Y));
    m_pNode = m_pIrrMngr->addCubeSceneNode(tam*2.0f,color);
    m_pNode->setPosition(irr::core::vector3df(pos.x*2.0f+(m_tam.X), -1*(pos.y*2.0f)-(m_tam.Y),0));
    m_pNode->setMaterialTexture(0,m_pIrrMngr->getDriver()->getTexture("media/Images/texture.jpg"));
    m_pNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    return m_id;
}
int GameObject::Inicialize(PhysicBody *physicBody, b2Vec2 pos, irr::core::vector3df tam, irr::video::SColor color){
    m_tam = tam;
    m_pos.x = pos.x*2.0f;
    m_pos.y = pos.y*2.0f;
	m_GRphysicBody.Reset(physicBody);
    m_pPhysicBody = m_GRphysicBody.Get();
    m_pWorld   = World::Inst();
    m_pIrrMngr = IrrMngr::Inst();
	 m_id = m_pPhysicBody->Inicialize(m_pos, b2Vec2(tam.X,tam.Y));
    m_pNode = m_pIrrMngr->addCubeSceneNode(tam*2.0f,color);
    m_pNode->setPosition(irr::core::vector3df(pos.x*2.0f+(m_tam.X), -1*(pos.y*2.0f)-(m_tam.Y),0));
    m_pNode->setMaterialTexture(0,m_pIrrMngr->getDriver()->getTexture("media/Images/texture.jpg"));
    m_pNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    return m_id;
}
void GameObject::Update(){
    //std::cout<<"MARGINBALA "<<m_margin.x<<" "<<m_margin.y<<std::endl;
    m_pNode->setPosition(irr::core::vector3df(m_pPhysicBody->GetPosition().x+m_margin.x,m_pPhysicBody->GetPosition().y+m_margin.y,0));
    m_pNode->setRotation(irr::core::vector3df(0,0,m_pPhysicBody->GetRotation()*RadToGrad));
}
irr::scene::IMeshSceneNode* GameObject::getNode(){
	return m_pNode;
}
b2Vec2 GameObject::GetPosition(){
    return m_pPhysicBody->GetPosition();
}
PhysicBody* GameObject::GetBody(){
    return m_pPhysicBody;
}
float GameObject::GetRotation(){
    return m_pPhysicBody->GetRotation();
}
b2Vec2 GameObject::GetLinearVelocity(){
    return m_pPhysicBody->GetLinearVelocity();
}
int GameObject::GetId(){
    return m_id;
}
int GameObject::SetMode(PhysicBody* body){
    b2Vec2  pos = m_pPhysicBody->GetPosition();
    b2Vec2  vel = m_pPhysicBody->GetLinearVelocity();
    pos.y = pos.y*-1;
    b2Vec2  tam(m_tam.X,m_tam.Y);
    m_GRphysicBody.Reset(body);
    m_pPhysicBody = m_GRphysicBody.Get();
    m_id = m_pPhysicBody->Inicialize(pos,tam);
    m_pPhysicBody->SetLinearVelocity(vel);
    return m_id;
}
void GameObject::SetVisible(bool visible){
    m_pNode->setVisible(visible);
}
void GameObject::SetFixedRotation(bool fixed){
    m_pPhysicBody->SetFixedRotation(fixed);
}
void GameObject::SetRotation(float angle){
    m_pPhysicBody->SetRotation(angle);
}
void GameObject::SetAngularVelocity(float imp){
    m_pPhysicBody->SetAngularVelocity(imp);
}
void GameObject::SetLinearVelocity(b2Vec2 vel){
    m_pPhysicBody->SetLinearVelocity(vel);
}
void GameObject::SetPosition(b2Vec2 pos){
    m_pPhysicBody->SetPosition(pos);
}
void GameObject::SetMargin(b2Vec2 margin){
    m_margin = margin;
}
void GameObject::Catch(int id){
    m_pPhysicBody->Catch(id);
}
void GameObject::Release(){
    m_pPhysicBody->Release();
}

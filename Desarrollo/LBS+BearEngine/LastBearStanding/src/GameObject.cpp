#include "GameObject.h"
#include "World.h"
#include <iostream>

GameObject::GameObject():m_margin(b2Vec2(0,0)){
    m_pWorld   = World::Inst();
    m_pBearMngr = BearMngr::Inst();
    m_GRphysicBody.Reset(NULL);
    m_pPhysicBody = NULL;
    m_bearNodo = NULL;
    m_id = -1;
}
GameObject::~GameObject(){
    //if(m_bearNodo)m_pBearMngr->RemoveBearNode(m_bearNodo);
    m_pBearMngr->IsBearVisible(m_bearNodo,false);
}
int GameObject::Inicialize(PhysicBody *physicBody, uint16 category, uint16 mask, int userdata, b2Vec2 pos, glm::vec3 tam, irr::video::SColor color,char *texture){
    m_tam = tam;
    m_pos.x = pos.x*2.0f;
    m_pos.y = pos.y*2.0f;
    m_GRphysicBody.Reset(physicBody);
    m_pPhysicBody = m_GRphysicBody.Get();
    m_pPhysicBody->SetCategory(category);
    m_pPhysicBody->SetUserData(userdata);
    m_pPhysicBody->SetMask(mask);
    m_id = m_pPhysicBody->Inicialize(m_pos, b2Vec2(tam.x,tam.y));
    //BearEngine
    m_bearNodo = m_pBearMngr->CreateBearNode(m_id,glm::vec3(pos.x*2.0f+(m_tam.x), -1*(pos.y*2.0f)-(m_tam.y),0),tam);
    //BearEngine
    //if(!texture)
    //    m_pNode->setMaterialTexture(0,m_pBearMngr->getDriver()->getTexture("media/Images/texture.jpg"));
    //else
    //    m_pNode->setMaterialTexture(0,m_pBearMngr->getDriver()->getTexture(texture));
    return m_id;
}
int GameObject::Inicialize(PhysicBody *physicBody, b2Vec2 pos, glm::vec3 tam, irr::video::SColor color,char *texture){
    m_tam = tam;
    m_pos.x = pos.x*2.0f;
    m_pos.y = pos.y*2.0f;
	m_GRphysicBody.Reset(physicBody);
    m_pPhysicBody = m_GRphysicBody.Get();
    m_pWorld   = World::Inst();
    m_pBearMngr = BearMngr::Inst();
	 m_id = m_pPhysicBody->Inicialize(m_pos, b2Vec2(tam.x,tam.y));
    //BearEngine
    m_bearNodo = m_pBearMngr->CreateBearNode(m_id,glm::vec3(m_pos.x,m_pos.y,0),tam);
    //BearEngine
    //m_pNode->setPosition(glm::vec3(pos.x*2.0f+(m_tam.X), -1*(pos.y*2.0f)-(m_tam.Y),0));
    //if(!texture)
    //    m_pNode->setMaterialTexture(0,m_pBearMngr->getDriver()->getTexture("media/Images/texture.jpg"));
    //else
    //    m_pNode->setMaterialTexture(0,m_pBearMngr->getDriver()->getTexture(texture));
    return m_id;
}
void GameObject::Update(){
    m_pBearMngr->SetBearCubePosition(m_bearNodo,glm::vec3(m_pPhysicBody->GetPosition().x+m_margin.x,m_pPhysicBody->GetPosition().y+m_margin.y,0));
    m_pBearMngr->SetBearCubeRotation(m_bearNodo,m_pPhysicBody->GetRotation());
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
void GameObject::SetGravity(float gravity){
    m_pPhysicBody->SetGravity(gravity);
}
int GameObject::SetMode(PhysicBody* body){
    b2Vec2  pos = m_pPhysicBody->GetPosition();
    b2Vec2  vel = m_pPhysicBody->GetLinearVelocity();
    pos.y = pos.y*-1;
    b2Vec2  tam(m_tam.x,m_tam.y);
    m_GRphysicBody.Reset(body);
    m_pPhysicBody = m_GRphysicBody.Get();
    m_id = m_pPhysicBody->Inicialize(pos,tam);
    m_pPhysicBody->SetLinearVelocity(vel);
    return m_id;
}
void GameObject::SetVisible(bool visible){
    m_pBearMngr->IsBearVisible(m_bearNodo,visible);
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

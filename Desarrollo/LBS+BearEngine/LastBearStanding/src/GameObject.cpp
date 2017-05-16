#include "GameObject.h"
#include "World.h"
#include <iostream>

GameObject::GameObject():m_margin(b2Vec2(0,0)),m_z(0){
    m_pBearMngr = BearMngr::Inst();
    m_GRphysicBody.Reset(NULL);
    m_pPhysicBody = NULL;
    m_bearNodo = NULL;
    m_id = -1;
}
GameObject::~GameObject(){
    if(m_bearNodo)m_pBearMngr->RemoveBearNode(m_bearNodo);
}
int GameObject::Inicialize(PhysicBody *physicBody, uint16 category, uint16 mask, int userdata, b2Vec2 pos, glm::vec3 tam, char *model,char *texture, bool shader){
    m_pWorld   = World::Inst();
    m_tam = tam;
    m_pos.x = pos.x*2.0f;
    m_pos.y = pos.y*2.0f;
    m_GRphysicBody.Reset(physicBody);
    m_pPhysicBody = m_GRphysicBody.Get();
    m_pPhysicBody->SetCategory(category);
    m_pPhysicBody->SetUserData(userdata);
    m_pPhysicBody->SetMask(mask);
    m_id = m_pPhysicBody->Inicialize(m_pos, b2Vec2(tam.x,tam.y));
    if(!model)
        if(!texture)
            m_bearNodo = m_pBearMngr->CreateBearCube(m_id,glm::vec3(pos.x*2.0f+(m_tam.x), -1*(pos.y*2.0f)-(m_tam.y),0),tam,"media/Images/textures.jpg");
        else
            m_bearNodo = m_pBearMngr->CreateBearCube(m_id,glm::vec3(pos.x*2.0f+(m_tam.x), -1*(pos.y*2.0f)-(m_tam.y),0),tam,texture, shader);
    else
        m_bearNodo = m_pBearMngr->CreateBearModel(m_id,glm::vec3(pos.x*2.0f+(m_tam.x), -1*(pos.y*2.0f)-(m_tam.y),0),model,texture);
    return m_id;
}
int GameObject::Inicialize(PhysicBody *physicBody, b2Vec2 pos, glm::vec3 tam, char *model,char *texture, bool shader){
    m_pWorld   = World::Inst();
    m_tam = tam;
    m_pos.x = pos.x*2.0f;
    m_pos.y = pos.y*2.0f;
	m_GRphysicBody.Reset(physicBody);
    m_pPhysicBody = m_GRphysicBody.Get();
    m_pWorld   = World::Inst();
    m_pBearMngr = BearMngr::Inst();
    m_id = m_pPhysicBody->Inicialize(m_pos, b2Vec2(tam.x,tam.y));
     if(!model)
        if(!texture)
            m_bearNodo = m_pBearMngr->CreateBearCube(m_id,glm::vec3(pos.x*2.0f+(m_tam.x), -1*(pos.y*2.0f)-(m_tam.y),0),tam,"media/Images/textures.jpg");
        else
            m_bearNodo = m_pBearMngr->CreateBearCube(m_id,glm::vec3(pos.x*2.0f+(m_tam.x), -1*(pos.y*2.0f)-(m_tam.y),0),tam,texture, shader);
    else
        m_bearNodo = m_pBearMngr->CreateBearModel(m_id,glm::vec3(pos.x*2.0f+(m_tam.x), -1*(pos.y*2.0f)-(m_tam.y),0),model,texture);

    return m_id;
}
void GameObject::Update(){
    m_pBearMngr->SetBearCubePosition(m_bearNodo,glm::vec3(m_pPhysicBody->GetPosition().x+m_margin.x,m_pPhysicBody->GetPosition().y+m_margin.y,m_z));
    m_pBearMngr->SetBearCubeRotation(m_bearNodo,m_pPhysicBody->GetRotation());
}
void GameObject::AddModel(char* model){
     m_pBearMngr->AddModel(m_bearNodo,model);
}
void GameObject::NextFrame(){
    m_pBearMngr->NextFrame(m_bearNodo);
}
void GameObject::ResetAnimacion(){
    m_pBearMngr->ResetAnimacion(m_bearNodo);
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
float GameObject::GetZ(){
    return m_z;
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
void GameObject::SetXRotation(int rot){
    m_pBearMngr->SetXRotation(m_bearNodo,rot*3.14/180);
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
void GameObject::SetZ(float z){
    m_z = z;
}
void GameObject::Catch(int id){
    m_pPhysicBody->Catch(id);
}
void GameObject::Release(){
    m_pPhysicBody->Release();
}

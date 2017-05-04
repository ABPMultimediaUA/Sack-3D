#include "PhysicBody/PBDefaultSensor.h"
#include "PathFinding/Nodo.h"
#include <iostream>
#include "World.h"


Nodo::Nodo(b2Vec2 posicion, glm::vec3 tam,int num, int coste, Nodo *nodoPadre){
    m_posicion = posicion;
    m_numero = num;
    m_pNextNodo = NULL;
    m_pNodoPadre = nodoPadre;
    m_id = m_gameObject.Inicialize(
        new PBDefaultSensor()
        ,M_NODO
        ,M_PLAYER
        ,DATA_NODO
        ,posicion
        ,tam
        ,"BearEngine/res/spawner.obj"
        ,"media/Images/otro.png"
    );
    m_gameObject.SetVisible(false);
    if(m_pNodoPadre != NULL)
        m_coste = coste + m_pNodoPadre->getCostoTotal();
    m_coste = coste;
}
Nodo::~Nodo(){}
void Nodo::setPadre(Nodo *nodo, int g){
    m_pNodoPadre = nodo;
    m_coste = g;
    if(m_pNodoPadre != NULL)
        m_coste = m_coste + m_pNodoPadre->getCostoTotal();
    m_coste = m_coste;
}
void Nodo::setNext(Nodo *nodo){
    m_pNextNodo = nodo;
}
b2Vec2 Nodo::getPosicion(){
    return m_posicion;
}
Nodo *Nodo::getPadre(){
    return m_pNodoPadre;
}
int Nodo::getCostoTotal(){
    return m_coste;
}
int Nodo::getNumero(){
    return m_numero;
}
Nodo *Nodo::getNextNodo(){
    return m_pNextNodo;
}
void Nodo::addAdyacente (int n){
    m_Adyacentes.push_back(n);
}
std::vector<int> Nodo::getAdyacentes(){
    return m_Adyacentes;
}
int Nodo::GetId(){
    return m_id;
}
void Nodo::SetVisible(bool aux){
    m_gameObject.SetVisible(aux);
}

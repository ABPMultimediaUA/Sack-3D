#ifndef NODO_H
#define NODO_H

#include "GameObject.h"
#include <vector>

class Nodo{
    public:
        Nodo(b2Vec2 posicion, glm::vec3 tam,int num, int coste, Nodo *nodoPadre);
        ~Nodo();
        void setPadre(Nodo *nodo, int g);
        void setNext(Nodo *nodo);
        b2Vec2 getPosicion();
        Nodo *getPadre();
        int getCostoTotal();
        int getNumero();
        Nodo *getNextNodo();
        void addAdyacente (int n);
        std::vector<int> getAdyacentes();
        int GetId();
        void SetVisible(bool aux);
    private:
        Nodo* m_pNodoPadre;
        int m_coste;
        Nodo* m_pNextNodo;
        int m_numero;
        std::vector<int> m_Adyacentes;
        b2Vec2 m_posicion;
        GameObject m_gameObject;
        int m_id;
};

#endif // NODO_H


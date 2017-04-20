#ifndef LISTA_H
#define LISTA_H

#include <Box2D/Box2D.h>
#include <Vector>

class Nodo;
class Lista{
    public:
        Lista();
        ~Lista();
        void setHead(Nodo *nodo);
        Nodo *getHead();
        Nodo *getUltimo();
        int getTamanyo();
        void imprimirListaAdyacentes();
        void imprimirLista();
        Nodo *buscaNumero(int i);
        Nodo *getMas(float x, float y);
        Nodo *getCercanoTotal(float x, float y);
        Nodo *getMenorCosto();
        void *remove (b2Vec2 posicion);
        void *insertar(Nodo *nodo);
        Nodo *buscaNodo2(float x, float y);
    private:
        int tamanyo;
        std::vector<int> cercanos;
        Nodo *head;
};

#endif // LISTA_H

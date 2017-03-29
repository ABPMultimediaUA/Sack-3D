#ifndef LISTA_H
#define LISTA_H

#include <Nodo.h>
#include <Box2D/Box2D.h>
#include <irrlicht.h>
#include <iostream>

class Lista
{
    private:
        Nodo *head;
        int tamanyo;
        std::vector<int> cercanos;

    public:
        Lista(){
            this->head = nullptr;
            tamanyo = 0;
        }

        void setHead(Nodo *nodo){
            this->head = nodo;
            head->setNext(nullptr);
        }

        Nodo *getHead(){
            return this->head;
        }

        Nodo *getUltimo(){
            Nodo *aux;
            aux = this->head;
            if(aux){
                while(aux->getNextNodo() != nullptr){
                    aux = aux->getNextNodo();
                }
            }
            return aux;
        }

        int getTamanyo(){
            return tamanyo;
        }

        void imprimirListaAdyacentes(){
            Nodo* temp = this->getHead();
            while (temp!=nullptr){
                std::cout<<"  Nodo: "<<temp->getNumero()<<" : ";
                std::cout<<std::endl;
                cercanos = temp->getAdyacentes();
                for(int i=0; i<cercanos.size(); i++){
                    std::cout<<" "<<cercanos[i]<<std::endl;
                }
                std::cout<<std::endl;
                temp = temp->getNextNodo();
            }
            std::cout<<std::endl;
        }

        void imprimirLista(){
            Nodo* temp = this->getHead();
            while (temp!=nullptr){
                std::cout<<"  Nodo: "<<temp->getNumero()<<" : ";
                temp = temp->getNextNodo();
            }
            std::cout<<std::endl;
        }

        Nodo *buscaNumero(int i){
            Nodo* temp = this->getHead();
            while(temp!=nullptr){
                if(i == temp->getNumero())
                    return temp;
                temp = temp->getNextNodo();
            }
            return nullptr;
        }

        Nodo *getMas(float x, float y){
            float pos = (x/2) + 0.3;
            int posX = (int) pos;
            float pos2 = -1* (y/2);
            int posY = (int) pos2;
            Nodo *aux = this->head;
            Nodo *aux2 = nullptr;
            int dif = 100;
            while(aux!=nullptr){
                if(aux->getPosicion().x == posY){
                    if(abs(aux->getPosicion().y - posX)< dif){
                        aux2 = aux;
                        dif = abs(aux->getPosicion().y - posX);
                    }
                }
                aux = aux->getNextNodo();
            }
            return aux2;
        }

        Nodo *getMenorCosto(){
            Nodo *aux;
            Nodo *retur;
            if(this->getHead()!=nullptr){
                aux = this->getHead();
                retur = this->getHead();
                int costo = this->getHead()->getCostoTotal();
                if(aux){
                    while(aux->getNextNodo() != nullptr){
                        if(costo > aux->getCostoTotal() ){
                            costo = aux->getCostoTotal();
                            retur = aux;
                        }
                    aux = aux->getNextNodo();
                    }
                }
                return retur;
            }
            return nullptr;
        }

        void *remove (b2Vec2 posicion){
            Nodo* temp = this->getHead();
            Nodo* temp1 = this->getHead()->getNextNodo();
            if(temp->getPosicion() == posicion){
                this->head = temp1;
                tamanyo--;
            }else{
                while(temp1!=nullptr){
                    if(temp1->getPosicion() == posicion){
                        Nodo* aux = temp1;
                        temp->setNext(temp1->getNextNodo());
                        tamanyo--;
                    }
                    temp = temp->getNextNodo();
                    temp1 = temp1->getNextNodo();
                }
            }
        }

        void *insertar(Nodo *nodo){
            Nodo  *aux;
            aux = this->getHead();
            if(!aux){
                this->setHead(nodo);
                nodo->setNext(nullptr);
                tamanyo++;
            }
            else{
                while(aux->getNextNodo() != nullptr){
                    aux = aux->getNextNodo();
                }
                aux->setNext(nodo);
                nodo->setNext(nullptr);
                tamanyo ++;
            }
            return 0;
        }

        Nodo *buscaNodo2(int x, int y){
            Nodo *aux;
            aux = this->head;
            while(aux!=nullptr){
                if(aux->getPosicion().x == x && aux->getPosicion().y == y){
                    return aux;
                }
                aux = aux->getNextNodo();
            }
            return nullptr;
        }

        virtual ~Lista(){}
};

#endif // LISTA_H

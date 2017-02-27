#ifndef LISTA_H
#define LISTA_H

#include <Nodo.h>
#include <Box2D/Box2D.h>
#include <irrlicht.h>
#include <iostream>

//Lista Enlazada Simple
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
        /*Devuelve el ultimo nodo de la lista.
        Busca la cabeza, y si no es NULL, va avanzando
        por los siguientes hasta que encuentra el final
        que si tiene NULL*/
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

        void *vaciarLista(){
            this->head = nullptr;
        }

        void imprimirLista(){
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
                if(aux->getDatos().x == posY){
                    if(abs(aux->getDatos().y - posX)< dif){
                        aux2 = aux;
                        dif = abs(aux->getDatos().y - posX);
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

            if(temp->getDatos() == posicion){
                this->head = temp1;
                tamanyo--;
            }else{
                while(temp1!=nullptr){
                    if(temp1->getDatos() == posicion){
                        Nodo* aux = temp1;
                        temp->setNext(temp1->getNextNodo());
                        //delete aux;
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
        //devuelve true si existe, false si no
        bool buscaNodo(int x, int y){
            //std::cout<<std::endl;
            //std::cout<<"PosixionBusca: "<<x<<" "<<y<<std::endl;

            Nodo *aux;
            aux = this->head;
            while(aux!=nullptr){
                //std::cout<<"Posixion: "<<aux->getDatos().x<<" "<<aux->getDatos().y<<std::endl;
                //std::cout<<"posicionEstoy: "<<aux->getDatos().x<<" "<<aux->getDatos().y<<std::endl;
                if(aux->getDatos().x == x && aux->getDatos().y == y){
                    return true;
                }
                aux = aux->getNextNodo();
            }
            return false;
        }
        //devuelve el nodo si lo encuentra
        Nodo *buscaNodo2(int x, int y){
            //std::cout<<std::endl;
            //std::cout<<"PosixionBusca: "<<x<<" "<<y<<std::endl;
            Nodo *aux;
            aux = this->head;
            while(aux!=nullptr){
                //std::cout<<"Posixion: "<<aux->getDatos().x<<" "<<aux->getDatos().y<<std::endl;
                //std::cout<<"posicionEstoy: "<<aux->getDatos().x<<" "<<aux->getDatos().y<<std::endl;
                if(aux->getDatos().x == x && aux->getDatos().y == y){
                    return aux;
                }
                aux = aux->getNextNodo();
            }
            return nullptr;
        }

        virtual ~Lista(){}

    protected:

};

#endif // LISTA_H

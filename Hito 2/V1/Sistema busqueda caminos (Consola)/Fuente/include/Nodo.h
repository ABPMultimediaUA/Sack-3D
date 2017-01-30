#ifndef NODO_H
#define NODO_H

#include <Box2D/Box2D.h>
#include <irrlicht.h>
#include <iostream>

class Nodo
{
    private:
        Nodo* nextNodo;
        Nodo* nodoPadre;
        Nodo* nodoFinal;
    public:
        b2Vec2 posicion; //DATO: posicion del nodo
        
        
        int cDirecto;
        int cIndirecto;
        int costoTotal;

        Nodo(b2Vec2 posicion, Nodo* nodoFinal, Nodo* nodoPadre, int g){
            this->posicion = posicion;
            this->nodoPadre = nodoPadre;
            this->nodoFinal = nodoFinal;
            this->nextNodo = nullptr;
            cDirecto = g;
            cIndirecto = 0;
            if(nodoPadre != nullptr){
                cDirecto = g + this->nodoPadre->getCostoDirecto();
            }
            if(nodoFinal != nullptr) {
                cIndirecto = costeIndirectoH(this, nodoFinal);
            }
            costoTotal = cDirecto + cIndirecto;
            //std::cout<<"costoTotal: "<<costoTotal<<std::endl;

        }

        void setPadre(Nodo *nodo, int g){
            this->nodoPadre = nodo;
            cDirecto = g;

            if(nodoPadre != nullptr){
                cDirecto = cDirecto + this->nodoPadre->getCostoDirecto();
            }
            this->costoTotal = cDirecto + cIndirecto;
        }

        int getCostoDirecto(){
            return cDirecto;
        }
        void setValor(b2Vec2 datos){
            this->posicion = datos;
        }
        void setNext(Nodo *nodo){
            this->nextNodo = nodo;
        }
        b2Vec2 getDatos(){
            return this->posicion;
        }
        int getCostoTotal(){
            return costoTotal;
        }
        Nodo *getNextNodo(){
            return this->nextNodo;
        } 

        Nodo *getPadre(){
            return this->nodoPadre;
        }

        int nodoSolidoOLibre(int matriz[10][10], Nodo *nodo){
            int x = nodo->getDatos().x;
            int y = nodo->getDatos().y;

            if(matriz[x][y] == 0) return 0;
            else                  return 1;
        }

        int costeDirectoG(Nodo *nodo, Nodo *siguiente){
            int x1 = nodo->getDatos().x;
            int y1 = nodo->getDatos().y;
            int x2 = siguiente->getDatos().x;
            int y2 = siguiente->getDatos().y;

            if( (abs(x1-x2) == 0 && abs(y1-y2) == 1) || (abs(x1-x2) == 1 && abs(y1-y2) == 0) )
                  return 10;
            else if( (abs(x1-x2) == 1 && abs(y1-y2) == 1) || (abs(x1-x2) == 1 && abs(y1-y2) == 1) )
                  return 14;
            else
                  return 0;
        }

        int costeIndirectoH(Nodo *nodo, Nodo *nodoFinal){
            //H = Math.Abs(nodoActual.X – nodoFinal.X) + Math.Abs(nodoActual.Y – nodoFinal.Y)
            int H = 0;
            int x1 = nodo->getDatos().x;
            int y1 = nodo->getDatos().y;
            int x2 = nodoFinal->getDatos().x;
            int y2 = nodoFinal->getDatos().y;

            H = abs(nodo->getDatos().x - nodoFinal->getDatos().x) + abs(nodo->getDatos().y - nodoFinal->getDatos().y);
            H = 10*H;
            return H;
        }


        virtual ~Nodo(){}

    protected:

};

#endif // NODO_H


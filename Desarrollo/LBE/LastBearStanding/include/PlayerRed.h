#ifndef PLAYERRED_H
#define PLAYERRED_H
//---------------------------------------------------------------------------
#include <Box2D/Box2D.h>
#include <irrlicht.h>
#include "Player.h"


class PlayerRed: public Player{
    public:
        PlayerRed(b2Vec2 pos, int mando, char idr[]);
        void actualiza();
        virtual ~PlayerRed(){}
        void mover();
        b2Vec2 getPosition(){return body->GetPosition();}
        void setx(long int aux){
            x = aux/1000000.f;
        }
        void sety(long int aux){
            y = aux/1000000.f;
        }
        void setEstado(int aux){
            estado = aux;
        }
        void setDireccion(int aux){
            direccion = aux;
            if(cogiendo) objCogido->setDireccion(direccion);
        }
        void setMoviendo(int aux){
            moviendo = aux;
        }
        void setId(char aux[]){
            strncpy(id, aux, sizeof(id));
        }
        void setMuerto(bool aux){
            muerto = aux;
        }
    protected:
        int estado;
        int estadoAntiguo;
        bool primera = true;
};

#endif // PLAYERRED_H

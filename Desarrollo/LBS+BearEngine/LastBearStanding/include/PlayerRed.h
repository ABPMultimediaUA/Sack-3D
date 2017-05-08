#ifndef PLAYERRED_H
#define PLAYERRED_H
#include "Player.h"


class PlayerRed: public Player{
    public:
        PlayerRed(b2Vec2 pos, int mando,char *texture,   char idr[], int ve=0, int sal=0);
        virtual void actualiza(MyEventReceiver *events);
        virtual ~PlayerRed();
        virtual void mover(int mov);
        virtual void setx(long int aux);
        virtual void sety(long int aux);
        virtual void setEstado(int aux);
        virtual void setDireccion(int aux);
        virtual void setMoviendo(int aux);
        virtual void setId(char aux[]);
        virtual void setMuerto(bool aux);
        virtual void saltar(int i);
        virtual void setPos();
        virtual void CogerTirar(int m_id);
        virtual void morir();
        virtual void morirRed();
        virtual void usar();
        virtual void fingirMuerte();

    protected:
        int estadoAntiguo;
        bool primera;
};

#endif // PLAYERRED_H

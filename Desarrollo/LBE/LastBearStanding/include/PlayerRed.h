#ifndef PLAYERRED_H
#define PLAYERRED_H
#include "Player.h"


class PlayerRed: public Player{
    public:
        PlayerRed(b2Vec2 pos, int mando, irr::video::SColor color, char idr[]);
        void actualiza();
        virtual ~PlayerRed();
        void mover(int mov);
        void setx(long int aux);
        void sety(long int aux);
        void setEstado(int aux);
        void setDireccion(int aux);
        void setMoviendo(int aux);
        void setId(char aux[]);
        void setMuerto(bool aux);
        void saltar(int i);
        void setPos();
        void CogerTirar(int idCogible);
        void morir();
        void morirRed();
        void usar();

    protected:
        int estadoAntiguo;
        bool primera;
};

#endif // PLAYERRED_H

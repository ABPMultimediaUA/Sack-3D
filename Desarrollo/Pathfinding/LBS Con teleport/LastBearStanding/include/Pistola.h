#ifndef PISTOLA_H
#define PISTOLA_H

#include "Usable.h"

class Pistola: public Usable{
    public:
        Pistola(Spawner* expo, int modelo,b2Vec2 pos);
        ~Pistola();
        void usar();
};

#endif

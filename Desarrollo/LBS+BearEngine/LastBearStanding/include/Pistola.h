#ifndef PISTOLA_H
#define PISTOLA_H

#include "Usable.h"

class Pistola: public Usable{
    public:
        Pistola(Spawner* expo, int modelo,b2Vec2 pos, int id);
        ~Pistola();
        void usar();
};

#endif

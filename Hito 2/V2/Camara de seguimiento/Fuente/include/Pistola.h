#ifndef PISTOLA_H
#define PISTOLA_H

#include "Usable.h"

class Pistola: public Usable{
    public:
        Pistola(int modelo,b2Vec2 pos);    
        virtual ~Pistola(){}		       
        void usar();                       
};

#endif // Pistola_H

#ifndef USABLE_H
#define USABLE_H

#include "Cogible.h"

class Usable : public Cogible{
    public:
        Usable(b2Vec2 pos);
        virtual ~Usable();
        virtual void setExpuesto(bool aux);
        virtual bool getExpuesto();
        virtual void usar();
        //virtual void setIdCogible();
        virtual int getIdCogible();
    protected:
    	bool expuesto = true;
        bool usando = false;
};

#endif

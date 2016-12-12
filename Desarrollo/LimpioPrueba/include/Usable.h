#ifndef USABLE_H
#define USABLE_H

#include "Cogible.h"

class Usable : public Cogible
{
    public:
        Usable();
        void setExpuesto(bool aux);
        bool getExpuesto();
        virtual void usar();
        virtual ~Usable();

    protected:
    	bool expuesto;
        bool usando;

    private:
};

#endif // USABLE_H

#ifndef USABLE_H
#define USABLE_H

#include "Cogible.h"

class Usable : public Cogible
{
    public:
        Usable();
        void setExpuesto(bool aux);
        bool getExpuesto();
        /*
        Spawner* getExpositor();
        virtual void usar(sf::Event::EventType);
        */
        virtual ~Usable();

    protected:
        /*
        Spawner* expositor;
        */
    	bool expuesto;
        bool usando;

    private:
};

#endif // USABLE_H

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
        int getValoacion();         ///< Getter de la valoracion
        virtual ~Usable();

    protected:
    	bool expuesto;
        bool usando;
        int valoracion;           ///< Valoracion del arma dependiendo de lo pro que es

    private:
};

#endif // USABLE_H

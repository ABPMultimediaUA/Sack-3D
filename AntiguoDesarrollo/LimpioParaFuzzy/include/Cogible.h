#ifndef COGIBLE_H
#define COGIBLE_H

#include <Box2D/Box2D.h>
#include <irrlicht.h>

class Cogible
{
    public:
        Cogible();
        virtual b2Body* getBody();
        bool getCogido();
        void setCogido(bool aux);
        int getValoacion();         ///< Getter de la valoracion
        virtual ~Cogible();

    protected:

        bool cogido;
        int valoracion;           ///< Valoracion del arma dependiendo de lo pro que es
    private:
};

#endif // COGIBLE_H

#ifndef COGIBLE_H
#define COGIBLE_H

#include <Box2D/Box2D.h>
#include <irrlicht.h>

class Cogible
{
    public:
        Cogible();
        virtual b2Body* getBody();
        void setDireccion(int);
        bool getCogido();
        void setCogido(bool aux);
        virtual ~Cogible();

    protected:
        bool cogido;
        int dir;

    private:
};

#endif // COGIBLE_H

#ifndef COGIBLE_H
#define COGIBLE_H

#include <Box2D/Box2D.h>
#include <irrlicht.h>

class Cogible
{
    public:
        Cogible();
        b2Body* getBody();
        bool getCogido();
        void setCogido(bool aux);
        virtual ~Cogible();

    protected:

        bool cogido;

    private:
};

#endif // COGIBLE_H

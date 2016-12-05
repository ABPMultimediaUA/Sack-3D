#ifndef COGIBLE_H
#define COGIBLE_H

#include <Box2D/Box2D.h>
#include <irrlicht.h>

class Cogible
{
    public:
        Cogible();
        //void actualiza();
        b2Body* getBody();
        /*
        bool getADestruir();
        bool getDespawnear();
        */
        bool getCogido();
        /*
        virtual void muellazo(int fuerza);
        */
        void setCogido(bool aux);
        virtual ~Cogible();

    protected:
        /*
        IMeshSceneNode* node;
	    b2Body* body;
	    */
        bool cogido;
        /*
        bool aDestruir;
        bool humo;
    	bool despawnear;
        */
    private:
};

#endif // COGIBLE_H

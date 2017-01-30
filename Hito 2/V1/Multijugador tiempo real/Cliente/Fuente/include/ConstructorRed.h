#ifndef CONSTRUCTORRED_H
#define CONSTRUCTORRED_H
//---------------------------------------------------------------------------
#include <Box2D/Box2D.h>
#include <irrlicht.h>


using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class ConstructorRed
{
    public:
        ConstructorRed(float xr, float yr);
        void actualiza();
        b2Body* getBody();
        virtual ~ConstructorRed();
        void setx(long int aux);
        void sety(long int aux);
        void setVivo(int aux);
        void setDireccion(int aux);
        void teletransportar();
        void fingirMuerte();
        IMeshSceneNode* node;
	    b2Body* body;

    protected:

        float x;
        float y;
        int vivo;
        int vivoAntiguo;
        int direccion;
        vector3df tam;
        b2Fixture* personFixture;                ///<

    private:
};

#endif // CONSTRUCTORRED_H

#ifndef BALA_H
#define BALA_H
#include <Box2D/Box2D.h>
#include <irrlicht.h>
class Bala{
    public:
        Bala(irr::core::vector3df, int, int, float, int);
        virtual ~Bala(){}
        void actualiza();
        void teletransportar();
        b2Body* getBody(){return body;}
        irr::scene::IMeshSceneNode* getNode(){return node;}
        b2Fixture* getbalaFixture(){return balaFixture;}
        void setNextPos(b2Vec2 pos){teletransportado=true; nextPos = pos;}
        int getTime(){return timerbala;}
        int getTimeVida(){return tiempoVida;}
    private:
        irr::core::vector3df tam;
        int tiempoVida;
        float desviacion;
        irr::f32 timerbala;
        irr::ITimer* timerIrr;
        irr::scene::IMeshSceneNode* node;
	    b2Body* body;
        b2Fixture* balaFixture;
        b2Vec2 nextPos;
		bool teletransportado;
};
#endif // BALA_H

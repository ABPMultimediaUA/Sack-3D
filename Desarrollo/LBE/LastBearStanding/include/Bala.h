#ifndef BALA_H
#define BALA_H
#include <Box2D/Box2D.h>
#include <irrlicht.h>
class Bala{
    public:
        Bala( irr::core::vector3df pos, int tiempoVidaP, int velocidad, float deviacionP, int dir, int tipo = 0);
        virtual ~Bala();
        void actualiza();
        void teletransportar();
        b2Body* getBody(){return body;}
        irr::scene::IMeshSceneNode* getNode(){return node;}
        b2Fixture* getbalaFixture(){return balaFixture;}
        void setNextPos(b2Vec2 pos){teletransportado=true; nextPos = pos;}
        void setDestruir(bool aux){ destruir = aux;}
        int getDestruir(){return destruir;}
    private:
        irr::core::vector3df tam;
        int tiempoVida;
        float desviacion;
        irr::f32 time2Kill;           
        irr::ITimer* timer2Kill;    
        irr::scene::IMeshSceneNode* node;
	    b2Body* body;
        b2Fixture* balaFixture;
        b2Vec2 velo;
        b2Vec2 nextPos;
        int dir;
        bool teletransportado;
		bool destruir = false;
};
#endif // BALA_H

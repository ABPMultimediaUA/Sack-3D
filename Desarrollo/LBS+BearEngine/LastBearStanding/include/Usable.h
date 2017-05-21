#ifndef USABLE_H
#define USABLE_H

#include "Cogible.h"

class Usable : public Cogible{
    public:
        Usable(PhysicBody* physicBody ,Spawner* expo, b2Vec2 pos, glm::vec3 tam,char *model = "BearEngine/res/cubo.obj", char *texture = NULL, int id=0);
        virtual ~Usable();
        virtual void usar();
        virtual void actualiza();
        virtual void CompruebaVida();
        virtual int getUsos();
    protected:
        bool usando;
	    int usos;
        int cadencia;
        bool killCountDown;
        uint32 time2Kill;
        uint32 timeCadencia;
};

#endif

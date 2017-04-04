#ifndef PBDEADPLAYER_H
#define PBDEADPLAYER_H

#include "PhysicBody.h"

class PBDeadPlayer: public PhysicBody{
    public:
        PBDeadPlayer();
        virtual ~PBDeadPlayer();
        virtual int   Inicialize(b2Vec2 pos, b2Vec2 tam);
        virtual b2Vec2 GetPosition();
		virtual b2Vec2 GetLinearVelocity();
        virtual float  GetRotation();
        virtual int    GetId();
        virtual void   SetFixedRotation(bool fixed);
        virtual void   SetGravity(float gr);
        virtual void   SetRotation(float angle);
		virtual void   SetAngularVelocity(float imp);
        virtual void   SetLinearVelocity(b2Vec2 vel);
        virtual void   SetPosition(b2Vec2 pos);
        virtual void   DestroyFixtures();
        virtual void   SetCategory(uint16 i);
        virtual void   SetUserData(int i);
        virtual void   SetMask(uint16 i);
        virtual void   Catch(int id);
        virtual void   Release();

    private:
    	virtual void   InitBody(b2Vec2 pos,b2Vec2 tam);
        virtual void   InitFixtures(b2Vec2 tam);
        virtual void   DestroyBody();
};

#endif // PBDEADPLAYER_H

#ifndef MYCONTACTLISTENER_H
#define MYCONTACTLISTENER_H
#include "Box2D/Box2D.h"
#include <iostream>
class MyContactListener: public b2ContactListener
{
    public:
        MyContactListener();
        virtual ~MyContactListener();
        void BeginContact(b2Contact* contact);
        void EndContact(b2Contact* contact);


    protected:

    private:
};

#endif // MYCONTACTLISTENER_H

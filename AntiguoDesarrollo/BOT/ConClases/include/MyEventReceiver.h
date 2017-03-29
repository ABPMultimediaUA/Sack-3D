#ifndef MYEVENTRECEIVER_H
#define MYEVENTRECEIVER_H

#include <Box2D/Box2D.h>
#include <iostream>
#include <irrlicht.h>
#include "cuboMierda.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class MyEventReceiver: public IEventReceiver{
     public:
     	MyEventReceiver();
     	virtual bool OnEvent(const SEvent& event);
        virtual ~MyEventReceiver();
		virtual bool IsKeyDown(EKEY_CODE keyCode)const; 
    private:
    	bool KeyIsDown[KEY_KEY_CODES_COUNT];
};

#endif // MYEVENTRECEIVER_H

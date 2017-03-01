
#ifndef MYEVENTRECEIVER_H
#define MYEVENTRECEIVER_H
#include <irrlicht.h>

class MyEventReceiver: public irr::IEventReceiver{
     public:
     	MyEventReceiver();
     	virtual bool OnEvent(const irr::SEvent& event);
        virtual ~MyEventReceiver();
		virtual bool IsKeyDown(irr::EKEY_CODE keyCode)const;
    private:
    	bool KeyIsDown[irr::KEY_KEY_CODES_COUNT];
};

#endif

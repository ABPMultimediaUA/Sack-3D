
#ifndef MYEVENTRECEIVER_H
#define MYEVENTRECEIVER_H
#include <irrlicht.h>

class MyEventReceiver;
struct Key2Method{
	irr::EKEY_CODE keyCode;
    void (MyEventReceiver::*p)();
};
class MyEventReceiver: public irr::IEventReceiver{
     public:
     	MyEventReceiver();
        virtual ~MyEventReceiver(){}
     	virtual bool OnEvent(const irr::SEvent& event);
		virtual bool IsKeyDown(irr::EKEY_CODE keyCode)const;
		void ClickEspacio();
		void ClickEnter();
		void ClickQ();
		void ClickE();
    void ClickEscape();
		void ClickF12();
    private:
    	bool KeyIsDown[irr::KEY_KEY_CODES_COUNT];
    	const static Key2Method keys[7];
};

#endif

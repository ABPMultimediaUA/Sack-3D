
#include "MyEventReceiver.h"
#include "BearManager.h"
#include "Player.h"
#include "World.h"

void MyEventReceiver::OnEvent(SDL_Event *event){
    if(event->key.keysym.sym>=0 && event->key.keysym.sym<=128){
    	if(event->type == SDL_KEYDOWN ){
	        KeyIsDown[event->key.keysym.sym] = true;
	    }
	    else if(event->type == SDL_KEYUP ){
	        KeyIsDown[event->key.keysym.sym] = false;
	    }
	}
}

bool MyEventReceiver::IsKeyDown(SDL_Keycode key) const{
  return KeyIsDown[key];
}
MyEventReceiver::MyEventReceiver(){
  for (int i=0; i<128; ++i)KeyIsDown[i] = false;
}

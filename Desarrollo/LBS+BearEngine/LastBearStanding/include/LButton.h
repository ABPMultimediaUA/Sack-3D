#ifndef LBUTTON_H
#define LBUTTON_H

//Using SDL, SDL_image, SDL_ttf, standard IO, strings, and string streams
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <iostream>
#include "LTexture.h"
//#include "Menu.h"

enum LButtonSprite
{
    BUTTON_SPRITE_MOUSE_OUT = 0,
    BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
    BUTTON_SPRITE_MOUSE_DOWN = 2,
    BUTTON_SPRITE_MOUSE_UP = 3,
    BUTTON_SPRITE_TOTAL = 4
};

class LButton
{
    public:
        //Initializes internal variables
        LButton();
        ~LButton();
        //Sets top left position
        void setPosition( int x, int y, int width, int height );

        //Handles mouse event
        void handleEvent( SDL_Event* e );

        //Shows button sprite
        void render(LTexture gButtonSpriteSheetTexture, SDL_Renderer* gRenderer/*, SDL_Rect gSpriteClips[]*/);

        int getX(){return mPosition.x;}
        int getY(){return mPosition.y;}
        int getState(){return mCurrentSprite;}
    private:
        //Top left position
        SDL_Point mPosition;

        //Currently used global sprite
        LButtonSprite mCurrentSprite;
        int BUTTON_WIDTH;
        int BUTTON_HEIGHT;
};

#endif // LBUTTON_H

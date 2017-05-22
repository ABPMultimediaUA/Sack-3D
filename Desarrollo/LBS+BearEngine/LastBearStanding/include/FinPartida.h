#ifndef FINPARTIDA_H
#define FINPARTIDA_H

//Using SDL, SDL_image, SDL_ttf, standard IO, strings, and string streams
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <iostream>
#include "LTexture.h"
#include "LButton.h"
class FinPartida
{
    public:
        FinPartida();
        //Starts up SDL and creates window
        bool init();
        //Loads media
        bool loadMedia();

        SDL_Texture* loadTexture( std::string path );
        //Frees media and shuts down SDL
        void close();

        void update();
        bool getOn(){return on;}
        void setWinner(int w);
        //bool getOn(){return on;}
        virtual ~FinPartida();

    protected:

    private:
        SDL_Window* gWindow = NULL;
        //The window renderer
        SDL_Renderer* gRenderer = NULL;
        //Globally used font
        TTF_Font *gFont = NULL;
        SDL_Texture* gTexture0 = NULL;
        SDL_Texture* gTexture1 = NULL;
        SDL_Texture* gTexture2 = NULL;
        SDL_Texture* gTexture3 = NULL;
        SDL_Surface *gWindowSurface;
        SDL_Surface *gFondoSurface;
        //Scene textures
        LTexture gPromptTextTexture;
        LTexture gInputTextTexture;

        LTexture gSpriteSheetTextureBackground;
        LTexture gSpriteSheetTextureFigure;
        //LTexture gSpriteSheetTexturePressedClicked;
        int SCREEN_WIDTH;
        int SCREEN_HEIGHT;
        int BUTTON_WIDTH;
        int BUTTON_HEIGHT;
        bool on;
        int winner;

};

#endif // FINPARTIDA_H

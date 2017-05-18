#ifndef MENU_H
#define MENU_H

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

//Screen dimension constants
//const int SCREEN_WIDTH = 640;
//const int SCREEN_HEIGHT = 480;

//Button constants
/*const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 200;*/
const int TOTAL_BUTTONS = 5;

//class LButton;
class Menu
{
    public:
        Menu(/*SDL_Window* pWindow, SDL_Renderer* pRenderer*/);
        //Starts up SDL and creates window
        bool init();
        //Loads media
        bool loadMedia();

        SDL_Texture* loadTexture( std::string path );
        //Frees media and shuts down SDL
        void close();

        void update();
        bool getOn(){return on;}
        int getDifficult(){return difficult;}
        std::string getGameMode(){return gameMode;}
        std::string getIP(){return IP;}
        //bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
        virtual ~Menu();


    protected:

    private:
        //The window we'll be rendering to
        SDL_Window* gWindow = NULL;
        //The window renderer
        SDL_Renderer* gRenderer = NULL;
        //Globally used font
        TTF_Font *gFont = NULL;
        SDL_Texture* gTexture = NULL;
        SDL_Surface *gWindowSurface;
        SDL_Surface *gFondoSurface;
        //Scene textures
        LTexture gPromptTextTexture;
        LTexture gInputTextTexture;

        SDL_Rect gSpriteClips[ BUTTON_SPRITE_TOTAL ];
        LTexture gButtonSpriteSheetTexture;
        LTexture gButtonSpriteSheetTexturePressed;
        LTexture gButtonSpriteSheetTexturePressedClicked;
        LTexture gButtonSpriteSheetTexture2;
        LTexture gButtonSpriteSheetTexturePressed2;
        LTexture gButtonSpriteSheetTexturePressedClicked2;
        LTexture gButtonSpriteSheetTexture3;
        LTexture gButtonSpriteSheetTexturePressed3;
        LTexture gButtonSpriteSheetTexture4;
        LTexture gButtonSpriteSheetTexturePressed4;
        LTexture gButtonSpriteSheetTexture5;
        LTexture gButtonSpriteSheetTexturePressed5;
        LTexture gButtonSpriteSheetPanel;
        //LTexture gButtonSpriteSheetTexture;
        //LTexture gButtonSpriteSheetTexture;

        //Buttons objects
        LButton gButtons[ TOTAL_BUTTONS ];
        bool ipPanel;
        bool difficultPanel;
        int SCREEN_WIDTH;
        int SCREEN_HEIGHT;
        int BUTTON_WIDTH;
        int BUTTON_HEIGHT;
        std::string gameMode;
        std::string IP;
        int difficult;
        bool on;
        bool desactivarDectector;
};

#endif // MENU_H

//#ifdef _SDL_TTF_H

//#endif


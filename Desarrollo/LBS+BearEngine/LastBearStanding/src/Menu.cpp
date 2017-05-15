#include "Menu.h"
#include "LTexture.h"
#include "BearManager.h"
#include "../BearEngine/include/tmotorbear.h"

//Button constants
/*const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 200;
const int TOTAL_BUTTONS = 4;

enum LButtonSprite
{
    BUTTON_SPRITE_MOUSE_OUT = 0,
    BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
    BUTTON_SPRITE_MOUSE_DOWN = 2,
    BUTTON_SPRITE_MOUSE_UP = 3,
    BUTTON_SPRITE_TOTAL = 4
};*/

class TMotorBear;
Menu::Menu(/*SDL_Window* pWindow, SDL_Renderer* pRenderer*/)
{
        gWindow = BearMngr::Inst()->getMotorBear()->getEscena()->getWindow();
        //The window renderer
        gRenderer = BearMngr::Inst()->getMotorBear()->getEscena()->getRenderer();

        gWindowSurface = BearMngr::Inst()->getMotorBear()->getEscena()->getWindowSurface();

        gFondoSurface = BearMngr::Inst()->getMotorBear()->getEscena()->getFondoSurface();
        SCREEN_HEIGHT = BearMngr::Inst()->getMotorBear()->getEscena()->getHeight();
        SCREEN_WIDTH = BearMngr::Inst()->getMotorBear()->getEscena()->getWidth();
        on = true;
        BUTTON_HEIGHT = SCREEN_HEIGHT / 10;
        BUTTON_WIDTH = SCREEN_HEIGHT / 6;
}

Menu::~Menu()
{
    //dtor
}

void Menu::update(){


    //Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//Set text color as black
			SDL_Color textColor = { 255, 255, 255, 0xFF };

			//The current input text.
			std::string inputText = "";
			gInputTextTexture.loadFromRenderedText( inputText.c_str(), textColor, gWindow, gRenderer, gFont);

			//Enable text input

			SDL_StartTextInput();

			//While application is running
			while( !quit )
			{   gButtonSpriteSheetTexture.loadFromFile( "media/Images/singleplayer-btn.png", gRenderer );
				//The rerender text flag
				bool renderText = false;
               // SDL_RenderPresent( gRenderer );
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
				     //Handle button events
                    for( int i = 0; i < TOTAL_BUTTONS; ++i )
                    {
                        gButtons[ i ].handleEvent( &e );
                    }
					//User requests quit
					if( e.key.keysym.sym == SDLK_1 )
					{

					}
					if( e.key.keysym.sym == SDLK_KP_ENTER )
					{

					}
					if( e.key.keysym.sym == SDLK_3 )
					{
						inputText = inputText.substr(0, inputText.size()-1);
						IP = inputText;
					}
					//Special key input
					else if( e.type == SDL_KEYDOWN )
					{
						//Handle backspace
						if( e.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0 )
						{
							//lop off character
							//inputText.pop_back();
							inputText = inputText.substr(0, inputText.size()-1);
							renderText = true;
						}
						//Handle copy
						else if( e.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL )
						{
							SDL_SetClipboardText( inputText.c_str() );
						}
						//Handle paste
						else if( e.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL )
						{
							inputText = SDL_GetClipboardText();
							renderText = true;
						}
						//Obtain
						else if( e.key.keysym.sym == SDLK_0 ){
                            //std::cout<<inputText<<std::endl;
						}
					}
					//Special text input event
					else if( e.type == SDL_TEXTINPUT )
					{
						//Not copy or pasting
						if( !( ( e.text.text[ 0 ] == 'c' || e.text.text[ 0 ] == 'C' ) && ( e.text.text[ 0 ] == 'v' || e.text.text[ 0 ] == 'V' ) && SDL_GetModState() & KMOD_CTRL ) )
						{
							//Append character
							inputText += e.text.text;
							renderText = true;
						}
					}
				}
                				//Apply the image
			//SDL_BlitSurface( gFondoSurface, NULL, gWindowSurface, NULL );
			//Update the surface
			//SDL_UpdateWindowSurface( gWindow );
				//Rerender text if needed
				if( renderText )
				{
					//Text is not empty
					if( inputText != "" )
					{
						//Render new text
						gInputTextTexture.loadFromRenderedText( inputText.c_str(), textColor, gWindow, gRenderer, gFont );
					}
					//Text is empty
					else
					{
						//Render space texture
						gInputTextTexture.loadFromRenderedText( " ", textColor, gWindow, gRenderer, gFont );
					}
				}


				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

                //Render texture to screen
                SDL_RenderCopy( gRenderer, gTexture, NULL, NULL );

				//Render text textures
				gPromptTextTexture.render( ( SCREEN_WIDTH - gPromptTextTexture.getWidth() ) / 2, 0, gRenderer);
				gInputTextTexture.render( ( SCREEN_WIDTH - gInputTextTexture.getWidth() ) / 2, gPromptTextTexture.getHeight(), gRenderer );
                //std::cout<<"HDHDHBBDBDBHDBHDBH"<<std::endl;
                //Render buttons
                    for( int i = 0; i < TOTAL_BUTTONS; ++i )
                    {
                        //std::cout<<TOTAL_BUTTONS<<std::endl;
                        if(i==0){
                            if(gButtons[ i ].getState()==0)
                            gButtonSpriteSheetTexture.render(gButtons[ i ].getX(), gButtons[ i ].getY(), gRenderer);
                            else if (gButtons[ i ].getState()==1)
                            gButtonSpriteSheetTexturePressed.render(gButtons[ i ].getX(), gButtons[ i ].getY(), gRenderer);
                            else if  (gButtons[ i ].getState()==2 && i==0){
                            gameMode.assign("s");
                            quit = true;
                            }
                        }
                        if(i==1){
                            if(gButtons[ i ].getState()==0)
                            gButtonSpriteSheetTexture2.render(gButtons[ i ].getX(), gButtons[ i ].getY(), gRenderer);
                            else if (gButtons[ i ].getState()==1)
                            gButtonSpriteSheetTexturePressed2.render(gButtons[ i ].getX(), gButtons[ i ].getY(), gRenderer);
                            else if  (gButtons[ i ].getState()==2 ){
                            gameMode.assign("s");
                            quit = true;
                            }
                        }
                        if(i==2){
                            if(gButtons[ i ].getState()==0)
                            gButtonSpriteSheetTexture3.render(gButtons[ i ].getX(), gButtons[ i ].getY(), gRenderer);
                            else if (gButtons[ i ].getState()==1)
                            gButtonSpriteSheetTexturePressed3.render(gButtons[ i ].getX(), gButtons[ i ].getY(), gRenderer);
                            else if  (gButtons[ i ].getState()==2 ){
                            gameMode.assign("s");
                            quit = true;
                            }
                        }
                    }


				//Update screen
				SDL_RenderPresent( gRenderer );
			}
	}

			//Disable text input
			SDL_StopTextInput();


		}


	//Free resources and close SDL
	close();
}

bool Menu::init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		//gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			//gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

				 //Initialize SDL_ttf
				if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}
			}
		}

		//Initialize PNG loading
        int imgFlags = IMG_INIT_PNG;
        if( !( IMG_Init( imgFlags ) & imgFlags ) )
        {
            printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
            success = false;
        }
	}

	return success;
}

bool Menu::loadMedia()
{
	//Loading success flag
	bool success = true;

	//Open the font
	gFont = TTF_OpenFont( "media/Fuentes/Gloria.ttf", 28 );
	if( gFont == NULL )
	{
		printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}
	else
	{
		//Render the prompt
		SDL_Color textColor = { 255, 255, 255, 0xFF };
		if( !gPromptTextTexture.loadFromRenderedText( "Select Single(s) or Multiplayer(m) mode:", textColor, gWindow, gRenderer, gFont ) )
		{
			printf( "Failed to render prompt text!\n" );
			success = false;
		}
	}

	//Load PNG texture
    gTexture = loadTexture( "media/Images/background.png" );
    if( gTexture == NULL )
    {
        printf( "Failed to load texture image!\n" );
        success = false;
    }

    if( !gButtonSpriteSheetTexture.loadFromFile( "media/Images/singleplayer-btn.png", gRenderer ) )
	{
		printf( "Failed to load button sprite texture!\n" );
		success = false;
	}

	if( !gButtonSpriteSheetTexturePressed.loadFromFile( "media/Images/singleplayer-btn-hover.png", gRenderer ) )
	{
		printf( "Failed to load button sprite texture!\n" );
		success = false;
	}

	if( !gButtonSpriteSheetTexture2.loadFromFile( "media/Images/multiplayer-btn.png", gRenderer ) )
	{
		printf( "Failed to load button sprite texture!\n" );
		success = false;
	}

	if( !gButtonSpriteSheetTexturePressed2.loadFromFile( "media/Images/multiplayer-btn-hover.png", gRenderer ) )
	{
		printf( "Failed to load button sprite texture!\n" );
		success = false;
	}

	if( !gButtonSpriteSheetTexture3.loadFromFile( "media/Images/exit-btn.png", gRenderer ) )
	{
		printf( "Failed to load button sprite texture!\n" );
		success = false;
	}

	if( !gButtonSpriteSheetTexturePressed3.loadFromFile( "media/Images/exit-btn-hover.png", gRenderer ) )
	{
		printf( "Failed to load button sprite texture!\n" );
		success = false;
	}

	//Set sprites
		for( int i = 0; i < BUTTON_SPRITE_TOTAL; ++i )
		{
			gSpriteClips[ i ].x = 0;
			gSpriteClips[ i ].y = 1 * 200;
			gSpriteClips[ i ].w = BUTTON_WIDTH;
			gSpriteClips[ i ].h = BUTTON_HEIGHT;
		}

		//Set buttons in corners
		gButtons[ 0 ].setPosition( SCREEN_WIDTH/2.8f, SCREEN_HEIGHT/3.8f );
		gButtons[ 1 ].setPosition( SCREEN_WIDTH/2.8f, SCREEN_HEIGHT/3.8f + 1.5f* BUTTON_HEIGHT  );
		gButtons[ 2 ].setPosition( SCREEN_WIDTH/2.8f, SCREEN_HEIGHT/3.5f + 5* BUTTON_HEIGHT );
		//gButtons[ 3 ].setPosition( SCREEN_WIDTH/3, SCREEN_HEIGHT - BUTTON_HEIGHT );
	//Load splash image
	/*gFondoSurface = SDL_LoadBMP( "diablo2.bmp" );
	if( gFondoSurface == NULL )
	{
		printf( "Unable to load image %s! SDL Error: %s\n", "diablo2.bmp", SDL_GetError() );
		success = false;
	}*/

	return success;
}

SDL_Texture* Menu::loadTexture( std::string path )
{
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
    //Create texture from surface pixels
    newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
    if( newTexture == NULL )
    {
        printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
    }

    //Get rid of old loaded surface
    SDL_FreeSurface( loadedSurface );
    }

    return newTexture;
}

void Menu::close()
{
    on=false;
}

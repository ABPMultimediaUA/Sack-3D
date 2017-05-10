#include "Menu.h"
#include "LTexture.h"
#include "BearManager.h"
#include "../BearEngine/include/tmotorbear.h"
class TMotorBear;
Menu::Menu(/*SDL_Window* pWindow, SDL_Renderer* pRenderer*/)
{
        gWindow = BearMngr::Inst()->getMotorBear()->getEscena()->getWindow();
        //The window renderer
        gRenderer = BearMngr::Inst()->getMotorBear()->getEscena()->getRenderer();

        SCREEN_HEIGHT = BearMngr::Inst()->getHeight();
        SCREEN_WIDTH = BearMngr::Inst()->getWidth();
        on = true;
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
			SDL_Color textColor = { 0, 0, 0, 0xFF };

			//The current input text.
			std::string inputText = "";
			gInputTextTexture.loadFromRenderedText( inputText.c_str(), textColor, gWindow, gRenderer, gFont);

			//Enable text input
			SDL_StartTextInput();

			//While application is running
			while( !quit )
			{
				//The rerender text flag
				bool renderText = false;

				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.key.keysym.sym == SDLK_1 )
					{

					}
					if( e.key.keysym.sym == SDLK_KP_ENTER )
					{
						gameMode.assign(inputText);
						quit = true;
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
                            std::cout<<inputText<<std::endl;
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

				//Render text textures
				gPromptTextTexture.render( ( SCREEN_WIDTH - gPromptTextTexture.getWidth() ) / 2, 0, gRenderer);
				gInputTextTexture.render( ( SCREEN_WIDTH - gInputTextTexture.getWidth() ) / 2, gPromptTextTexture.getHeight(), gRenderer );

				//Update screen
				SDL_RenderPresent( gRenderer );
			}


			//Disable text input
			SDL_StopTextInput();
		}
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
	}

	return success;
}

bool Menu::loadMedia()
{
	//Loading success flag
	bool success = true;

	//Open the font
	gFont = TTF_OpenFont( "lazy.ttf", 28 );
	if( gFont == NULL )
	{
		printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}
	else
	{
		//Render the prompt
		SDL_Color textColor = { 0, 0, 0, 0xFF };
		if( !gPromptTextTexture.loadFromRenderedText( "Select Single(s) or Multiplayer(m) mode:", textColor, gWindow, gRenderer, gFont ) )
		{
			printf( "Failed to render prompt text!\n" );
			success = false;
		}
	}

	return success;
}

void Menu::close()
{
    on=false;
}

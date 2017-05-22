#include "FinPartida.h"
#include "Menu.h"
#include "LTexture.h"
#include "BearManager.h"
#include "../BearEngine/include/tmotorbear.h"

FinPartida::FinPartida()
{
    gWindow = BearMngr::Inst()->getMotorBear()->getEscena()->getWindow();
    //The window renderer
    gRenderer = BearMngr::Inst()->getMotorBear()->getEscena()->getRenderer();

    gWindowSurface = BearMngr::Inst()->getMotorBear()->getEscena()->getWindowSurface();

    gFondoSurface = BearMngr::Inst()->getMotorBear()->getEscena()->getFondoSurface();
    on = true;
    SCREEN_HEIGHT = BearMngr::Inst()->getMotorBear()->getEscena()->getHeight();
    SCREEN_WIDTH = BearMngr::Inst()->getMotorBear()->getEscena()->getWidth();
    BUTTON_HEIGHT = SCREEN_HEIGHT / 10;
    BUTTON_WIDTH = SCREEN_HEIGHT / 2.3f;
    winner=0;
}

void FinPartida::update(){
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
			{
				//The rerender text flag
				bool renderText = false;
               // SDL_RenderPresent( gRenderer );
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
				     //Handle button events
					//User requests quit
					if( e.key.keysym.sym == SDLK_RETURN )
					{
                        SDL_Quit();
					}

                    else if(e.key.keysym.sym == SDLK_ESCAPE){ 
                    	//std::cout<<"UEJHRJHE"<<std::endl; 
                    	quit = true; 
                    	close();
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
                if(winner==0){
                    SDL_RenderCopy( gRenderer, gTexture0, NULL, NULL );
                }else if(winner==1){
                    SDL_RenderCopy( gRenderer, gTexture1, NULL, NULL );
                }else if(winner==2){
                    SDL_RenderCopy( gRenderer, gTexture2, NULL, NULL );
                }else{
                SDL_RenderCopy( gRenderer, gTexture3, NULL, NULL );
                }


				//Render text textures
				//gPromptTextTexture.render( ( SCREEN_WIDTH - gPromptTextTexture.getWidth() ) / 2, 0, gRenderer);
				gInputTextTexture.render( SCREEN_WIDTH/2.15f, SCREEN_HEIGHT/3.3f + 2.8f* BUTTON_HEIGHT, gRenderer );

				//Update screen
				SDL_RenderPresent( gRenderer );
			}
	}
			//Disable text input
			SDL_StopTextInput();


		}

}

bool FinPartida::init()
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

bool FinPartida::loadMedia()
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
    gTexture0 = loadTexture( "media/Images/red-win.png" );
    if( gTexture0 == NULL )
    {
        printf( "Failed to load texture image!\n" );
        success = false;
    }
    gTexture1 = loadTexture( "media/Images/green-win.png" );
    if( gTexture0 == NULL )
    {
        printf( "Failed to load texture image!\n" );
        success = false;
    }
    gTexture2 = loadTexture( "media/Images/yellow-win.png" );
    if( gTexture0 == NULL )
    {
        printf( "Failed to load texture image!\n" );
        success = false;
    }
    gTexture3 = loadTexture( "media/Images/lila-win.png" );
    if( gTexture0 == NULL )
    {
        printf( "Failed to load texture image!\n" );
        success = false;
    }

  /*  if( !gButtonSpriteSheetTexture.loadFromFile( "media/Images/singleplayer-btn.png", gRenderer ) )
	{
		printf( "Failed to load button sprite texture!\n" );
		success = false;
	}*/


	return success;
}

SDL_Texture* FinPartida::loadTexture( std::string path )
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

void FinPartida::close(){
	//std::cout<<"pongo a false"<<std::endl;
    on=false;
}

void FinPartida::setWinner(int w){
    winner=w;
}

FinPartida::~FinPartida()
{
    //dtor
}

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>



int main(int argc, char* argv[]){
    SDL_Window *window = nullptr;

    SDL_Surface *windowSurface = nullptr;
    SDL_Surface *fondo = nullptr;
    SDL_Event event;
    bool isRuning = true;
    TTF_Font *font = nullptr;

    //INICIALIZACION

    if(SDL_Init(SDL_INIT_VIDEO)< 0){
        std::cout<<"ERROR VIDEO INIT: "<<SDL_GetError()<<std::endl;
    }
    window = SDL_CreateWindow("LBS", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    windowSurface = SDL_GetWindowSurface(window);

    if(TTF_Init() <0 ){
        std::cout<<"ERROR FUENTE INIT: "<<TTF_GetError()<<std::endl;
    }
    font = TTF_OpenFont("assets/arial.ttf", 20);

    fondo = IMG_Load("assets/fondo.jpg");
    if(fondo == nullptr)
        std::cout<<"ERROR CARGA IMG: "<<IMG_GetError()<<std::endl;

    const int NUMMENU = 3;
    const char* labels[NUMMENU] = {"JUGAR","OPCIONES","SALIR"};
    SDL_Surface* menus[NUMMENU];

    //Color[0] no selecionado -> color[1] cuando se selecione
    SDL_Color color[2] = {{255,255,255},{255,0,0}};
    SDL_Rect pos[NUMMENU];
    for(int i=0; i<NUMMENU; i++){
        if(i==0){
            menus[i] = TTF_RenderText_Solid(font,labels[i],color[1]);
        }
        else{
            menus[i] = TTF_RenderText_Solid(font,labels[i],color[0]);
        }
        pos[i].x = windowSurface->clip_rect.w/2 - menus[0]->clip_rect.w/2;
        pos[i].y = windowSurface->clip_rect.h/2 + i*menus[0]->clip_rect.h;
    }
    //BUCLE JUEGO
    int select  =0;
    while(isRuning){
        while(SDL_PollEvent(&event) != 0){
            //obtener los eventos de teclado
            if(event.type == SDL_QUIT){
                isRuning=false;
            }
            else if(event.type == SDL_KEYDOWN){
                //std::cout<<"TECLA: "<<SDL_GetKeyName(event.key.keysym.sym)<<std::endl;
                switch(event.key.keysym.sym){

                    case SDLK_DOWN:

                        select = select+1;

                        if(select == NUMMENU)
                            select=0;
                        //dibujar
                        for(int i=0; i<NUMMENU; i++){
                            if(i==select){
                                menus[i] = TTF_RenderText_Solid(font,labels[i],color[1]);
                            }
                            else{
                                menus[i] = TTF_RenderText_Solid(font,labels[i],color[0]);
                            }
                        }
                    break;
                    case SDLK_UP:
                        select = select-1;


                        if(select < 0){
                            select=NUMMENU-1;
                            }
                        for(int i=0; i<NUMMENU; i++){
                            if(i==select){
                                menus[i] = TTF_RenderText_Solid(font,labels[i],color[1]);
                            }
                            else{
                                menus[i] = TTF_RenderText_Solid(font,labels[i],color[0]);
                            }
                        }

                    break;
                    case SDLK_RETURN:
                            switch (select){
                            case 0:
                                std::cout<<"Jugar"<<std::endl;
                                break;
                            case 1:
                                std::cout<<"Opciones"<<std::endl;
                                break;
                            case 2:
                                std::cout<<"Salir"<<std::endl;
                                isRuning = false;
                                break;
                            default:
                                break;
                            }
                    break;
                    case SDLK_ESCAPE:
                        isRuning = false;
                        std::cout<<"SALIR"<<std::endl;
                    break;
                }
            }
        }

        //Fin while pollevent
        SDL_BlitSurface(fondo, NULL, windowSurface, NULL);
        SDL_UpdateWindowSurface(window);
        for(int i = 0; i < NUMMENU; i += 1) {
            SDL_BlitSurface(menus[i],NULL,windowSurface,&pos[i]);
        }

    }

    //Liberar
    SDL_FreeSurface(fondo);
    SDL_DestroyWindow(window);
    for(int i=0; i<NUMMENU; i++){
        SDL_FreeSurface(menus[i]);
    }
    //Liberar todo
    fondo = nullptr;
    window = nullptr;

    SDL_Quit();

    return 0;
}

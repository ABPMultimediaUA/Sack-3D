#ifndef DISPLAY_H
#define DISPLAY_H


#include<SDL.h>
#include <SDL_image.h>

#include <string>
#include "camera.h"
#include "../include/tnodo.h"
#include "MyEventReceiver.h"



class Display
{
    public:
        Display(int width, int height, const std::string& title);

        void Clear(float r, float g, float b, float a);
        //void Update(Camera& camera);
        int Update(TNodo* TfCamera);

        bool IsClosed();

        SDL_Texture* CreaTextura(const std::string &archivo);
        void RenderTextura(SDL_Texture *tex, int x, int y);
        SDL_Window* getWindow(){return m_window;}
        SDL_Renderer* getRenderer(){return ren;}
        virtual ~Display();

    protected:
    private:

        Display(const Display& other){}
        Display& operator=(const Display& other){}
        MyEventReceiver* myEventReceiver;
        SDL_Window* m_window;
        SDL_Surface *windowSurface;
        SDL_Surface *fondo;
        SDL_Renderer *ren;
        SDL_GLContext m_glContext;
        bool m_isClosed;
        int malla;

};

#endif // DISPLAY_H

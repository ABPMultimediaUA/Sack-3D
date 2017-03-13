#ifndef DISPLAY_H
#define DISPLAY_H


#include<SDL.h>
#include <string>
#include "camera.h"
#include "tnodo.h"


class Display
{
    public:
        Display(int width, int height, const std::string& title);

        void Clear(float r, float g, float b, float a);
        //void Update(Camera& camera);
        int Update(TNodo* TfCamera);

        bool IsClosed();

        virtual ~Display();

    protected:
    private:

        Display(const Display& other){}
        Display& operator=(const Display& other){}

        SDL_Window* m_window;
        SDL_GLContext m_glContext;
        bool m_isClosed;
          int malla;

};

#endif // DISPLAY_H

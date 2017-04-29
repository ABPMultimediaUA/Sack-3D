#ifndef TEXTURE_H
#define TEXTURE_H

#ifndef GLEW_STATIC
#define GLEW_STATIC
#include <GL/glew.h>
#endif

#include <string.h>
#include<iostream>
#include "trecurso.h"
class Texture : public TRecurso
{
    public:
        Texture( const std::string& fileName);
        ~Texture();
        void Bind(unsigned int unit);


         char* GetNombre();
         void setNombre( char* name);
         void setTipo(int tipo);
         int GetTipo();

    protected:

    private:

        Texture(const Texture& other){}
        Texture& operator=(const Texture& other){}
        char* nombre;
        int type;
        GLuint m_texture;


};

#endif // TEXTURE_H

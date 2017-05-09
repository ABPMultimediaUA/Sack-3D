#include "../include/texture.h"
#include "../include/stb_image.h"
//#include "SDL_image.h"

#include <cassert>


Texture::Texture(const std::string& fileName)
{
  /*   int width, height, numComponents;

  //  unsigned char* imageData   = IMG_Load(fileName.c_str(), &width, &height, &numComponents, 4);

    SDL_Surface* imageData   = IMG_Load(fileName.c_str());



    if( imageData == NULL){
        std::cerr<<"Fallo al cargar la textura: "<<fileName<<std::endl;
    }
     width = imageData->w;
    height = imageData->h;
    glGenTextures(1,&m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE,imageData->pixels);
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE,);
              std::cout<<"Fallo al cargar la textura: "<<std::endl;

    SDL_FreeSurface(imageData);*/

     int width, height, numComponents;

    unsigned char* imageData   = stbi_load(fileName.c_str(), &width, &height, &numComponents, STBI_rgb_alpha);

    if( imageData == NULL){
        std::cerr<<"Fallo al cargar la textura: "<<fileName<<std::endl;
    }
    glGenTextures(1,&m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

    stbi_image_free(imageData);

}

Texture::~Texture()
{
    glDeleteTextures(1,&m_texture);
}

void Texture::Bind(unsigned int unit){

    assert(unit >= 0 && unit <= 31);

    glActiveTexture(GL_TEXTURE0+unit);
    glBindTexture(GL_TEXTURE_2D, m_texture);
   // glDisable(GL_TEXTURE0+unit);
}


char* Texture::GetNombre(){
        return nombre;
 }
int Texture::GetTipo(){

        return type;
 }
void  Texture::setNombre( char* name){
    nombre= name;
}void  Texture::setTipo(int tipo){
    type= tipo;
}

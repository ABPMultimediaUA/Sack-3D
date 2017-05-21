#include "Spawner.h"
#include "Usable.h"
#include "SDL.h"

#define TIME2DESTROY 3000

Usable::Usable(PhysicBody* physicBody ,Spawner* expo, b2Vec2 pos, glm::vec3 tam, char *model, char *texture, int id)
:Cogible(physicBody,expo,pos,tam,model,texture, id){
    timeCadencia = 0;
    usando = false;
    usos = 1;
    cadencia = 500;
    killCountDown = false;
}
Usable::~Usable(){}
void Usable::usar(){}
void Usable::actualiza(){
    Cogible::actualiza();
    if(!usos)CompruebaVida();
}
void Usable::CompruebaVida(){
    if(!cogido){
        if(!killCountDown){
            time2Kill = SDL_GetTicks();
            killCountDown = true;
        }
        else if(SDL_GetTicks()-time2Kill>TIME2DESTROY){
            autoDestruir = true;
        }
    }
}
int  Usable::getUsos(){return usos;}

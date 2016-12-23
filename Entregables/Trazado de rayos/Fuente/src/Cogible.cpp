#include "Cogible.h"

Cogible::Cogible()
{
    cogido = false;
}

void Cogible::setCogido(bool aux){cogido = aux;}
bool Cogible::getCogido(){return cogido;}
int Cogible::getValoacion(){return valoracion;}
b2Body* Cogible::getBody(){}
Cogible::~Cogible()
{

}

#include "Cogible.h"

Cogible::Cogible()
{
    cogido = false;
    dir = 1;
}

void Cogible::setCogido(bool aux){cogido = aux;}
void Cogible::setDireccion(int d){if(d != 0) dir = d;}
bool Cogible::getCogido(){return cogido;}
b2Body* Cogible::getBody(){}
Cogible::~Cogible()
{

}

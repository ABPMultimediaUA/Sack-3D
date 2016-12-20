#include "Cogible.h"

Cogible::Cogible()
{
    cogido = false;
}

void Cogible::setCogido(bool aux){cogido = aux;}
bool Cogible::getCogido(){return cogido;}
b2Body* Cogible::getBody(){}
Cogible::~Cogible()
{

}

#include "Cogible.h"

Cogible::Cogible()
{
    cogido = false;
}

void Cogible::setCogido(bool aux){cogido = aux;}
bool Cogible::getCogido(){return cogido;}

Cogible::~Cogible()
{

}

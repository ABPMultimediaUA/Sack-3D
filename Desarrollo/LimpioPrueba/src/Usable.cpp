#include "Usable.h"

Usable::Usable()
{
    //ctor
    expuesto = true;
	expuesto = false;
}
void Usable::usar(){};
void Usable::setExpuesto(bool aux){expuesto = aux;}
bool Usable::getExpuesto(){return expuesto;}

Usable::~Usable()
{
    //dtor
}

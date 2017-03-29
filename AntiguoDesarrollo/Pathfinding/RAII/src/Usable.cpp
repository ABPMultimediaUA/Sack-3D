#include "Usable.h"

Usable::Usable(b2Vec2 pos):Cogible(pos){}
Usable::~Usable(){}
void Usable::usar(){};
void Usable::setExpuesto(bool aux){expuesto = aux;}
bool Usable::getExpuesto(){return expuesto;}


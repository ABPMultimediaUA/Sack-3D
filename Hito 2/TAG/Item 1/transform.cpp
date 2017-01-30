#include "transform.h"

Transform::Transform()
{
    //ctor
}

Transform::~Transform()
{
    //dtor
}

Transform::Transform(const Transform& other)
{
    //copy ctor
}

Transform& Transform::operator=(const Transform& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}

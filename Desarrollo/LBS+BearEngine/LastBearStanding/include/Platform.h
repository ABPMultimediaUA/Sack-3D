
#ifndef PLATFORM_H
#define PLATFORM_H

#include "GameObject.h"

class Platform{
    public:
        Platform(bool mata, b2Vec2 pos, glm::vec3 tam, char *texture);
        ~Platform();
        int GetId();
    private:
        GameObject m_gameObject;
        int m_id;
};

#endif

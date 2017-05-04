
#ifndef MUELLE_H
#define MUELLE_H

#include "GameObject.h"

class Muelle{
    public:
        Muelle(float f , b2Vec2 pos, glm::vec3 tam = glm::vec3(1.5f, 0.5f, 1.5f)); 	///< Constructor
        ~Muelle();
        float getFuerza();
        int GetId();
    private:
        GameObject m_gameObject;
	    float m_fuerza;
        int m_id;
};
#endif

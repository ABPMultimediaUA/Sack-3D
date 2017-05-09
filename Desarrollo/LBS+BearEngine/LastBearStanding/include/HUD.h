#ifndef HUD_H
#define HUD_H

#include "GameObject.h"
class HUD{
    public:
        HUD();
        ~HUD(){}
        Inicialize(int *puntuaciones);
        void Update(glm::vec3 pos);

    private:
        GameObject m_red,
                   m_green,
                   m_yellow,
                   m_pink;
};

#endif

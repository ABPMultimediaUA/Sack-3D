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
        char *contadores[6] = {
              {   "media/Images/Hud/0.png" }
            , {   "media/Images/Hud/1.png" }
            , {  "media/Images/Hud/2.png"  }
            , {   "media/Images/Hud/3.png" }
            , {  "media/Images/Hud/4.png"  }
            , {  "media/Images/Hud/5.png"  }
        };
        GameObject m_red,
                   m_green,
                   m_yellow,
                   m_pink,
                   m_redPoints,
                   m_greenPoints,
                   m_yellowPoints,
                   m_pinkPoints;
};

#endif

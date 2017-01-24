/*******************************************************************************
Estudio Rorschach - Last Bear Standing
Copyright  2016. All Rights Reserved.

Project:       Last Bear Standing
File:          Pistola.h

Author:        Estudio Rorschach
Created:
Modified:      19/12/2016 Miguel Paniagua

Overview:
Clase que contiene el codigo de funcionamiento para la granada.
*******************************************************************************/
//---------------------------------------------------------------------------
#ifndef GRANADA_H
#define GRANADA_H
//---------------------------------------------------------------------------
#include <vector>
#include "Usable.h"

/******************************************************************************
                               Granada
*******************************************************************************/
class Granada:public Usable{
    public:
        Granada(int modelo,irr::core::vector3df pos);
        void actualiza();		      ///< actualiza la posicion y rotacion del Pistola
        void usar();                  ///< ejecuta el usar de la clase
        irr::f32 timergranada;  ///<
        irr::ITimer* timerIrr;             ///<
        void setCogido(bool aux);
        bool getCogida();
        b2Body* getBody();		      ///< Getter del body
        virtual ~Granada();
    private:
        std::vector<b2Body*>* particulas;
        int mecha;
        bool usada;
};

#endif // GRANADA_H

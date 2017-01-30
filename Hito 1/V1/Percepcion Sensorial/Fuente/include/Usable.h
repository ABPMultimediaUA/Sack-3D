/*******************************************************************************
Estudio Rorschach - Last Bear Standing
Copyright  2016. All Rights Reserved.

Project:       Last Bear Standing
File:          Usable.h

Author:        Estudio Rorschach 
Created:       11/11/2016 Jorge Puerto
Modified:      08/12/2016 Jorge Puerto

Overview:
Clase que hereda de cogible e implementa lo necesario para que un 
objeto se pueda usar, es decir el player sea capaz de realizar una accion
con el. 
*******************************************************************************/
//---------------------------------------------------------------------------
#ifndef USABLE_H
#define USABLE_H

#include "Cogible.h"

/******************************************************************************
                               Usable
*******************************************************************************/
class Usable : public Cogible{
    public:
        Usable();                                 ///< Constructor      
        void setExpuesto(bool aux);               ///< Setter                                          
        bool getExpuesto();                       ///< Getter                                  
        /*                                                          
        Spawner* getExpositor();                                                            
        virtual void usar(sf::Event::EventType);                                                            
        */                                                          
        virtual ~Usable();                        ///< Destructor                                  
                                                            
    protected:                                                          
        /*                                                          
        Spawner* expositor;                                                         
        */                                                          
    	bool expuesto;                            ///< Esta en modo exposicion?                             
        bool usando;                              ///< Esta siendo usado?                               

    private:
};

#endif // USABLE_H

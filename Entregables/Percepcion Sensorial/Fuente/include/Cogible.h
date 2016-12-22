/*******************************************************************************
Estudio Rorschach - Last Bear Standing
Copyright  2016. All Rights Reserved.

Project:       Last Bear Standing
File:          Cogible.h

Author:        Estudio Rorschach 
Created:       
Modified:      08/12/2016 Jorge Puerto

Overview:
Clase que define lo minimo para que un objeto que se pueda coger, heredaran de 
esta todos los objetos que se puedan coger y ademas tengan funcionalidades propias.
*******************************************************************************/
//---------------------------------------------------------------------------

#ifndef COGIBLE_H
#define COGIBLE_H
//---------------------------------------------------------------------------

#include <Box2D/Box2D.h>
#include <irrlicht.h>


/******************************************************************************
                               Cogible
*******************************************************************************/
class Cogible{
    public:
        Cogible();                      ///< Constructor
        /*
        void actualiza();
        bool getADestruir();
        bool getDespawnear();
        virtual void muellazo(int fuerza);
        */
        b2Body* getBody();
        bool getCogido();
        void setCogido(bool aux);
        virtual ~Cogible();             ///< Destructor

    protected:
        /*
        IMeshSceneNode* node;
	    b2Body* body;
	    */
        bool cogido;                    ///< Booleano para saber si esta siendo cogido
        /*
        bool aDestruir;
        bool humo;
    	bool despawnear;
        */
    private:
};

#endif // COGIBLE_H

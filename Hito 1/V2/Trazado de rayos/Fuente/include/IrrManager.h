/*******************************************************************************
Estudio Rorschach - Last Bear Standing
Copyright  2016. All Rights Reserved.

Project:       Last Bear Standing
File:          IrrManager.h

Author:        Estudio Rorschach 
Created:       11/11/2016 Jorge Puerto
Modified:      08/12/2016 Jorge Puerto

Overview:
Clase que controla todo lo relacionado con en mundo tridimensional, la pantalla
temporizadores, entorno, graficos... 

ToDo:
Hay mucho que aprender sobre esta gran mierda llamada irrlicht
*******************************************************************************/
//---------------------------------------------------------------------------
#ifndef IRRMANAGER_H
#define IRRMANAGER_H
//---------------------------------------------------------------------------
#include <irrlicht.h>
#include "MyEventReceiver.h"


using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;


/******************************************************************************
                               IrrManager
*******************************************************************************/
class IrrManager{
    public:
        static IrrManager* Instance();             ///< Devuelve la unica instancia de la clase
        IrrManager();                              ///< Constructor
        void drawAll();                            ///< Dibuja el mundo
        void beginScene();                         ///< ???
        void endScene();                           ///< ???
        void drop();                               ///< ???                                                 
        float getTime();                           ///< ???                                      
        // Genera una maya rectangular pasando posicion, tamaño y color                      
        IMesh* createCubeMesh(vector3df pos, vector3df tam,  SColor color);
        // Genera una nodo cubico pasando tamaño y color                      
        IMeshSceneNode* addCubeSceneNode(int tam , SColor color);
        // Genera una nodo rectangular pasando tamaño y color                      
        IMeshSceneNode* addCubeSceneNode(vector3df tam, SColor color);
        IXMLReader* createXMLReader(stringw file);  ///< Crea un lector de xml    
        ISceneManager* getManager();                ///< Getter                                               
        MyEventReceiver* getEventReciever();        ///< Getter                                                       
        IrrlichtDevice* getDevice();                ///< Getter                                               
        IVideoDriver* getDriver();                  ///< Getter                                           
        IGUIEnvironment* getGUI();                  ///< Getter                                           
        ITimer* getTimer();                         ///< Getter                                   
        virtual ~IrrManager();                      ///< Destructor                                       

    private:
    static IrrManager* pinstance;                   ///< Unica instancia de la clase
    ISceneManager* smgr;                            ///< Manejador de la escena                        
    IrrlichtDevice* device;                         ///< Controlador de la pantalla                        
    MyEventReceiver* receiver;                      ///< Controlador de los eventos                             
    IVideoDriver* driver;                           ///< Controlador de la grafica                        
    ITimer* timer;                                  ///< Controla el tiempo del bucle
    IGUIEnvironment* guienv;                        ///< ???                                                 
};

#endif // IRRMANAGER_H

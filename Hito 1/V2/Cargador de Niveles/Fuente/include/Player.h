/*******************************************************************************
Estudio Rorschach - Last Bear Standing
Copyright  2016. All Rights Reserved.

Project:       Last Bear Standing
File:          Player.h

Author:        Estudio Rorschach 
Created:       11/11/2016 Jorge Puerto
Modified:      08/12/2016 Jorge Puerto

Overview:
Clase que define un player
*******************************************************************************/
//---------------------------------------------------------------------------
#ifndef PLAYER_H
#define PLAYER_H
//---------------------------------------------------------------------------
#include <Box2D/Box2D.h>
#include <irrlicht.h>
#include "MyEventReceiver.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

/******************************************************************************
                               Player
*******************************************************************************/
class Player{
    public:
        Player(vector3df pos);                   ///< Constructor                  
        void update();                           ///< Actualizar                      
        void mover();                            ///< Mover                   
        void saltar();                           ///< Saltar                  
        void fingirMuerte();                     ///< Hacerse el muerto                            
        void crearJoint(b2Body*, b2Body*);       ///< ???                                          
        void romperJoint();                      ///< ???                     
        vector3df getPosition();                 ///< Getter                                
        bool getSaltando();                      ///< Getter                        
        bool getDobleSaltando();                 ///< Getter                                
        bool getCogiendo();                      ///< Getter                        
        int getDireccion();                      ///< Getter                        
        bool getPuedoCoger();                    ///< Getter                            
        b2Body* getBody();                       ///< Getter                        
        void setSaltando(bool aux);              ///< Setter                                
        void setDobleSaltando(bool);             ///< Setter                                    
        void setCogiendo(bool aux);              ///< Setter                                
        void setPuedoCoger(bool aux);            ///< Setter                                    
        virtual ~Player();                       ///< Destructor                               

    protected:
        IMeshSceneNode* node;                    ///<                            
        b2Body* body;                            ///<                    
        b2PolygonShape* polyShape;               ///<                                
        b2Fixture* personFixture;                ///<                                
        b2RevoluteJoint* joint;                  ///<                            
        b2RevoluteJointDef* jointDef;            ///<                                    
        int x;                                   ///<            
        int y;                                   ///<            
        int vel;                                 ///<                
        int salto;                               ///<                
        bool cogiendo;                           ///<                    
        int direccion;                           ///<                    
        bool puedoCoger;                         ///<                        
        bool dobleSaltando;                      ///<                        
        bool fingiendoMuerte;                    ///<                            
        bool saltando;                           ///<                    
        vector3df tam;                           ///<                    
		MyEventReceiver* eventReceiver;          ///<                                      
    private:
};

#endif // PLAYER_H

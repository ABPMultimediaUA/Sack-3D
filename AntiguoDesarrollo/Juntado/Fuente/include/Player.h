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
#include "Cogible.h"

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
        void recibeImpulso(float fuerza);          ///< Recibe el impulso de un muelle
        void teletransportar();                  ///< Teletrasporta al player a la posicion nextPos
        void morir();                            ///< Muere :(
        void crearJoint();                       ///< ???
        void romperJoint();                      ///< ???
        void usar();
        vector3df getPosition();                 ///< Getter
        bool getSaltando();                      ///< Getter
        bool getDobleSaltando();                 ///< Getter
        bool getCogiendo();                      ///< Getter
        int getDireccion();                      ///< Getter
        bool getPuedoCoger();                    ///< Getter
        bool getMuerto();                        ///< Getter
        b2Body* getBody();                       ///< Getter
        Cogible* getObjCogido();                 ///< Getter
        Cogible* getObjPuedoCoger();             ///< Getter
        void setSaltando(bool aux);              ///< Setter
        void setDobleSaltando(bool);             ///< Setter
        void setCogiendo(bool aux);              ///< Setter
        void setPuedoCoger(bool aux);            ///< Setter
        void setObjCogido(Cogible* aux);         ///< Setter
        void setObjPuedoCoger(Cogible* aux);     ///< Setter
        void setNextPos(b2Vec2 pos);             ///< Setter
        void setParaMorir(bool aux);             ///< Setter
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
        float vel;                                 ///<
        float salto;                               ///<
        bool cogiendo;                           ///<
        int direccion;                           ///<
        bool puedoCoger;                         ///<
        bool dobleSaltando;                      ///<
        bool fingiendoMuerte;                    ///<
        bool saltando;                           ///<
        bool paraMorir;                          ///< Booleano que indica que debe morir
        bool muerto;                             ///< Booleano que indica que esta muerto
        b2Vec2 nextPos;                          ///< La posicion a la que debe teletransportarse la siguiente vez que se actualice
		bool teletransportado;                   ///< Booleano que indica que ha pisado un teletransporte
        Cogible* objCogido;                      ///<
        Cogible* objPuedoCoger;                  ///<
        vector3df tam;                           ///<
		MyEventReceiver* eventReceiver;          ///<
		b2Vec2 velActual;
    private:
};

#endif // PLAYER_H

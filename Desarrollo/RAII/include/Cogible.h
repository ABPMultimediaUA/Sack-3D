#ifndef COGIBLE_H
#define COGIBLE_H

#include <Box2D/Box2D.h>
#include <irrlicht.h>

#define RADTOGRAD 180 / 3.14159265          ///< Conversor de radianes a grados
#define CATCH     1                        ///< Int para las colisiones de las Pistolas
#define RELEASE   2                        ///< Int para las colisiones de las Pistolas
#define ARMA      30                        ///< Int para las colisiones de las Pistolas
#define SENSOR    35                        ///< Int para las colisiones del area cogible de las Pistolas
#define MPP       64
#define PPM       1/64


class Cogible{
    public:
        Cogible();
        virtual ~Cogible();
        virtual void DestroyFixtures();
        virtual void InicializeFixtures(int mode);
        virtual void actualiza();           ///< actualiza la posicion y rotacion del Pistola
        virtual void setDireccion(int);
        virtual b2Body* getBody();          ///< Getter del body
        virtual bool getCogido();
        virtual void setCogido(bool aux);
    protected:
        irr::scene::IMeshSceneNode* node;   ///< Nodo irrlicht para poder mover, dibujar, etc.
        b2Body* body;                       ///< Cuerpo fisico box2d para poder aplicar fisicas
        irr::core::vector3df tam;
        bool cogido = false;
        int dir = 1;
        float restitution = 1;
        float density = 1;
        float friction = 1;
};

#endif // COGIBLE_H

#ifndef DEFINES_H_INCLUDED
#define DEFINES_H_INCLUDED

//POSICIONES COGIBLE
#define CATCH            1                       
#define RELEASE          2                       
//POSICIONES PLAYER
#define LEVANTADO        1
#define MUERTO_DORMIDO   2
#define AGACHADO         3
//CONTACT LISTENER
#define PLAYER           10
#define PIESPLAYER       100
#define COGIBLE          30                      
#define SENSOR           35    
//PHYSICS
#define RADTOGRAD        180 / 3.14159265
#define VELITER 6              //NUMERO DE ITERACION POR TICK PARA CALCULAR LA VELOCIDAD
#define POSITER 2              //NUMERO DE ITERACIONES POR TICK PARA CALCULAR LA POSICION
#define TIMESTEP 1.0f / 250.0f  //TIEMPO DE REFRESCO
        
//GRANADA
#define PARTICULAS 10
//VECTORES
#define MAX_NUM_TELEPORT       10
#define MAX_NUM_PLAYER         4
#define MAX_NUM_PISTOLA        20
#define MAX_NUM_ESCOPETA       20
#define MAX_NUM_GRANADA        20
#define MAX_NUM_BALA           200
#define MAX_NUM_MUELLE         20
//MAPA
#define PLAYER       1
#define MUELLE       2
#define TELEPORT     3
#define PLATAFORMA   4
#define ARMA         5
#define PISTOLA      1
#define ESCOPETA     2
#define GRANADA      3

#endif // DEFINES_H_INCLUDED

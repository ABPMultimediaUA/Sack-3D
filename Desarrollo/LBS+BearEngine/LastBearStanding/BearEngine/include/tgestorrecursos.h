#ifndef TGESTORRECURSOS_H
#define TGESTORRECURSOS_H

#include "trecurso.h"
#include <vector>

class TGestorRecursos
{
    public:
        TGestorRecursos();
        virtual ~TGestorRecursos();
        TRecurso * getRecurso( char * nombre, int tipo);
        void almacenarRecurso(TRecurso* recur);
        void borrarRecurso(char * nombre);
        void verRecursos();
    protected:

    private:

        std::vector<TRecurso*> recursos;


};

#endif // TGESTORRECURSOS_H

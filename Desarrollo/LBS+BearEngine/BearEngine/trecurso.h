#ifndef TRECURSO_H
#define TRECURSO_H


class TRecurso
{
    public:

        virtual ~TRecurso(){};
        virtual char* GetNombre() = 0;
        virtual void setNombre( char* name)=0;
        virtual void setTipo(int tipo)=0;
        virtual int GetTipo()=0;
    protected:
        char* nombre;
        int type;
    private:
};

#endif // TRECURSO_H

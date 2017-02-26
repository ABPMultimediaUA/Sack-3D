#ifndef TENTIDAD_H
#define TENTIDAD_H


 class TEntidad
{
    public:
        virtual ~TEntidad(){}
        virtual void begingDraw() =0;
        virtual void endDraw()  =0;
        virtual int getTipo()=0;
};

#endif // TENTIDAD_H

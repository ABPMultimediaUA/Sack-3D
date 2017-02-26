*************************************************************************************
*************************************************************************************
*************************************************************************************
*********************											*********************
*********************	"Guia"	del código del arbol de escena	*********************
*********************											*********************
*************************************************************************************
*************************************************************************************
*************************************************************************************

AVISO: De momento el arbol está implementado una camara y una malla.

Para el funcionamiento del arbol de escena es necesario dos clases, la clase Nodo y la clase TEntidad, la clase Nodo se usa para la formación del arbol y contiene lo siguiente:

    public:
        Nodo(int raiz); Constructor se le pasa 1 si va a ser la raiz y 0 si no
        virtual ~Nodo();
        int addHijo(Nodo* hijo); -> Añadimos un hijo al nodo para eso se le pasa un puntero al nodo hijo y se añade al final del vector de hijos
        int remHijo(Nodo* hijo); -> Para borrar un hijo pasando un puntero al Nodo hijo se busca con un bucle el hijo que se le pasa por parametro (Ineficaz seguramente)
        bool seTEntidad(TEntidad* entidadN); -> Le asignamos una entidad al nodo (Malla, Camara, Transformacion, etc) la raiz no tiene entidad, de ello el constructor con el int
        TEntidad *getEntidad(); -> Devuelve la entidad si tiene
        int conPadre(); -> Te dice si el nodo tiene padre (los nodos se crean sin padre y se les da uno al añadirlos al arbol a posteriori)
        Nodo* getPadre(); -> Te da al padre 
        void draw(Shader* shad, Camera* cam, Transform* trans); -> Metodo de dibujado con el que llamamos a la raiz y esta se encarga de dibujar todo el arbol, seguramente haya que cambiarlo todo, en la llamada le pasamos el shader a usar, un puntero a la camara, Si es la llamada a la raiz la camara va a null y dentro del arbol obtendría el valor que corresponda de ahi lo de puntero, una transformacion( es transformacion porque aun no esta implementado las transformaciones en el arbol, habra que cambiarlo por una matriz de 4x4 la cual se pasa en un principio como entidad y va cambiando en el recorrido del arbol)
        Aqui es donde se llama al shader.Update() para multiplicar la transformacion con la camara y pasarle la matriz resultante al shader para que dibuje el objeto en la posicion que le corresponde. (Recomiendo ver la implementacion en nodo.cpp)
        void setPadre(Nodo* padreN); -> asignamos un padre a un nodo
        int numeroHijos(); -> numero de hijos que tiene un nodo
        void setRaiz(int i); -> dar o quitar la propiedad de ser raiz
    protected:

    private:
        TEntidad * entidad; 
        std::vector <Nodo*> hijos; -> Vector de hijos
        Nodo* padre; 
        int tienePadre;
        int esRaiz;

Sobre la clase TEntidad, TEntidad es una clase abstracta cuyos metodos son implementados en las clases que la heredan, como son Camara, Malla, Transformacion(Aun no), etc. Los metodos que contiene son los siguientes:

   virtual ~TEntidad(){}
        virtual void begingDraw() =0; ->Empieza el proceso de dibujado, cada clase que lo implementa hace algo distinto, en la clase camara esta vacio, en la clase malla se llama al this->draw(), para dibujar la malla
        virtual void endDraw()  =0; -> Termina el proceso de dibujado, en Camara y Malla no hace nada, sirve para desapilar la matriz en Transformacion
        virtual int getTipo()=0; -> Devuelve el tipo del que es la entidad, para poder identificarlas, está implementa igual en todas las derivadas, "return tipo " 0 Malla, 1 Transformacion, 2 Camara, 3 Luz
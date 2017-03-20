#include "tmotorbear.h"

TMotorBear::TMotorBear(int width, int height, const std::string& title)
{
    arbolEscena = new TNodo(1);
    gestorRecursos= new TGestorRecursos();
    camaraActiva = nullptr;
    escena = new Display(width,height,title);
    pila = new std::vector<glm::mat4>;
}

TMotorBear::~TMotorBear()
{
    delete(arbolEscena);
    delete(gestorRecursos);
    delete(escena);
    delete(pila);
    /*for(int i=0;registroCamara.size();i++){ PETA
        delete(registroCamara[i]);
        i--;
    }*/
}

TNodo* TMotorBear::getRaiz(){
    return arbolEscena;
}

TNodo* TMotorBear::crearNodo(TNodo* padre, TEntidad * ent, char* nom){
    TNodo* devolv = new TNodo(0);
    devolv->setNombreEntidad(nom);
    devolv->setEntidad(ent);
    devolv->setPadre(padre);
    padre->addHijo(devolv);


    return devolv;
}

//TTransform * TMotorBear::crearTransform(){
TEntidad * TMotorBear::crearTransform(){
    TTransform *trans = new TTransform();
    return trans;

}
void TMotorBear::transformarEntidad(TEntidad* entity, float tipo, glm::vec3 vec){ //0 = traslacion != 0 rotacion
    TTransform* trans = static_cast<TTransform*>(entity);

    if(!tipo){
        trans->trasladar(vec);
    }
    else{trans->rotar(tipo,vec);
    }
}


//Camera * TMotorBear::crearCamara(const glm::vec3 pos, float fov, float aspect, float zNear, float zFar){
TEntidad * TMotorBear::crearCamara(const glm::vec3 pos, float fov, float aspect, float zNear, float zFar){
    Camera* camera= new Camera( pos,  fov,  aspect,  zNear,  zFar);
    return camera;
}
//TEntidadMalla* TMotorBear::crearMalla( char* file){
TEntidad* TMotorBear::crearMalla( char* file){
    TEntidadMalla* mesh = new TEntidadMalla();
    mesh->setMalla(static_cast<Mesh*> (gestorRecursos->getRecurso(file, 0)));
    return mesh ;
}
TEntidad* TMotorBear::crearMalla( float alto, float ancho, float prof){
    TEntidadMalla* mesh = new TEntidadMalla();
    mesh->setMalla( new Mesh(ancho, alto, prof));
    return mesh ;
}

TNodo* TMotorBear::crearCuboEn(float alto, float ancho, float prof, glm::vec3 vec){

    TNodo* nodoTrans1 = crearNodo(arbolEscena,crearTransform(), "rot");
    TTransform* desp = static_cast<TTransform* > (crearTransform());
    desp->trasladar(vec);
    TNodo* nodoTrans2 = crearNodo(arbolEscena,desp, "rot");
    TNodo* nodoMalla6 = crearNodo(nodoTrans2,crearMalla(alto,ancho,prof),"malla");

return nodoMalla6;
}



void TMotorBear::cambiarMalla(TEntidad* mesh, char* file){
    if( file){
       static_cast<TEntidadMalla*> (mesh)->setMalla(static_cast<Mesh*> (gestorRecursos->getRecurso(file, 0)));
    }else{
       static_cast<TEntidadMalla*> (mesh)->setMalla(0);
    }

}

void TMotorBear::transformarMalla(TNodo* nodoMalla, float tipo, glm::vec3 vec){    //necesario que el nodo arbol este ya incorporado al arbol
    TNodo* padre = nodoMalla->getPadre();
        if(tipo){
            padre= padre->getPadre();
        }
    transformarEntidad(padre->getEntidad(),tipo,vec);

}
void TMotorBear::borrarMalla(char * nombre){
    gestorRecursos->borrarRecurso(nombre);
}

void TMotorBear::registrarCamara(TNodo* camera){
   // std::cout<<"Entra registro camara"<<std::endl;


    registroCamara.push_back(camera);
      //  std::cout<<"Sale registro camara"<<std::endl;
}
TNodo* TMotorBear::verCamaraActiva(){
       // std::cout<<"Entra ver camara activa"<<std::endl;
    TNodo * nodoCam;
    Camera * cam;
    for(int i=0; i<registroCamara.size();i++){
         nodoCam= registroCamara[i];
        cam=static_cast<Camera*> (nodoCam->getEntidad());
        if(cam->verActivadoCamara()){
         //       std::cout<<"Hay una camara Activa"<<std::endl;

            return nodoCam;

        }
       // delete(cam);
    }

           //         std::cout<<"No hay una camara Activa"<<std::endl;
    return 0;
}
void TMotorBear::activarCamara(TNodo* cam){
    camaraActiva= verCamaraActiva();
    //Camera* camarita;
    if(camaraActiva){
     //   camarita = static_cast <Camera*>( camActiva->getEntidad());
     static_cast <Camera*>( camaraActiva->getEntidad())->desactivarCamara();

    //    camarita->desactivarCamara();
        //std::cout<<"Camara Desactivada"<<std::endl;
    }
    static_cast <Camera*>( cam->getEntidad())->activarCamara();
   // camarita->activarCamara();
   // std::cout<<"Camara Activada"<<std::endl;

}
glm::mat4 TMotorBear::obtenerMatCam(){
    TNodo* nodo = verCamaraActiva();
    int cont=0;
    glm::mat4 mat =glm::mat4();
    std::vector<glm::mat4> mats;

    while(nodo!=arbolEscena){
    //    std::cout<<nodo->getNombreEntidad()<<std::endl;
     //   std::cout<<nodo->getPadre()->getNombreEntidad()<<std::endl;

       // if(!cont){
           //mats.insert(mats.begin(),static_cast<Camera*> (nodo->getEntidad())->GetViewProjection());
         //  mats.insert(mats.begin(),glm::mat4());

        //mats.insert(mats.begin(), glm::inverse(glm::mat4()));
   //         std::cout<<"CAMARA"<<std::endl;

        if(cont){
            mats.insert(mats.begin(),static_cast<TTransform*> (nodo->getEntidad())->GetModel());
     //       std::cout<<"TRANSFORMACION"<<std::endl;
        }else{
           mats.insert(mats.begin(),glm::inverse(static_cast<Camera*> (nodo->getEntidad())->getPers()));
        }
         nodo=nodo->getPadre();
        cont++;
    }
    //std::cout<<"Fuera While"<<std::endl;
    for(int i=0; i<mats.size();i++){
            //if(i==mats.size()-i){
               // mat = glm::vec3(0,0,0)  mat;
              //  mat = glm::dot(glm::vec3(0,0,0),mat);
           // }else{
        mat=mat*mats[i];
        //}

    }


   // mat = glm::inverse(mat) * static_cast<Camera*> (nodo->getEntidad())->miraA(glm::vec3(0,0,0),glm::vec3(0,0,-1),glm::vec3(0,1,0));
   glm::vec3 transformed = glm::vec3(mats[mats.size()-1] * glm::vec4(glm::vec3(0,0,0), 1.0));
    mat = glm::inverse(mat) * static_cast<Camera*> (nodo->getEntidad())->miraA(transformed,glm::vec3(0,0,-1),glm::vec3(0,1,0));

      /*for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            std::cout<<mat[i][j]<<" ";
        }
        std::cout<<std::endl;

    }
    std::cout<<std::endl;*/
//mat = mat * glm::inverse(glm::mat4());
/*
   glm::vec3 pos =glm::vec3(mat * glm::vec4(glm::vec3(0,0,0), 1.0));

    for(int i =0; i<3;i++){
        std::cout<<pos[i]<<",";
    }
    std::cout<<std::endl;
*/
    return mat;
}


void TMotorBear::draw(Shader* shad){
    glm::mat4 cam = obtenerMatCam(); //Camara
  /*  for(int i =0; i<4;i++){
        for(int j=0;j<4;j++){
            std::cout<<cam[i][j];
        }std::cout<<std::endl;
    }std::cout<<std::endl;*/
   //luces
   //Viewport
   pila->push_back(cam);
    arbolEscena->draw(shad,pila);
    pila->pop_back();
}


//TLuz* TMotorBear::crearLuz(glm::vec3 colorLuz){
TEntidad* TMotorBear::crearLuz(glm::vec3 colorLuz){
    TLuz* luz= new TLuz();
    luz->setIntensidad(colorLuz);
    return luz;
}
void TMotorBear::cambiarLuz(TLuz* luz, glm::vec3 colorLuz){
    luz->setIntensidad(colorLuz);
}
void TMotorBear::registrarLuz(TNodo* luz){
    registroLuces.push_back(luz);
}

glm::vec3 TMotorBear::InteLuz(int posicion){
    glm::vec3 luz;
        luz = static_cast<TLuz*>(registroLuces[posicion]->getEntidad())->getIntensidad();
    return luz;
}
void TMotorBear::activarLuces(){
    for(int i =0; i<registroLuces.size();i++){
        activaLuz(i); //Devuelve posicion de luz habria que pasarla al shader para colocarla junto con la intensida
    }
}

void TMotorBear::activaLuz(int numero){ //QUE NO SE TE OLVIDE IMPLEMENTAR ESTO JOPUTA
    //LLamadas a shaderç
    TNodo* nodo = registroLuces[numero];
    glm::mat4 mat =glm::mat4();
    std::vector<glm::mat4> mats;
    glm::vec3 posLuz = glm::vec3();
    int cont=0;
    while(nodo!=arbolEscena){

    if(cont){
            mats.insert(mats.begin(),static_cast<TTransform*> (nodo->getEntidad())->GetModel());
     //       std::cout<<"TRANSFORMACION"<<std::endl;
        }else{
           //mats.insert(mats.begin(),glm::inverse(static_cast<Camera*> (nodo->getEntidad())->getPers()));
           mats.insert(mats.begin(), glm::mat4());
        }

    nodo= nodo->getPadre();
    cont++;
    }

    for(int i=0; i<mats.size();i++){
        mat=mat*mats[i];
    }

    posLuz = glm::vec3(mat * glm::vec4(glm::vec3(0,0,0), 1.0));

   // return posLuz;
}

//Display
bool TMotorBear::IsClosed(){
    return escena->IsClosed();
}
void TMotorBear::Clear(float r, float g, float b, float a){
    escena->Clear(r,g,b,a);
}
//void TMotorBear::UpdateDisplay(){
int TMotorBear::UpdateDisplay(){
  return  escena->Update(verCamaraActiva());
}

// TNodo* verCamaraActiva();
//void TMotorBear::activarLuz(TLuz* luz){}

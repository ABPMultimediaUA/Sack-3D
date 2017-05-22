#include "../include/tmotorbear.h"

#include <stdio.h>
#include <string.h>
#ifndef _CONCAT
#define _CONCAT
char* Concat(char* base, char* anya){
     char * dev = (char *) malloc(1 + strlen(base)+ strlen(anya) );
      strcpy(dev, base);
      strcat(dev, anya);
      return dev;
}
#endif // _CONCAT
TMotorBear::TMotorBear(int width, int height, const std::string& title)
{
    arbolEscena = new TNodo(1);
    arbolEscena->setNombreEntidad("RAIZ");
    gestorRecursos= new TGestorRecursos();
    camaraActiva = NULL;
    escena = new Display(width,height,title);
    pila = new std::vector<glm::mat4>;
    crearShadersBasicos();

}
void TMotorBear::verArbol(){
    arbolEscena->verArbol();
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

void TMotorBear::crearShader(const std::string& fileName){
    Shader * shad = new Shader(fileName);
    shadersMot.push_back(shad);
}

void TMotorBear::crearShadersBasicos(){
    crearShader("BearEngine/res//basicShader");
    std::cout<<"BasicShader"<<std::endl;
    crearShader("BearEngine/res//basicShaderLuz");
    std::cout<<"BasicShaderLuz"<<std::endl;
    crearShader("BearEngine/res//CelShader");
    std::cout<<"CelShader"<<std::endl;
}


int TMotorBear::getShaderProgram(int posVec){
    return  shadersMot.at(posVec)->positionLocation();
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
TNodo* TMotorBear::obtenerPadreCamara(){

return verCamaraActiva()->getPadre();
}

/*
void TMotorBear::transformarEntidad(TEntidad* entity, float tipo, glm::vec3 vec){ //0 = traslacion != 0 rotacion
    TTransform* trans = static_cast<TTransform*>(entity);

    if(!tipo){
        trans->trasladar(vec);
    }
    else{trans->rotar(tipo,vec);
    }
}
*//*
void TMotorBear::escalarEntidad(TEntidad* entity, glm::vec3 vec){

     TTransform* trans = static_cast<TTransform*>(entity);
     trans->escalar(vec);
}
*/

void TMotorBear::asignarMaterial(TNodo* nodoMalla, char* nombreMat){
    TEntidadMalla* ent = static_cast<TEntidadMalla*> (nodoMalla->getEntidad());
    ent->asignarMat(static_cast<TMaterial*> (gestorRecursos->getRecurso(nombreMat,2)));
}

void TMotorBear::materialesColoresBasicos(){
    /*TMaterial* blanco   = new TMaterial(glm::vec3(1.0,1.0,1.0), "Blanco");
    TMaterial* rojo     = new TMaterial(glm::vec3(1.0,0.0,0.0), "Rojo");
    TMaterial* verde    = new TMaterial(glm::vec3(0.0,1.0,0.0), "Verde");
    TMaterial* rosa     = new TMaterial(glm::vec3(0.9,0.11,0.88), "Rosa");
    TMaterial* amarillo = new TMaterial(glm::vec3(1.0,1.0,0.0), "Amarillo");

    gestorRecursos->almacenarRecurso(blanco);
    gestorRecursos->almacenarRecurso(rojo);
    gestorRecursos->almacenarRecurso(verde);
    gestorRecursos->almacenarRecurso(rosa);
    gestorRecursos->almacenarRecurso(amarillo);*/
}


void TMotorBear::cambiarColorLuz(glm::vec3 colr){
    TLuz* luz = static_cast<TLuz*> (registroLuces.at(0)->getEntidad());
    luz->setIntensidad(colr);
}

void TMotorBear::cambiarPosiLuz(glm::vec3 pos){
    TLuz* luz = static_cast<TLuz*> (registroLuces.at(0)->getEntidad());
    luz->setPosicion(pos.x,pos.y,pos.z);
}

//Camera * TMotorBear::crearCamara(const glm::vec3 pos, float fov, float aspect, float zNear, float zFar){
TEntidad * TMotorBear::crearCamara(const glm::vec3 pos, float fov, float aspect, float zNear, float zFar){
    Camera* camera= new Camera( pos,  fov,  aspect,  zNear,  zFar);
//    std::cout<<"AAA"<<std::endl;
    crearObjetoLuz(arbolEscena,glm::vec3(1.0f,1.0f,1.0f), glm::vec3(0,0,10),"lightUno", 1);
    //std::cout<<"BB"<<std::endl;
    return camera;
}
//TEntidadMalla* TMotorBear::crearMalla( char* file){
TEntidad* TMotorBear::crearMalla( char* file,int idS){

    TEntidadMalla* mesh = new TEntidadMalla(shadersMot.at(idS));

    mesh->setMalla(static_cast<Mesh*> (gestorRecursos->getRecurso(file, 0)));

    return mesh ;
}
TEntidad* TMotorBear::crearMalla( float alto, float ancho, float prof){
 /*   TEntidadMalla* mesh = new TEntidadMalla();
    mesh->setMalla( new Mesh(ancho, alto, prof));
    return mesh ;*/
}
void TMotorBear::AsignarMallaANodo(TNodo* nodo, char*file){
    cambiarMalla(nodo->getEntidad(),file);
}
TNodo* TMotorBear::crearCuboEn(float alto, float ancho, float prof, glm::vec3 vec){

    TNodo* nodoTrans1 = crearNodo(arbolEscena,crearTransform(), "rot");
    TTransform* desp = static_cast<TTransform* > (crearTransform());
    desp->trasladar(vec);
    TNodo* nodoTrans2 = crearNodo(arbolEscena,desp, "rot");
    TNodo* nodoMalla6 = crearNodo(nodoTrans2,crearMalla(alto,ancho,prof),"malla");

return nodoMalla6;
}
/***********************<OBJETOS>******************************************************/
TNodo* TMotorBear::crearObjetoCamaraCompleto(TNodo* padre, char * name, const glm::vec3 pos, float fov, float aspect, float zNear, float zFar){

    TEntidad* cam = crearCamara(pos, fov, aspect, zNear, zFar);
    TNodo* transTras = crearTransObj(padre, name);
    transTras->setVisible(1);
    TNodo* nodoCamara = crearNodo(transTras,cam, name);
    nodoCamara->setVisible(1);
    registrarCamara(nodoCamara);
    TrasladarObjeto(nodoCamara,pos);
    return nodoCamara;
}



TNodo* TMotorBear::crearObjetoLuz(TNodo*padre, glm::vec3 colorLuz, glm::vec3 pos, char* name, int tipoLuz){
    TEntidad* luz = crearLuzNoAmbiente(colorLuz,pos,name, tipoLuz);
    TNodo* transTras = crearTransObj(padre, name);
    transTras->setVisible(1);
    TNodo* nodoLuz = crearNodo(transTras,luz,name);
    nodoLuz->setVisible(1);
    TrasladarObjeto(nodoLuz, pos);
    registrarLuz(nodoLuz);
    return nodoLuz;
}


TNodo* TMotorBear::crearObjetoMallaCompleto(TNodo* padre, char * filename, char * name,int idShad){

    //std::cout<<"HOLAAA"<<std::endl;
    TEntidad* mallaE = crearMalla(filename, idShad);

    TNodo* transTras = crearTransObj(padre, name);
    transTras->setVisible(1);
    TNodo* malla = crearNodo(transTras,mallaE, name);
    malla->setVisible(1);

return malla;
}

TNodo* TMotorBear::crearTransObj(TNodo* padre, char* name){
    TEntidad * trans = crearTransform();

    char* transCH=  "Transformacion de ";
    TNodo* nodoTrans = crearNodo(padre,trans,Concat(transCH, name));

}

void TMotorBear::RotarObjeto(TNodo* malla,glm::vec3 vec){


    TNodo* nodoTrans = malla->getPadre(); //Transformacion
    TTransform * trans =static_cast<TTransform*>(nodoTrans->getEntidad());
    trans->SetRot(vec);


}
void TMotorBear::EscalarObjeto(TNodo* malla,glm::vec3 vec){
  //  std::cout<<"HOLI----------------------------------------"<<std::endl;

    TNodo* nodoTrans = malla->getPadre(); //Transformacion
    TTransform * trans =static_cast<TTransform*>(nodoTrans->getEntidad());
    trans->SetScale(vec);

}

void TMotorBear::TrasladarObjeto(TNodo* malla, glm::vec3 vec){

    TNodo* nodoTrans = malla->getPadre(); //Transformacion
    TTransform * trans =static_cast<TTransform*>(nodoTrans->getEntidad());
    trans->SetPos(vec);
}


void TMotorBear::cambiarNodoOrigen(TNodo* nodoObjeto, TNodo* PadreNuevo){
    TNodo * nodoTrans;
    TNodo* Origen;
    nodoTrans = nodoObjeto->getPadre();
    Origen = nodoTrans->getPadre();

    Origen->remHijo(nodoTrans);
    PadreNuevo->addHijo(nodoTrans);
    reiniciarPosicion(nodoObjeto);
}

void TMotorBear::reiniciarPosicion(TNodo* nodoMalla){
    TNodo* nodo = nodoMalla->getPadre();
    TTransform * trans = static_cast<TTransform*>(nodo->getEntidad());
    trans->SetPos(glm::vec3());
}
void TMotorBear::reiniciarRotacion(TNodo* nodoMalla){
    TNodo* nodo = nodoMalla->getPadre();
    TTransform * trans = static_cast<TTransform*>(nodo->getEntidad());
    trans->SetScale(glm::vec3(1,1,1));
}
void TMotorBear::reiniciarEscalado(TNodo* nodoMalla){
    TNodo* nodo = nodoMalla->getPadre();
    TTransform * trans = static_cast<TTransform*>(nodo->getEntidad());
    trans->SetRot(glm::vec3());
}

void TMotorBear::reiniciarTransPropias(TNodo* nodoMalla){

    reiniciarPosicion(nodoMalla);
    reiniciarRotacion(nodoMalla);
    reiniciarEscalado(nodoMalla);

}


 TNodo* TMotorBear::obtenerTransformacion(TNodo* nodoMalla){
    TNodo*    NodoTras = nodoMalla->getPadre();    //Tras
return NodoTras;
 }

 void  TMotorBear::borrarObjeto(TNodo* nodoObjeto){
  if(nodoObjeto){
    if( nodoObjeto != arbolEscena){
        TNodo* padreObjeto=0;
        TNodo* transObjeto=0;
        transObjeto = nodoObjeto->getPadre();
        padreObjeto = transObjeto->getPadre();

//std::cout<<"PADRE "<<        padreObjeto->getNombreEntidad()<<std::endl;
        padreObjeto->remHijo(transObjeto);
        delete(transObjeto);
      //  verArbol();
    }
    }
 }

void TMotorBear::hacerInvisibleObjeto(TNodo* nodoObjeto){
    nodoObjeto->setVisible(0);
}
void TMotorBear::hacerVisibleObjeto(TNodo* nodoObjeto){
    nodoObjeto->setVisible(1);
}

/*
 void TMotorBear::ReinciarTrans(TNodo* nodoTrans){
    TTransform * trans;

    trans = static_cast<TTransform*>(nodoTrans->getEntidad());
    trans->identidad();
 }
*/
/***********************</OBJETOS>******************************************************/


void TMotorBear::cambiarMalla(TEntidad* mesh, char* file){
    if( file){
       static_cast<TEntidadMalla*> (mesh)->setMalla(static_cast<Mesh*> (gestorRecursos->getRecurso(file, 0)));
    }else{
       static_cast<TEntidadMalla*> (mesh)->setMalla(0);
    }

}
/*
void TMotorBear::transformarMalla(TNodo* nodoMalla, float tipo, glm::vec3 vec){    //necesario que el nodo arbol este ya incorporado al arbol
    TNodo* padre = nodoMalla->getPadre();
        if(tipo){
            padre= padre->getPadre();
        }
    transformarEntidad(padre->getEntidad(),tipo,vec);

}
*/
void TMotorBear::borrarRecurso(char * nombre){
    gestorRecursos->borrarRecurso(nombre);
}

void TMotorBear::animarMalla(TNodo* nodoMalla){
    TEntidadMalla* malla;

   // std::cout<<"ENTRA"<<std::endl;
    malla= static_cast<TEntidadMalla*> (nodoMalla->getEntidad());
    malla->animar();
   // std::cout<<"SALE"<<std::endl;
}
void TMotorBear::resetAnimacion(TNodo* nodoMalla){
    TEntidadMalla* malla;

   // std::cout<<"ENTRA"<<std::endl;
    malla= static_cast<TEntidadMalla*> (nodoMalla->getEntidad());
    malla->resetAnimacion();
}

    //DEBUG
        void TMotorBear::verMallas(TNodo* nodoMalla){
           TEntidadMalla* malla;

    std::cout<<"Entidad "<<nodoMalla->getNombreEntidad()<<std::endl;
            malla= static_cast<TEntidadMalla*> (nodoMalla->getEntidad());
            malla->verInformacionEMalla();
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
glm::mat4 TMotorBear::obtenerMatCam(){ //REHACER BIEN
    TNodo* nodo = verCamaraActiva();
    int cont=0;
    glm::mat4 mat =glm::mat4();
    std::vector<glm::mat4> mats;
    TNodo* transPadre = nodo->getPadre();

    /*while(nodo!=arbolEscena){
    //    std::cout<<nodo->getNombreEntidad()<<std::endl;
     //   std::cout<<nodo->getPadre()->getNombreEntidad()<<std::endl;

       // if(!cont){
           //mats.insert(mats.begin(),static_cast<Camera*> (nodo->getEntidad())->GetViewProjection());
         //  mats.insert(mats.begin(),glm::mat4());

        //mats.insert(mats.begin(), glm::inverse(glm::mat4()));
   //         std::cout<<"CAMARA"<<std::endl;

        if(cont){
      //      mats.insert(mats.begin(),static_cast<TTransform*> (nodo->getEntidad())->GetModel());
     //       std::cout<<"TRANSFORMACION"<<std::endl;
        }else{
          // mats.insert(mats.begin(),glm::inverse(static_cast<Camera*> (nodo->getEntidad())->getPers()));
        }
         nodo=nodo->getPadre();
        cont++;
    }*/
    //std::cout<<"Fuera While"<<std::endl;
   /* for(int i=0; i<mats.size();i++){
            //if(i==mats.size()-i){
               // mat = glm::vec3(0,0,0)  mat;
              //  mat = glm::dot(glm::vec3(0,0,0),mat);
           // }else{
        mat=mat*mats[i];
        //}

    }*/


   // mat = glm::inverse(mat) * static_cast<Camera*> (nodo->getEntidad())->miraA(glm::vec3(0,0,0),glm::vec3(0,0,-1),glm::vec3(0,1,0));
   glm::vec3 transformed = glm::vec3(static_cast<TTransform*> (transPadre->getEntidad())->GetModel() * glm::vec4(glm::vec3(0,0,0), 1.0));
   glm::vec3 transformedP = static_cast<TTransform*> (transPadre->getEntidad())->GetPos();

   //     std::cout<<transformed.x<<","<<std::cout<<(float)transformed.y<<","<<std::cout<<transformed.z<<"|"<<std::endl;
  //      std::cout<<transformedP.x<<","<<std::cout<<transformedP.y<<","<<std::cout<<transformedP.z<<"Y"<<std::endl;

   //glm::vec3 transformedR = static_cast<TTransform*> (transPadre->getEntidad())->GetRot();
   //glm::vec3 transformed =glm::vec3( static_cast<TTransform*> (transPadre->getEntidad())->GetModel() * glm::vec4(glm::vec3(0,0,0), 1.0));
   // mat = glm::inverse(mat) * static_cast<Camera*> (nodo->getEntidad())->miraA(transformed,glm::normalize(glm::vec3(0,0,-1)),glm::vec3(0,1,0));
    mat = static_cast<Camera*> (nodo->getEntidad())->getPers()    * (static_cast<Camera*> (nodo->getEntidad())->miraA(transformedP, transformed + glm::vec3(0,0,-1) /* glm::vec3(0,0,0)*/,glm::vec3(0,1,0)));

      /*for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            std::cout<<mat[i][j]<<" ";
        }
        std::cout<<std::endl;

    }
    std::cout<<std::endl;*/
//mat = mat * glm::inverse(glm::mat4());

  /* glm::vec3 pos =glm::vec3(mat * glm::vec4(glm::vec3(0,0,0), 1.0));

*/


    return mat;
}

void TMotorBear::verDetallesTransformaciones(TNodo* nodoTrans){
    TTransform* trans = static_cast<TTransform*> (nodoTrans->getEntidad());
    std::cout<<"Detalles locales de "<<nodoTrans->getNombreEntidad()<<std::endl;
    trans->MostrarInformacion();
}


//void TMotorBear::draw(Shader* shad){
void TMotorBear::draw(){
    Shader* shad;
    glm::mat4 cam = obtenerMatCam();
    glm::vec3 posCam = glm::vec3( cam * glm::vec4(glm::vec3(0,0,0), 1.0)); //Camara
  /*  for(int i =0; i<4;i++){
        for(int j=0;j<4;j++){
            std::cout<<cam[i][j];
        }std::cout<<std::endl;
    }std::cout<<std::endl;*/
   //luces
   //Viewport
   pila->push_back(cam);
/*
    GLuint cameraPosUniformLocation = glGetUniformLocation(shad->positionLocation(), "uPosCam");
    glUniform3fv(cameraPosUniformLocation,1, &posCam[0]);

    dibujarLuces(shad);
    arbolEscena->draw(shad,pila);
    */
    for(int i =0;i<shadersMot.size();i++){
        shad= shadersMot.at(i);
        shad->Bind();
        GLuint cameraPosUniformLocation = glGetUniformLocation(shad->positionLocation(), "uPosCam");
        glUniform3fv(cameraPosUniformLocation,1, &posCam[0]);

        dibujarLuces(shad);
        arbolEscena->draw(shad,pila);
    }

    pila->pop_back();

}


TEntidad* TMotorBear::crearLuzNoAmbiente(glm::vec3 colorLuz, glm::vec3 posLuz, char* nombreLuz, int tipoLuz){
    TLuz* luz = static_cast<TLuz*> ( crearLuz(colorLuz, nombreLuz, tipoLuz));
    luz->setPosicion(posLuz.x,posLuz.y,posLuz.z);
    return luz;
}


//TLuz* TMotorBear::crearLuz(glm::vec3 colorLuz){
TEntidad* TMotorBear::crearLuz(glm::vec3 colorLuz, char* nombre, int tipoLuz){
    TLuz* luz= new TLuz(colorLuz.x,colorLuz.y,colorLuz.z, nombre, tipoLuz);
   // luz->setIntensidad(colorLuz);
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

void TMotorBear::asignarTextura(TNodo* nodoMalla, char* file ){
    TEntidadMalla* malla = static_cast<TEntidadMalla*>(nodoMalla->getEntidad());
    malla->setTextura(gestorRecursos->getRecurso(file,1));

}


void TMotorBear::dibujarLuces(Shader* shad){
    TNodo* nodoLuz;
    for(int i =0; i< registroLuces.size();i++){
       nodoLuz = registroLuces.at(i);
        dibujarLuz(shad, nodoLuz);
    }
}

void TMotorBear::dibujarLuz(Shader* shad, TNodo* nodoLuz){

    TLuz* luz = static_cast<TLuz*> (nodoLuz->getEntidad());
    TNodo * nodoPa;
    glm::vec3 posicion = glm::vec3();
    nodoPa=nodoLuz->getPadre();
    while(nodoPa != arbolEscena){
    posicion = posicion + static_cast<TTransform*> (nodoPa->getEntidad())->GetPos();
      nodoPa=nodoPa->getPadre();
    }
    luz->aplicarLuz(shad, posicion);

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
  //return  escena->Update(registroLuces.at(1)->getPadre());
}
////////////////GESTOR RECURSOS
    //DEBUG
            void TMotorBear::verRecursos(){
                gestorRecursos->verRecursos();
            }


// TNodo* verCamaraActiva();
//void TMotorBear::activarLuz(TLuz* luz){}

SDL_Texture* TMotorBear::CreaTextura(const std::string &archivo){
  escena->CreaTextura(archivo);
}
void TMotorBear::RenderTextura(SDL_Texture *tex, int x, int y){
  escena->RenderTextura(tex,x,y);
}

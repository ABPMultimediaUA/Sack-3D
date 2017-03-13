#include "tgestorrecursos.h"
#include "mesh.h"

TGestorRecursos::TGestorRecursos()
{
    //ctor
}

TGestorRecursos::~TGestorRecursos()
{

   std::cout<<recursos.size()<<std::endl;
   for(int i=0; i<recursos.size();i++){
        std::cout<<recursos.at(i)->GetNombre()<<std::endl;
        borrarRecurso(recursos.at(i)->GetNombre());
        i--;
   }
}


TRecurso *TGestorRecursos::getRecurso(  char* nombre, int tipo){
//TRecurso *TGestorRecursos::getRecurso( const std::string& nombre, int tipo){

TRecurso* recu;
int encontrado=0;

//sstd::cout<<"Hay "<< recurs<<std::cout<<" recursos"<<std::endl;
    for(int i=0; i<recursos.size();i++){
    //    std::cout<<"HOLI"<<std::endl;
        recu= recursos.at(i);
        if(recu->GetNombre()== nombre){
            std::cout<<"Recurso Encontrado en "<<i<<std::endl;
            std::cout<<recu->GetNombre()<<std::endl;

            recu=recursos.at(i);
            encontrado=1;
            return recursos.at(i);
        }
    }
    if(!encontrado){
             std::cout<<"Recurso NO Encontrado CARGAR"<<std::endl;
        if(tipo==0){

            //Cargar fichero ,y apilar en el vector
            //Mesh* mesh = new Mesh(nombre);
            Mesh* mesh = new Mesh(nombre);
          //  TRecursoMalla* malla= new TRecursoMalla;
            //malla->SetMeshes(load->getMeshes());
          // malla->SetMesh(mesh);
            recu=mesh;
            recu->setNombre(nombre);
            recu->setTipo(tipo);
            std::cout<<"Malla Cargada"<<std::endl;
            recursos.push_back(recu);
            std::cout<<recu->GetNombre()<<std::endl;
          //  delete(mesh); Peta
        }
    }
    return recu;

}
void TGestorRecursos::borrarRecurso(char * nombre){
    TRecurso* recu;
    Mesh* mesh;
    int tipo;
    for(int i=0; i<recursos.size();i++){
            recu=recursos.at(i);
        if(recu->GetNombre()== nombre){
            tipo=recu->GetTipo();
            std::cout<<"Recurso Encontrado"<<std::endl;
            std::cout<<recu->GetNombre()<<std::endl;
            if(tipo==0){
                mesh=static_cast<Mesh*>(recursos.at(i));
                delete(mesh);
            }

            recursos.erase(recursos.begin()+i);
            std::cout<<"Recurso Borrado"<<std::endl;
            break;
        }
    }
}


#include "Master.h"
#include "Client.h"
#include "IrrManager.h"

Client* cliente;
        irr::f32 timer;

int main(){
    cliente = new Client();
    cliente->iniciar();
    if(cliente->getRun()){
	Master m;
	//std::cout<<"asd"<<std::endl;
	while(m.Run()){
        m.Update();
        cliente->recibir();
        if(IrrMngr::Inst()->getTime()>(timer+1112500)){
            cliente->enviar();
            timer = IrrMngr::Inst()->getTime();
        }
	}

	m.Drop();
	}
}

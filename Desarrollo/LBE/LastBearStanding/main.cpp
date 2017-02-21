#include "Master.h"
#include "Client.h"

Client* cliente;

int main(){
    cliente = new Client();
    cliente->iniciar();
	Master m;
	while(m.Run()){
            m.Update();
            cliente->recibir();
            cliente->enviar();
	}
	m.Drop();
}

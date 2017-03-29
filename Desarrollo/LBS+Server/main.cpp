#include "Master.h"
#include "Server/Client.h"
int main(){
    Client::Inst()->iniciar();
	Master m;
	while(m.Run()){
        m.Update();
	}
	m.Drop();
}

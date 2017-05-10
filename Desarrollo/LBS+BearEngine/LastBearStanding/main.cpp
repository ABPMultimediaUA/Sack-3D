#include "Master.h"
#include "Client.h"

int main(int argc, char* argv[]){
    //Client::Inst()->iniciar();
	Master m;
	while(m.Run()){
        m.Update();
	}
}

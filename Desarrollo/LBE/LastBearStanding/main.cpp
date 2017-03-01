#include "Master.h"
int main(){
	Master m;
	while(m.Run()){
        m.Update();
	}
	m.Drop();
}

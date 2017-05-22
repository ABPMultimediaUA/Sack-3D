#include "Client.h"
#include "World.h"
#include "time.h"

Client* Client::pinstance = NULL;
Client* Client::Inst(){
    if(!pinstance){
    pinstance = new Client;
  }
  return pinstance;
}
Client::Client(){
    //unsigned char GetPacketIdentifier(RakNet::Packet *p);
    client=RakNet::RakPeerInterface::GetInstance();
    clientID=RakNet::UNASSIGNED_SYSTEM_ADDRESS;
    isServer=false;
    run = false;
    strncpy(idCliente, "", sizeof(idCliente));
    numPlayersRed=0;
}

void Client::PacketFunction(int aux){
    const Type2Func * it = packetFunction;
    while(it->A != -1){
        if(it->A == aux){
            (this->*it->Type2Func::p)();
            break;
        }
        it++;

    }
}

void Client::iniciar(std::string gameModes, std::string IPs, int difficult){
    dificultad = difficult;

    char auxip[64], auxserverPort[30], auxclientPort[30], mode[30], auxautomatic[30];
    bool server = true;
    IP.assign(IPs);
    gameMode.assign(gameModes);
    //CUIDADOO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //*idCliente = '0';
    //-------------------------------------------------------------------------
    //puts("Select Single(s) or Multiplayer(m) mode");
    //Gets(mode,sizeof(mode));
    //if(strcmp(gameMode,"s") == 0){
    if(gameMode.compare("s") == 0){
        singleMaps();
       *idCliente = '0';
       idPlayerInt = 0;
       run=true;
    }
    else{
        time_t timer;
        time(&timer);
        srand (timer);
        int x=0, i=0;
        std::vector<int> result;
        while(i<10){
            x = rand() % 9;
            result.push_back(x);
            i++;
        }
        //puts("Enter the client port to listen on");
        for(int y=0;y<4;y++) sprintf(auxautomatic,"%s%.0f", auxautomatic, (float)result.at(y));
        strncpy(auxclientPort,auxautomatic, sizeof(auxclientPort));
        if(strcmp(auxclientPort,"") == 0){
            server = false;
        }
        if(server){
            puts("Enter IP to connect to");
            //Gets(auxip,sizeof(auxip));
            //strncpy(auxip, "192.168.1.6", sizeof(auxip));
            const char * c = IP.c_str();
            strncpy(auxip, c, sizeof(auxip));

            puts("Enter the port to connect to");
            //Gets(auxserverPort,sizeof(auxserverPort));
            strncpy(auxserverPort, "3333", sizeof(auxserverPort));

            RakNet::SocketDescriptor socketDescriptor(atoi(auxclientPort),0);
            socketDescriptor.socketFamily=AF_INET;
            client->Startup(8,&socketDescriptor, 1);
            client->SetOccasionalPing(true);

            #if LIBCAT_SECURITY==1
                char public_key[cat::EasyHandshake::PUBLIC_KEY_BYTES];
                FILE *fp = fopen("publicKey.dat","rb");
                fread(public_key,sizeof(public_key),1,fp);
                fclose(fp);
            #endif

            #if LIBCAT_SECURITY==1
                RakNet::PublicKey pk;
                pk.remoteServerPublicKey=public_key;
                pk.publicKeyMode=RakNet::PKM_USE_KNOWN_PUBLIC_KEY;
                bool b = client->Connect(auxip, atoi(auxserverPort), "Rumpelstiltskin", (int) strlen("Rumpelstiltskin"), &pk)==RakNet::CONNECTION_ATTEMPT_STARTED;
                #else
                RakNet::ConnectionAttemptResult car = client->Connect(auxip, atoi(auxserverPort), "Rumpelstiltskin", (int) strlen("Rumpelstiltskin"));
                RakAssert(car==RakNet::CONNECTION_ATTEMPT_STARTED);
            #endif

            printf("\nMy IP addresses:\n");
            unsigned int i;
            for (i=0; i < client->GetNumberOfAddresses(); i++)
            {
                printf("%i. %s\n", i+1, client->GetLocalIP(i));
            }

            printf("My GUID is %s\n", client->GetGuidFromSystemAddress(RakNet::UNASSIGNED_SYSTEM_ADDRESS).ToString());

            while(!run){recibir();}
        }
    }
}

void Client::enviar(int idb){
    char aux[60];
    char id[30];
    int muer;
    int idUsada;

    if(idb!=-1) idUsada=idb;
    else idUsada=idPlayerInt;

    b2Vec2 posicion = World::Inst()->getPlayer(idUsada)->getPosition();
    int dir = World::Inst()->getPlayer(idUsada)->getDireccion();
    if(World::Inst()->getPlayer(idUsada)->getMuerto()==true) muer = 1;
    else muer = 0;

    int estador = World::Inst()->getPlayer(idUsada)->getEstado();

    float auxiliarx = posicion.x * 1000000;
    float auxiliary = posicion.y * 1000000;

    // ---------- ID
        if(strcmp(World::Inst()->getPlayer(idUsada)->getId(), "") == 0){strncpy(id, "-1", sizeof(id));}
        else{strncpy(id, World::Inst()->getPlayer(idUsada)->getId(), sizeof(id));}


    sprintf(aux, "1 %s %.0f %.0f %.0f %.0f %.0f", id, (float)estador,auxiliarx,auxiliary, (float)dir, (float)muer);

    client->Send(aux, (int) strlen(aux)+1, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
}

void Client::enviarUsar(int idb){
    char aux[60];
    char id[30];
    int idUsada;

    if(idb!=-1) idUsada=idb;
    else idUsada=idPlayerInt;

        if(strcmp(World::Inst()->getPlayer(idUsada)->getId(), "") == 0){strncpy(id, "-1", sizeof(id));}
        else{strncpy(id, World::Inst()->getPlayer(idUsada)->getId(), sizeof(id));}

    sprintf(aux, "2 %s", id);

    client->Send(aux, (int) strlen(aux)+1, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
}

void Client::enviarMuerto(int idb){
    char aux[60];
    char id[30];
    int idUsada;

    if(idb!=-1) idUsada=idb;
    else idUsada=idPlayerInt;

        if(strcmp(World::Inst()->getPlayer(idUsada)->getId(), "") == 0){strncpy(id, "-1", sizeof(id));}
        else{strncpy(id, World::Inst()->getPlayer(idUsada)->getId(), sizeof(id));}

    sprintf(aux, "7 %s", id);

    client->Send(aux, (int) strlen(aux)+1, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
}

void Client::enviarCogido (int TCogible, int idb){
    char aux[60];
    char id[30];
    int idUsada;

    if(idb!=-1) idUsada=idb;
    else idUsada=idPlayerInt;

        if(strcmp(World::Inst()->getPlayer(idUsada)->getId(), "") == 0){ strncpy(id, "-1", sizeof(id));}
        else{strncpy(id, World::Inst()->getPlayer(idUsada)->getId(), sizeof(id));}

    sprintf(aux, "3 %s %.0f", id, (float)TCogible);

    client->Send(aux, (int) strlen(aux)+1, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
}

void Client::enviarMoviendo(int moviendo, int idb){

    char aux[60];
    char id[30];
    int idUsada;
    float auxiliarx;
    float auxiliary;

    if(idb!=-1) idUsada=idb;
    else idUsada=idPlayerInt;

    b2Vec2 posicion = World::Inst()->getPlayer(idUsada)->getPosition();
    auxiliarx = posicion.x * 1000000;
    auxiliary = posicion.y * 1000000;
    // ---------- ID
        if(strcmp(World::Inst()->getPlayer(idUsada)->getId(), "") == 0){ strncpy(id, "-1", sizeof(id));}
        else{strncpy(id, World::Inst()->getPlayer(idUsada)->getId(), sizeof(id));}

    sprintf(aux, "4 %s %.0f %.0f %.0f", id, (float)moviendo,auxiliarx,auxiliary);
    client->Send(aux, (int) strlen(aux)+1, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
}

void Client::enviarSalto(int Nsalto, int idb){

    char aux[60];
    char id[30];
    int idUsada;
    float auxiliarx;
    float auxiliary;

    if(idb!=-1){ idUsada=idb;
    }else{ idUsada=idPlayerInt;}

    b2Vec2 posicion = World::Inst()->getPlayer(idUsada)->getPosition();
    auxiliarx = posicion.x * 1000000;
    auxiliary = posicion.y * 1000000;

    // ---------- ID
        if(strcmp(World::Inst()->getPlayer(idUsada)->getId(), "") == 0){ strncpy(id, "-1", sizeof(id));}
        else{strncpy(id, World::Inst()->getPlayer(idUsada)->getId(), sizeof(id));}

    sprintf(aux, "5 %s %.0f %.0f %.0f", id, (float)Nsalto, auxiliarx, auxiliary);
    client->Send(aux, (int) strlen(aux)+1, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
}

void Client::enviarHacerseMuerto(int idb){
    char aux[60];
    char id[30];
    int idUsada;

    if(idb!=-1) idUsada=idb;
    else idUsada=idPlayerInt;

        if(strcmp(World::Inst()->getPlayer(idUsada)->getId(), "") == 0){strncpy(id, "-1", sizeof(id));}
        else{strncpy(id, World::Inst()->getPlayer(idUsada)->getId(), sizeof(id));}

    sprintf(aux, "8 %s", id);
    client->Send(aux, (int) strlen(aux)+1, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
}

void Client::recibir(){

    for (p=client->Receive(); p; client->DeallocatePacket(p), p=client->Receive()){

            if(comprobarPaquete(p)) break;
            //--------TRABAJO DEL MENSAJE

            char recibido[60];
            iterador=0;

            strncpy(recibido, reinterpret_cast<const char*>(p->data), sizeof(recibido));
            char * msg;
            msg = strtok(recibido, " ");

            while(msg != NULL){
                strncpy(params[iterador].var, msg, sizeof(params[iterador].var));
                //std::cout<<"TEXTO "<<msg<<std::endl;
                msg = strtok(NULL, " ");

                iterador++;
            }
            //--------LLAMADA A FUNCION SEGUN PAQUETE
                //std::cout<<"LLamadaFuncion"<<std::endl;
            if(comprobacion(params[0].var)){
            //std::cout<<"tipo.-"<<params[0].var<<"1.-"<<params[1].var<<" 2.-"<<params[2].var<<" 3.-"<<params[3].var<<" 4.-"<<params[4].var<<" 5.-"<<params[5].var<<" 6.-"<<params[6].var<<"7.-"<<params[7].var<<" 8.-"<<params[8].var<<" 9.-"
//            <<params[9].var<<std::endl;
            PacketFunction(atoi(params[0].var));

            }
        }

}



unsigned char Client::GetPacketIdentifier(RakNet::Packet *p)
{
    if (p==0)
        return 255;

    if ((unsigned char)p->data[0] == ID_TIMESTAMP)
    {
        RakAssert(p->length > sizeof(RakNet::MessageID) + sizeof(RakNet::Time));
        return (unsigned char) p->data[sizeof(RakNet::MessageID) + sizeof(RakNet::Time)];
    }
    else
        return (unsigned char) p->data[0];
}


void Client::analizarPaquete0(){

    struct TPlayersRed{
        char* id;
    };

    TPlayersRed players [3]=
    {{params[2].var}
    ,{params[3].var}
    ,{params[4].var}
    };
    if(strcmp(idCliente, "") == 0){
        strncpy(idCliente, params[1].var, sizeof(idCliente));
        for(int i=numPlayersRed+1;i<iterador-1;i++){
            numPlayersRed++;
            strncpy(playersRed[i-1].id, players[i-1].id, sizeof(playersRed[i-1].id));
        }
    }
    else{
        for(int i=numPlayersRed+1;i<iterador-1;i++){
            numPlayersRed++;
            strncpy(playersRed[i-1].id, params[1].var, sizeof(playersRed[i-1].id));
        }
    }
    idPlayerInt = *(idCliente)-'0';
}

void Client::analizarPaquete1(){
    long int x = atol(params[3].var);
    long int y = atol(params[4].var);
    int vivo = atoi(params[2].var);
    int dir = atoi(params[5].var);
    int muerto = atoi(params[6].var);

    //--------PARTE SETTEAR PLAYERRED

    for(unsigned int i=0; i < World::Inst()->GetPlayers().size(); i++){
        if(strcmp(World::Inst()->GetPlayers().at(i)->getId(), params[1].var) == 0){
            PlayerRed* p = dynamic_cast<PlayerRed*>(World::Inst()->GetPlayers().at(i));
            p->setx(x);
            p->sety(y);
            p->setEstado(vivo);
            p->setDireccion(dir);
            p->setMuerto(muerto);
            p->setPos();

        }
    }
}

void Client::analizarPaquete2(){

    for(unsigned int i=0; i < World::Inst()->GetPlayers().size(); i++){
        if(strcmp(World::Inst()->GetPlayers().at(i)->getId(), params[1].var) == 0){
            dynamic_cast<PlayerRed*>(World::Inst()->GetPlayers().at(i))->usar();
        }
    }
}

void Client::analizarPaquete3(){

        int cogible = atoi(params[2].var);
        //--------PARTE SETTEAR PLAYERRED

        for(unsigned int i=0; i < World::Inst()->GetPlayers().size(); i++){

            if(strcmp(World::Inst()->GetPlayers().at(i)->getId(), params[1].var) == 0){
                if(cogible == -1){ dynamic_cast<PlayerRed*>(World::Inst()->GetPlayers().at(i))->CogerTirar(-1);
                }else{
                dynamic_cast<PlayerRed*>(World::Inst()->GetPlayers().at(i))->CogerTirar(cogible);
                }
            }
        }
}

void Client::analizarPaquete4(){

        int moviendo = atoi(params[2].var);
        long int x = atol(params[3].var);
        long int y = atol(params[4].var);
        //--------PARTE SETTEAR PLAYERRED


        for(unsigned int i=0; i < World::Inst()->GetPlayers().size(); i++){
            if(strcmp(World::Inst()->GetPlayers().at(i)->getId(), params[1].var) == 0){
                PlayerRed* p = dynamic_cast<PlayerRed*>(World::Inst()->GetPlayers().at(i));
                p->setx(x);
                p->sety(y);
                p->setPos();
                p->mover(moviendo);
            }
        }

}

void Client::analizarPaquete5(){

    int moviendo = atoi(params[2].var);
    long int x = atol(params[3].var);
    long int y = atol(params[4].var);
    for(unsigned int i=0; i < World::Inst()->GetPlayers().size(); i++){

        if(strcmp(World::Inst()->GetPlayers().at(i)->getId(), params[1].var) == 0){
            PlayerRed* p = dynamic_cast<PlayerRed*>(World::Inst()->GetPlayers().at(i));
            p->setx(x);
            p->sety(y);
            p->setPos();
            p->saltar(moviendo);
        }
    }
}

void Client::analizarPaquete6(){

    run=true;
    std::vector<int> result;
    for(int i=0;i<10;i++){
            result.push_back(atoi(params[i+1].var));
    }

    setMaps(result);
}

void Client::analizarPaquete7(){

    for(unsigned int i=0; i < World::Inst()->GetPlayers().size(); i++){
        if(strcmp(World::Inst()->GetPlayers().at(i)->getId(), params[1].var) == 0){
            dynamic_cast<PlayerRed*>(World::Inst()->GetPlayers().at(i))->morirRed();
        }
    }
}

void Client::analizarPaquete8(){

    for(unsigned int i=0; i < World::Inst()->GetPlayers().size(); i++){
        if(strcmp(World::Inst()->GetPlayers().at(i)->getId(), params[1].var) == 0){
            dynamic_cast<PlayerRed*>(World::Inst()->GetPlayers().at(i))->fingirMuerte();
        }
    }
}

bool Client::comprobacion(char* tipo){
if(strcmp(tipo, "0") == 0 || strcmp(tipo, "1") == 0 || strcmp(tipo, "2") == 0 ||
   strcmp(tipo, "3") == 0 || strcmp(tipo, "4") == 0 || strcmp(tipo, "5") == 0 ||
   strcmp(tipo, "6") == 0 || strcmp(tipo, "7") == 0 || strcmp(tipo, "8") == 0 ) return true;
else
    return false;

}

bool Client::comprobarPaquete(RakNet::Packet* p){
    char aux[60];
    char* comp="";
    packetIdentifier = GetPacketIdentifier(p);
        if(packetIdentifier == ID_DISCONNECTION_NOTIFICATION         || packetIdentifier == ID_ALREADY_CONNECTED         || packetIdentifier == ID_INCOMPATIBLE_PROTOCOL_VERSION  ||
           packetIdentifier == ID_REMOTE_DISCONNECTION_NOTIFICATION  || packetIdentifier == ID_REMOTE_CONNECTION_LOST    || packetIdentifier == ID_REMOTE_NEW_INCOMING_CONNECTION ||
           packetIdentifier == ID_CONNECTION_BANNED                  || packetIdentifier == ID_CONNECTION_ATTEMPT_FAILED || packetIdentifier == ID_NO_FREE_INCOMING_CONNECTIONS   ||
           packetIdentifier == ID_INVALID_PASSWORD                   || packetIdentifier == ID_CONNECTION_LOST           || packetIdentifier == ID_CONNECTION_REQUEST_ACCEPTED ){
               if(packetIdentifier == ID_CONNECTION_REQUEST_ACCEPTED){
                    printf("ID_CONNECTION_REQUEST_ACCEPTED to %s with GUID %s\n", p->systemAddress.ToString(true), p->guid.ToString());
                    printf("My external address is %s\n", client->GetExternalID(p->systemAddress).ToString(true));
               }else sprintf(aux, "%s", packetIdentifier);

               return true;
           }
        else
            return false;

}

void Client::setMaps(std::vector<int> mapas){
    //std::cout<<"setMapsINICIA"<<std::endl;
    for(int i=0;i<10;i++){
        maps.push_back(mapas[i]);
    }
    //std::cout<<"setMapsACABA"<<std::endl;
}

void Client::singleMaps(){

    time_t timer;
    time(&timer);
    srand (timer);
    int x=0;
    std::vector<int> nums;
    std::vector<int> result;

    for(int i=0;i<10;i++) nums.push_back(i);
    while(nums.size()!=0){
        x = rand() % nums.size();
        result.push_back(nums[x]);
        nums.erase(nums.begin()+x);
    }

    setMaps(result);
}

Client::~Client()
{
    //dtor
}

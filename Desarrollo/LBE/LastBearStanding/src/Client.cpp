#include "Client.h"
#include "World.h"

Client::Client()
{
    //ctor
    //unsigned char GetPacketIdentifier(RakNet::Packet *p);
    client=RakNet::RakPeerInterface::GetInstance();
    clientID=RakNet::UNASSIGNED_SYSTEM_ADDRESS;
    isServer=false;
    strncpy(idCliente, "", sizeof(idCliente));
    numPlayersRed=0;
}

PlayerRed* Client::crearPlayer(char* i){
    return(new PlayerRed(b2Vec2(100.f, 61.995),0,i));
}

void Client::iniciar(){

    char auxip[64], auxserverPort[30], auxclientPort[30];
    puts("Enter the client port to listen on");
    Gets(auxclientPort,sizeof(auxclientPort));

    puts("Enter IP to connect to");
    //Gets(auxip,sizeof(auxip));
    //strncpy(auxip, "192.168.1.6", sizeof(auxip));
    strncpy(auxip, "192.168.1.6", sizeof(auxip));

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
	//client->GetGuidFromSystemAddress(RakNet::UNASSIGNED_SYSTEM_ADDRESS).ToString()
	//strncpy(aux, PhysicWorld::Instance()->getPlayer()->getClientPort(), sizeof(aux));

}

void Client::enviar(){

    char aux[60];
    char tipo[60];
    char id[30];
    char estado[30];
    char posx[30];
    char posy[30];
    char direcc[30];
    char muertor[30];
    int estador;
    int dir;
    int muer;
    int moviendo;
    float auxiliarx;
    float auxiliary;

    b2Vec2 posicion = World::Inst()->getPlayer(1)->getPosition();
    strncpy(tipo, "1", sizeof(tipo));
    dir = World::Inst()->getPlayer(1)->getDireccion();
    if(World::Inst()->getPlayer(1)->getMuerto()==true){
        muer = 1;
    }else{
        //std::cout<<"ENVIANDO entrooo"<<std::endl;
        muer = 0;
    }
    estador = World::Inst()->getPlayer(1)->getEstado();

    auxiliarx = posicion.x * 1000000;
    auxiliary = posicion.y * 1000000;

    // ---------- ID
    if(strcmp(World::Inst()->getPlayer(1)->getId(), "") == 0){ strncpy(id, "-1", sizeof(id));}

    else{    strncpy(id, World::Inst()->getPlayer(1)->getId(), sizeof(id));}

    //---------- ESTADO
    sprintf(estado, "%.0f", (float)estador);
    // ------- DIRECCION DE PJ
    sprintf(direcc, "%.0f", (float)dir);
    // -------- POSICIONES
    sprintf(posx, "%.0f", auxiliarx);
    sprintf(posy, "%.0f", auxiliary);

        sprintf(muertor, "%.0f", (float)muer);
/*
    #ifdef _WIN32
		Sleep(30);
    #else
        usleep(30 * 1000);
    #endif
*/

    strncat (tipo, " ", 30);
    strncat (tipo, id, 30);
    strncat (tipo, " ", 30);
    strncat (tipo, estado, 30);
    strncat (tipo, " ", 30);
    strncat (tipo, posx, 30);
    strncat (tipo, " ", 30);
    strncat (tipo, posy, 30);
    strncat (tipo, " ", 30);
    strncat (tipo, direcc, 30);
    strncat (tipo, " ", 30);
    strncat (tipo, muertor, 30);
    strncpy(aux, tipo, sizeof(aux));
    //std::cout<<"ENVIANDO "<<aux<<std::endl;
    client->Send(aux, (int) strlen(aux)+1, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
}

void Client::enviarUsar(){
    char aux[60];
    char tipo[60];
    char id[30];

    strncpy(tipo, "2", sizeof(tipo));
        if(strcmp(World::Inst()->getPlayer(1)->getId(), "") == 0){ strncpy(id, "-1", sizeof(id));}

        else{    strncpy(id, World::Inst()->getPlayer(1)->getId(), sizeof(id));}

    strncat (tipo, " ", 30);
    strncat (tipo, id, 30);

    strncpy(aux, tipo, sizeof(aux));
    std::cout<<"ENVIANDO "<<aux<<std::endl;
    client->Send(aux, (int) strlen(aux)+1, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
}

void Client::enviarCogido (int TCogible){
    char aux[60];
    char tipo[60];
    char id[30];
    char cogible[30];

    strncpy(tipo, "3", sizeof(tipo));

    if(strcmp(World::Inst()->getPlayer(1)->getId(), "") == 0){ strncpy(id, "-1", sizeof(id));}

    else{    strncpy(id, World::Inst()->getPlayer(1)->getId(), sizeof(id));}

    sprintf(cogible, "%.0f", (float)TCogible);

    strncat (tipo, " ", 30);
    strncat (tipo, id, 30);
    strncat (tipo, " ", 30);
    strncat (tipo, cogible, 30);

    //strncat (tipo, Tarma, 30);
    strncpy(aux, tipo, sizeof(aux));
    std::cout<<"ENVIANDO "<<aux<<std::endl;
    client->Send(aux, (int) strlen(aux)+1, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
}

void Client::enviarMoviendo(int moviendo){

    char aux[60];
    char tipo[60];
    char id[30];
    char mov[30];

    strncpy(tipo, "4", sizeof(tipo));


    // ---------- ID
    if(strcmp(World::Inst()->getPlayer(1)->getId(), "") == 0){ strncpy(id, "-1", sizeof(id));}
    else{    strncpy(id, World::Inst()->getPlayer(1)->getId(), sizeof(id));}

    sprintf(mov, "%.0f", (float)moviendo);

    strncat (tipo, " ", 30);
    strncat (tipo, id, 30);
    strncat (tipo, " ", 30);
    strncat (tipo, mov, 30);

    strncpy(aux, tipo, sizeof(aux));
    std::cout<<"ENVIANDO "<<aux<<std::endl;
    client->Send(aux, (int) strlen(aux)+1, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
}

void Client::enviarSalto(int Nsalto){

    char aux[60];
    char tipo[60];
    char id[30];
    char salto[30];
    strncpy(tipo, "5", sizeof(tipo));


    // ---------- ID
    if(strcmp(World::Inst()->getPlayer(1)->getId(), "") == 0){ strncpy(id, "-1", sizeof(id));}
    else{    strncpy(id, World::Inst()->getPlayer(1)->getId(), sizeof(id));}

    sprintf(salto, "%.0f", (float)Nsalto);

    strncat (tipo, " ", 30);
    strncat (tipo, id, 30);
    strncat (tipo, " ", 30);
    strncat (tipo, salto, 30);

    strncpy(aux, tipo, sizeof(aux));
    std::cout<<"ENVIANDO "<<aux<<std::endl;
    client->Send(aux, (int) strlen(aux)+1, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
}

void Client::recibir(){

    for (p=client->Receive(); p; client->DeallocatePacket(p), p=client->Receive())
		{
			// We got a packet, get the identifier with our handy function
			packetIdentifier = GetPacketIdentifier(p);

			// Check if this is a network message packet
			switch (packetIdentifier)
			{
			case ID_DISCONNECTION_NOTIFICATION:
				// Connection lost normally
				printf("ID_DISCONNECTION_NOTIFICATION\n");
				break;
			case ID_ALREADY_CONNECTED:
				// Connection lost normally
				printf("ID_ALREADY_CONNECTED\n");
				break;
			case ID_INCOMPATIBLE_PROTOCOL_VERSION:
				printf("ID_INCOMPATIBLE_PROTOCOL_VERSION\n");
				break;
			case ID_REMOTE_DISCONNECTION_NOTIFICATION: // Server telling the clients of another client disconnecting gracefully.  You can manually broadcast this in a peer to peer enviroment if you want.
				printf("ID_REMOTE_DISCONNECTION_NOTIFICATION\n");
				break;
			case ID_REMOTE_CONNECTION_LOST: // Server telling the clients of another client disconnecting forcefully.  You can manually broadcast this in a peer to peer enviroment if you want.
				printf("ID_REMOTE_CONNECTION_LOST\n");
				break;
			case ID_REMOTE_NEW_INCOMING_CONNECTION: // Server telling the clients of another client connecting.  You can manually broadcast this in a peer to peer enviroment if you want.
				printf("ID_REMOTE_NEW_INCOMING_CONNECTION\n");
				break;
			case ID_CONNECTION_BANNED: // Banned from this server
				printf("We are banned from this server.\n");
				break;
			case ID_CONNECTION_ATTEMPT_FAILED:
				printf("Connection attempt failed\n");
				break;
			case ID_NO_FREE_INCOMING_CONNECTIONS:
				// Sorry, the server is full.  I don't do anything here but
				// A real app should tell the user
				printf("ID_NO_FREE_INCOMING_CONNECTIONS\n");
				break;

			case ID_INVALID_PASSWORD:
				printf("ID_INVALID_PASSWORD\n");
				break;

			case ID_CONNECTION_LOST:
				// Couldn't deliver a reliable packet - i.e. the other system was abnormally
				// terminated
				printf("ID_CONNECTION_LOST\n");
				break;

			case ID_CONNECTION_REQUEST_ACCEPTED:
                char aux[30];
				// This tells the client they have connected
				printf("ID_CONNECTION_REQUEST_ACCEPTED to %s with GUID %s\n", p->systemAddress.ToString(true), p->guid.ToString());
				printf("My external address is %s\n", client->GetExternalID(p->systemAddress).ToString(true));
                //PhysicWorld::Instance()->getPlayer()->setId( const_cast<char*> (client->GetGuidFromSystemAddress(RakNet::UNASSIGNED_SYSTEM_ADDRESS).ToString()));
				//strncpy(aux, PhysicWorld::Instance()->getPlayer()->getId(), sizeof(aux));
                //client->Send(aux, (int) strlen(aux)+1, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
				break;
			default:
				// It's a client, so just show the message
				//printf("%s\n", p->data);
				break;
			}

			/////////TRABAJO DEL MENSAJE\\\\\\\\\\\\

            char id[30];
			char recibido[60];
			char tipo[30];
			char param1[30];
			char param2[30];
			char param3[30];
			char param4[30];
			char param5[30];
            char param6[30];
			int iterador=0;
			long int x;
			long int y;
			int vivo;
			int dir;
            int muerto;
			int cogible;
			int Tarma;
			int moviendo;
			PlayerRed* Player1;
			PlayerRed* Player2;
			PlayerRed* Player3;

            struct TPlayersRed{
                PlayerRed* player;
                char* id;
            };

			strncpy(recibido, reinterpret_cast<const char*>(p->data), sizeof(recibido));
			char * msg;
			msg = strtok(recibido, " ");
            //std::cout<<"RECIBIENDO "<<msg<<std::endl;
			while(msg != NULL){
                switch (iterador)
                {
                    case 0:
                        strncpy(tipo, msg, sizeof(tipo));
                        break;
                    case 1:
                        strncpy(param1, msg, sizeof(param1));
                        break;
                    case 2:
                        strncpy(param2, msg, sizeof(param2));
                        break;
                    case 3:
                        strncpy(param3, msg, sizeof(param3));
                        break;
                    case 4:
                        strncpy(param4, msg, sizeof(param4));
                        break;
                    case 5:
                        strncpy(param5, msg, sizeof(param5));
                        break;
                    case 6:
                        strncpy(param6, msg, sizeof(param6));
                        break;
                }
                msg = strtok(NULL, " ");
                iterador++;
            }

            TPlayersRed players [3]=
            {{Player1, param2}
            ,{Player2, param3}
            ,{Player3, param4}
            };

            /////////PARTE CREAR PLAYERRED\\\\\\\\

            if(strcmp(tipo, "0") == 0){
                if(strcmp(World::Inst()->getPlayer(1)->getId(), "") == 0){
                    World::Inst()->getPlayer(1)->setId(param1);
                    strncpy(idCliente, param1, sizeof(idCliente));
                    for(int i=1;i<iterador-1;i++){
                        players[i-1].player = crearPlayer(players[i-1].id);
                        //World::Inst()->GetPlayersRed()->push_back(players[i-1].player);
                        World::Inst()->AddPlayer(players[i-1].player);
                        numPlayersRed++;
                        //playersRed[numPlayersRed-1].id = players[i-1].id;
                        strncpy(playersRed[numPlayersRed-1].id, players[i-1].id, sizeof(playersRed[numPlayersRed-1].id));
                    }
                }
                else{
                    std::cout<<"seteando de compaaaadre>"<<param1<<" e-"<<param2<<" x-"<<param3<<" y-"<<param4<<" d-"<<param5<<" ITE-"<<iterador<<std::endl;
                    PlayerRed* playerRed = new PlayerRed(b2Vec2(100.f, 61.995),0,param1);
                    //World::Inst()->GetPlayersRed()->push_back(playerRed);
                    World::Inst()->AddPlayer(playerRed);
                    numPlayersRed++;
                    //playersRed[numPlayersRed-1].id = param1;
                    strncpy(playersRed[numPlayersRed-1].id, param1, sizeof(param1));
                }
                enviar();
            }

            /////////PARTE UPDATE PLAYERRED\\\\\\\\

            if(strcmp(tipo, "1") == 0){
                x = atol(param3);
                y = atol(param4);
                vivo = atoi(param2);
                dir = atoi(param5);
                 muerto = atoi(param6);

                /////////PARTE SETTEAR PLAYERRED\\\\\\\\

        if(IrrMngr::Inst()->getTime()>(timer+5000)){
                for(int i=0; i < World::Inst()->GetPlayers().size(); i++){
                    if(strcmp(World::Inst()->GetPlayers().at(i)->getId(), param1) == 0){
                        PlayerRed* p = dynamic_cast<PlayerRed*>(World::Inst()->GetPlayers().at(i));
                        p->setx(x);
                        p->sety(y);
                        p->setEstado(vivo);
                        p->setDireccion(dir);
                        p->setMuerto(muerto);
                        p->setPos();
                        std::cout<<"SEEEET "<<msg<<std::endl;
                    }
                }
                timer=IrrMngr::Inst()->getTime();
        }
            }

            /////////PARTE DISPARO PLAYERRED\\\\\\\\


            if(strcmp(tipo, "2") == 0){
                for(int i=0; i < World::Inst()->GetPlayers().size(); i++){
                    if(strcmp(World::Inst()->GetPlayers().at(i)->getId(), param1) == 0){
                        World::Inst()->GetPlayers().at(i)->usar();
                    }
            }
            }

            if(strcmp(tipo, "3") == 0){
                cogible = atoi(param2);
                /////////PARTE SETTEAR PLAYERRED\\\\\\\\

                for(int i=0; i < World::Inst()->GetPlayers().size(); i++){

                    if(strcmp(World::Inst()->GetPlayers().at(i)->getId(), param1) == 0){
                        if(cogible == 0){ World::Inst()->GetPlayers().at(i)->Soltar();
                        }else{
                        //World::Inst()->GetPlayersRed().at(i)->CogerTirar(cogible);
                        World::Inst()->GetPlayers().at(i)->CogerTirar();
                        }
                    }
                }
            }

            if(strcmp(tipo, "4") == 0){
                moviendo = atoi(param2);
                /////////PARTE SETTEAR PLAYERRED\\\\\\\\


                for(int i=0; i < World::Inst()->GetPlayers().size(); i++){

                    if(strcmp(World::Inst()->GetPlayers().at(i)->getId(), param1) == 0){
                        dynamic_cast<PlayerRed*>(World::Inst()->GetPlayers().at(i))->mover(moviendo);
                    }
                }
            }

            if(strcmp(tipo, "5") == 0){
                moviendo = atoi(param2);
                for(int i=0; i < World::Inst()->GetPlayers().size(); i++){

                    if(strcmp(World::Inst()->GetPlayers().at(i)->getId(), param1) == 0){
                        //World::Inst()->GetPlayersRed().at(i)->saltar(moviendo);
                        dynamic_cast<PlayerRed*>(World::Inst()->GetPlayers().at(i))->saltar(moviendo);
                        //World::Inst()->GetPlayers().at(i)->saltar(moviendo);
                    }
                }
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

///////METODOS DE ACCION DE PLAYER\\\\\\\

void Client::dispararPistola(long int x, long int y, int direc){
    std::cout<<"entro en disparar! X:"<<x<<" Y:"<<y<<std::endl;
    float aux_x = x/1000000.f;
    float aux_y = y/1000000.f;
    World::Inst()->AddBala(new Bala(irr::core::vector3df(aux_x, aux_y, 0), 300, 10, 1.0f, direc));
}

void Client::dispararEscopeta(long int x, long int y, int direc){
    std::cout<<"entro en disparar! X:"<<x<<" Y:"<<y<<std::endl;
    float aux_x = x/1000000.f;
    float aux_y = y/1000000.f;

    for(int i=0; i<15; i++){
            float desvBala = rand()% 20 - 10;
            float velBala = rand()% 3 + 10;
            World::Inst()->AddBala(new Bala(irr::core::vector3df(aux_x, aux_y, 0), 200, velBala, desvBala, direc, 1));
    }
}

Client::~Client()
{
    //dtor
}

#include "Client.h"
#include "PhysicWorld.h"

Client::Client()
{
    //ctor
    //unsigned char GetPacketIdentifier(RakNet::Packet *p);
    client=RakNet::RakPeerInterface::GetInstance();
    clientID=RakNet::UNASSIGNED_SYSTEM_ADDRESS;
    isServer=false;
}

void Client::iniciar(){

    char auxip[64], auxserverPort[30], auxclientPort[30];
    puts("Enter the client port to listen on");
    Gets(auxclientPort,sizeof(auxclientPort));

    puts("Enter IP to connect to");
    Gets(auxip,sizeof(auxip));
    //strncpy(auxip, "192.168.43.104", sizeof(auxip));

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
	//strncpy(aux, PhysicWorld::Instance()->getPlayer()->getClientPort(), sizeof(aux));

}

void Client::enviar(){

    char aux[60];
    char id[60];
    char estado[30];
    char posx[30];
    char posy[30];
    char direcc[30];
    bool muerto;
    int dir;



    irr::core::vector3df posicion = PhysicWorld::Instance()->getPlayer(1)->getPosition();

    muerto = PhysicWorld::Instance()->getPlayer(1)->getFingirMuerte();
    //std::cout<<"LLEVO"<<std::endl;
    dir = PhysicWorld::Instance()->getPlayer(1)->getDireccion();

    //std::cout<<posicion.X<<std::endl;
    float auxiliarx;
    float auxiliary;
    auxiliarx = posicion.X * 1000000;
    auxiliary = posicion.Y * 1000000;

    // ---------- ID
    if(strcmp(PhysicWorld::Instance()->getPlayer(1)->getId(), "") == 0){
        strncpy(id, "-1", sizeof(id));
    } else{
        strncpy(id, PhysicWorld::Instance()->getPlayer(1)->getId(), sizeof(id));
    }

    //std::cout<<"mi idddddddddd"<<id<<std::endl;
    //---------- VIVO O MUERTO
    if(muerto) strncpy(estado, "0", sizeof(estado));
    else strncpy(estado, "1", sizeof(estado));

    // ------- DIRECCION DE PJ
    sprintf(direcc, "%.0f", (float)dir);
    // -------- POSICIONES
    sprintf(posx, "%.0f", auxiliarx);
    sprintf(posy, "%.0f", auxiliary);
/*
    #ifdef _WIN32
		Sleep(30);
    #else
        usleep(30 * 1000);
    #endif
*/


    char posx2[30];
    strncpy(posx2, posx, sizeof(posx2));
    char posy2[30];
    strncpy(posy2, posy, sizeof(posy2));

    strncat (id, " ", 30);
    strncat (id, estado, 30);
    strncat (id, " ", 30);
    strncat (id, posx2, 30);
    strncat (id, " ", 30);
    strncat (id, posy2, 30);
    strncat (id, " ", 30);
    strncat (id, direcc, 30);
    strncpy(aux, id, sizeof(aux));
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
			//	PhysicWorld::Instance()->getPlayer()->setId( const_cast<char*> (client->GetGuidFromSystemAddress(RakNet::UNASSIGNED_SYSTEM_ADDRESS).ToString()));
				//strncpy(aux, PhysicWorld::Instance()->getPlayer()->getId(), sizeof(aux));
                //client->Send(aux, (int) strlen(aux)+1, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
				break;
			default:
				// It's a client, so just show the message
				//printf("%s\n", p->data);
				break;
			}

			/////////TRABAJO DEL MENSAJE\\\\\\\\\\\\

			char recibido[60];
			char id_r[30];
			char estado_r[30];
			char posx_r[30];
			char posy_r[30];
			char direccion_r[30];
			int iterador=0;
			long int x;
			long int y;
			int vivo;
			int dir;
            PlayerRed* playerRed1;
            PlayerRed* playerRed2;
            PlayerRed* playerRed;

			strncpy(recibido, reinterpret_cast<const char*>(p->data), sizeof(recibido));
			std::cout<<"recibido-> "<<recibido<<std::endl;
			char * msg;
			msg = strtok(recibido, " ");
			while(msg != NULL){
                switch (iterador)
                {
                    case 0:
                        strncpy(id_r, msg, sizeof(id_r));
                        break;
                    case 1:
                        strncpy(estado_r, msg, sizeof(estado_r));
                        break;
                    case 2:
                        strncpy(posx_r, msg, sizeof(posx_r));
                        break;
                    case 3:
                        strncpy(posy_r, msg, sizeof(posy_r));
                        break;
                    case 4:
                        strncpy(direccion_r, msg, sizeof(direccion_r));
                        break;
                }
                msg = strtok(NULL, " ");
                iterador++;
            }

            int help;
            help = atoi(id_r);

            if(help > 0 && iterador<5){
                if(strcmp(PhysicWorld::Instance()->getPlayer(1)->getId(), "") == 0){
                    std::cout<<"ESTOY seteando mi id->"<<id_r<<std::endl;
                    PhysicWorld::Instance()->getPlayer(1)->setId(id_r);
                    switch (iterador)
                    {
                        case 2:
                            std::cout<<"Mi compa que ya jugaba es -> "<<estado_r<<std::endl;
                            playerRed = new PlayerRed(estado_r, 100, 0);
                            std::cout<<"He pasado meter"<<std::endl;
                            PhysicWorld::Instance()->GetPlayersRed()->push_back(playerRed);
                            break;
                        case 3:
                             std::cout<<"Mis compas que ya jugaban son -> "<<estado_r<<" "<<posx_r<<std::endl;
                            playerRed = new PlayerRed(estado_r, 100, 0);
                             std::cout<<"He pasado meter"<<std::endl;
                            PhysicWorld::Instance()->GetPlayersRed()->push_back(playerRed);
                            playerRed1 = new PlayerRed(posx_r, 100, 0);
                             std::cout<<"He pasado meter"<<std::endl;
                            PhysicWorld::Instance()->GetPlayersRed()->push_back(playerRed1);
                            break;
                        case 4:
                            playerRed = new PlayerRed(estado_r, 100, 0);
                            PhysicWorld::Instance()->GetPlayersRed()->push_back(playerRed);
                            playerRed1 = new PlayerRed(posx_r, 100, 0);
                            PhysicWorld::Instance()->GetPlayersRed()->push_back(playerRed1);
                            playerRed2 = new PlayerRed(posy_r, 100, 0);
                            PhysicWorld::Instance()->GetPlayersRed()->push_back(playerRed2);
                            break;
                    }
                }
                else{
                    std::cout<<"seteando de compaaaadre>"<<id_r<<" e-"<<estado_r<<" x-"<<posx_r<<" y-"<<posy_r<<" d-"<<direccion_r<<" ITE-"<<iterador<<std::endl;
                    PlayerRed* playerRed = new PlayerRed(id_r, 100, 0);
                    //PhysicWorld::Instance()->getPlayerRed()->setId(id_r);
                    std::cout<<"He pasado"<<std::endl;
                    PhysicWorld::Instance()->GetPlayersRed()->push_back(playerRed);
                }

            }

           /*sscanf(posx_r, "%d", x);
           sscanf(posy_r, "%d", y);*/
           if(iterador>=5){
            x = atol(posx_r);
            y = atol(posy_r);
            vivo = atoi(estado_r);
            dir = atoi(direccion_r);
           }
            //std::cout<<"REDSSS"<<PhysicWorld::Instance()->GetPlayersRed()->size()<<std::endl;
            for(int i=0; i < PhysicWorld::Instance()->GetPlayersRed()->size(); i++){
                if(strcmp(PhysicWorld::Instance()->GetPlayersRed()->at(i)->getId(), id_r) == 0){
                    PhysicWorld::Instance()->GetPlayersRed()->at(i)->setx(x);
                    PhysicWorld::Instance()->GetPlayersRed()->at(i)->sety(y);
                    PhysicWorld::Instance()->GetPlayersRed()->at(i)->setEstado(vivo);
                    PhysicWorld::Instance()->GetPlayersRed()->at(i)->setDireccion(dir);
                }
            }
    }

    //
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

Client::~Client()
{
    //dtor
}

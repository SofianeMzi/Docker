 #include<stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
#include <stdlib.h>
#include <string.h>
#define PORT 1110
#include <time.h>// pour nanosleep
#include <sys/time.h>//pour gattimeofday()



int main(int argc, char *argv[])
{

////////////// structure pour utiliser nanosleep
	long time_ns=strtol(argv[1], NULL, 10);//temps en ns, (rentré par l'utilisateur)

	struct timespec time, time2;
	time.tv_sec = 0;
	time.tv_nsec = time_ns;

/////////////

	struct timeval temps_avant, temps_apres;//Structure pour la mesure du temps d'aller retour


///////////

        int port;       
        SOCKET sock;   
        SOCKADDR_IN csin;   

        csin.sin_family=AF_INET;//Le protocole utilisé sera AF_INET (TCP)
        csin.sin_addr.s_addr=htonl(INADDR_ANY);//permet la connexion au socket de tous les ip
        csin.sin_port=htons(PORT);//Le port utilisé sera PORT
       
        sock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP); //définition de la socket 

        int sock_err=bind(sock,(SOCKADDR*)&csin,sizeof(csin));// associer les informations de la structure précédente à la socket 
	/* Si la socket fonctionne */
	if(sock_err != SOCKET_ERROR)
	{ 
       
        	sock_err=listen(sock, 7);//on met la socket dans un état d'écoute, et on permet la connexion de 7 clients en même temps au maximum
		printf("Listage du port %d...\n", PORT);
		/* Si la socket fonctionne */
		if(sock_err != SOCKET_ERROR)
		{
			/* Attente pendant laquelle le client se connecte */
        		printf("Patientez pendant que les Node se connectent sur le port %d...\n", PORT);

        		SOCKET accept_node_2 = INVALID_SOCKET; 
        		int len=sizeof(csin);
        		while(accept_node_2==INVALID_SOCKET)
        		{
                	accept_node_2 = accept(sock, (SOCKADDR *)&csin, &len);//on accepte la connexion du client node 2
			printf("Le Node2 se connecte avec la socket %d de %s:%d\n", accept_node_2, inet_ntoa(csin.sin_addr), htons(csin.sin_port));
        		}
			
//ajout
			SOCKET accept_node_3 = INVALID_SOCKET;
			while(accept_node_3==INVALID_SOCKET)
        		{
                	accept_node_3 = accept(sock, (SOCKADDR *)&csin, &len);//on accepte la connexion du client node 3
			printf("Le Node3 se connecte avec la socket %d de %s:%d\n", accept_node_3, inet_ntoa(csin.sin_addr), htons(csin.sin_port));
        		}

			SOCKET accept_node_4 = INVALID_SOCKET;
			while(accept_node_4==INVALID_SOCKET)
        		{
                	accept_node_4 = accept(sock, (SOCKADDR *)&csin, &len);//on accepte la connexion du client node 4
			printf("Le Node4 se connecte avec la socket %d de %s:%d\n", accept_node_4, inet_ntoa(csin.sin_addr), htons(csin.sin_port));
        		}

			SOCKET accept_node_5 = INVALID_SOCKET;
			while(accept_node_5==INVALID_SOCKET)
        		{
                	accept_node_5 = accept(sock, (SOCKADDR *)&csin, &len);//on accepte la connexion du client node 5
			printf("Le Node5 se connecte avec la socket %d de %s:%d\n", accept_node_5, inet_ntoa(csin.sin_addr), htons(csin.sin_port));
        		}

			SOCKET accept_node_6 = INVALID_SOCKET;
			while(accept_node_6==INVALID_SOCKET)
        		{
                	accept_node_6 = accept(sock, (SOCKADDR *)&csin, &len);//on accepte la connexion du client node 6
			printf("Le Node6 se connecte avec la socket %d de %s:%d\n", accept_node_6, inet_ntoa(csin.sin_addr), htons(csin.sin_port));
        		}

			SOCKET accept_node_7 = INVALID_SOCKET;
			while(accept_node_7==INVALID_SOCKET)
        		{
                	accept_node_7 = accept(sock, (SOCKADDR *)&csin, &len);//on accepte la connexion du client node 7
			printf("Le Node7 se connecte avec la socket %d de %s:%d\n", accept_node_7, inet_ntoa(csin.sin_addr), htons(csin.sin_port));
        		}

			SOCKET accept_node_8 = INVALID_SOCKET;
			while(accept_node_8==INVALID_SOCKET)
        		{
                	accept_node_8 = accept(sock, (SOCKADDR *)&csin, &len);//on accepte la connexion du client node 8
			printf("Le Node8 se connecte avec la socket %d de %s:%d\n", accept_node_8, inet_ntoa(csin.sin_addr), htons(csin.sin_port));
        		}

			


        		char buffer[50];
        		//memset(buffer,0,sizeof(buffer));
        		int send_node_2=0;
			int send_node_3=0;
			int send_node_4=0;
			int send_node_5=0;
			int send_node_6=0;
			int send_node_7=0;
			int send_node_8=0;
			int i=0;
			int j=0;

        		while(send_node_2>-1)
    		       {

				//node2
           			strcpy(buffer,"ping");
				gettimeofday (&temps_avant, NULL);//début du compteur aller-retour
                		send_node_2=send(accept_node_2,buffer,sizeof(buffer),0);//envoi de données vers le node 2
				printf("Message envoyé au node 2...\n");
				j=j+1;//compteur de "pong" envoyé
                		send_node_2=recv(accept_node_2,buffer,sizeof(buffer),0);//réception des données du node 2
				gettimeofday (&temps_apres, NULL);//fin du compteur aller-retour
				printf("temps aller-retour données node1 vers node2: %ld µs\n", (temps_apres.tv_sec - temps_avant.tv_sec)*1000000 + (temps_apres.tv_usec - temps_avant.tv_usec));//affichage du temps d'aller-retour
				if(send_node_2!=0)// si le message n'est pas vide
				{
                		printf("Node2 : %s\n",buffer);// on affiche le contenu du message
				int delay_s=nanosleep(&time, &time2);//délai d'attente en seconde 
				if (delay_s<0){
					printf("erreur avec le délai");
					perror("nanosleep");
					return -1;
				}
				
				i=i+1;//competeur de "ping" recu
				}
				else
				{
				printf("Le Node1 a envoyé %i ping, et a reçu %i pong\n", j, i);
				printf("Connexion terminée\n\n");
				shutdown(sock,2);
				close(sock);
				}
				//node3
				
           			strcpy(buffer,"ping");
				printf("Message envoyé au node 3...\n");
				gettimeofday (&temps_avant, NULL);//début du compteur aller-retour
				send_node_3=send(accept_node_3,buffer,sizeof(buffer),0);
				j=j+1;
				send_node_3=recv(accept_node_3,buffer,sizeof(buffer),0);
				gettimeofday (&temps_apres, NULL);//fin du compteur aller-retour
				printf("temps aller-retour données node1 vers node3: %ld µs\n", (temps_apres.tv_sec - temps_avant.tv_sec)*1000000 + (temps_apres.tv_usec - temps_avant.tv_usec));//affichage du temps d'aller-retour
				if(send_node_3!=0)
				{
                		printf("Node3 : %s\n",buffer);
				int delay_s=nanosleep(&time, &time2);//délai en seconde 
				if (delay_s<0){
					printf("erreur avec le délai");
					perror("nanosleep");
					return -1;
				}
				i=i+1;
				}
				else
				{
				printf("Le Node1 a envoyé %i ping, et a reçu %i pong\n", j, i);
				printf("Connexion terminée\n\n");
				shutdown(sock,2);
				close(sock);
				}
				// node 4
				strcpy(buffer,"ping");
				printf("Message envoyé au node 4...\n");
				gettimeofday (&temps_avant, NULL);//début du compteur aller-retour
				send_node_4=send(accept_node_4,buffer,sizeof(buffer),0);
				j=j+1;
				send_node_4=recv(accept_node_4,buffer,sizeof(buffer),0);
				gettimeofday (&temps_apres, NULL);//fin du compteur aller-retour
				printf("temps aller-retour données node1 vers node4: %ld µs\n", (temps_apres.tv_sec - temps_avant.tv_sec)*1000000 + (temps_apres.tv_usec - temps_avant.tv_usec));//affichage du temps d'aller-retour
				if(send_node_4!=0)
				{
                		printf("Node4 : %s\n",buffer);
				int delay_s=nanosleep(&time, &time2);//délai en seconde 
				if (delay_s<0){
					printf("erreur avec le délai");
					perror("nanosleep");
					return -1;
				}
				i=i+1;
				}
				else
				{
				printf("Le Node1 a envoyé %i ping, et a reçu %i pong\n", j, i);
				printf("Connexion terminée\n\n");
				shutdown(sock,2);
				close(sock);
				}
				//node5
				strcpy(buffer,"ping");
				printf("Message envoyé au node 5...\n");
				gettimeofday (&temps_avant, NULL);//début du compteur aller-retour
				send_node_5=send(accept_node_5,buffer,sizeof(buffer),0);
				j=j+1;
				send_node_5=recv(accept_node_5,buffer,sizeof(buffer),0);
				gettimeofday (&temps_apres, NULL);//fin du compteur aller-retour
				printf("temps aller-retour données node1 vers node5: %ld µs\n", (temps_apres.tv_sec - temps_avant.tv_sec)*1000000 + (temps_apres.tv_usec - temps_avant.tv_usec));//affichage du temps d'aller-retour
				if(send_node_5!=0)
				{
                		printf("Node5 : %s\n",buffer);
				int delay_s=nanosleep(&time, &time2);//délai en seconde 
				if (delay_s<0){
					printf("erreur avec le délai");
					perror("nanosleep");
					return -1;
				}
				i=i+1;
				}
				else
				{
				printf("Le Node1 a envoyé %i ping, et a reçu %i pong\n", j, i);
				printf("Connexion terminée\n\n");
				shutdown(sock,2);
				close(sock);
				}
				//node6
				strcpy(buffer,"ping");
				printf("Message envoyé au node 6...\n");
				gettimeofday (&temps_avant, NULL);//début du compteur aller-retour
				send_node_6=send(accept_node_6,buffer,sizeof(buffer),0);
				j=j+1;
				send_node_6=recv(accept_node_6,buffer,sizeof(buffer),0);
				gettimeofday (&temps_apres, NULL);//fin du compteur aller-retour
				printf("temps aller-retour données node1 vers node6: %ld µs\n", (temps_apres.tv_sec - temps_avant.tv_sec)*1000000 + (temps_apres.tv_usec - temps_avant.tv_usec));//affichage du temps d'aller-retour
				if(send_node_6!=0)
				{
                		printf("Node6 : %s\n",buffer);
				int delay_s=nanosleep(&time, &time2);//délai en seconde 
				if (delay_s<0){
					printf("erreur avec le délai");
					perror("nanosleep");
					return -1;
				}
				i=i+1;
				}
				else
				{
				printf("Le Node1 a envoyé %i ping, et a reçu %i pong\n", j, i);
				printf("Connexion terminée\n\n");
				shutdown(sock,2);
				close(sock);
				}
				//node7
				strcpy(buffer,"ping");
				printf("Message envoyé au node 7...\n");
				gettimeofday (&temps_avant, NULL);//début du compteur aller-retour
				send_node_7=send(accept_node_7,buffer,sizeof(buffer),0);
				j=j+1;
				send_node_7=recv(accept_node_7,buffer,sizeof(buffer),0);
				gettimeofday (&temps_apres, NULL);//fin du compteur aller-retour
				printf("temps aller-retour données node1 vers node7: %ld µs\n", (temps_apres.tv_sec - temps_avant.tv_sec)*1000000 + (temps_apres.tv_usec - temps_avant.tv_usec));//affichage du temps d'aller-retour
				if(send_node_7!=0)
				{
                		printf("Node7 : %s\n",buffer);
				int delay_s=nanosleep(&time, &time2);//délai en seconde 
				if (delay_s<0){
					printf("erreur avec le délai");
					perror("nanosleep");
					return -1;
				}
				i=i+1;
				}
				else
				{
				printf("Le Node1 a envoyé %i ping, et a reçu %i pong\n", j, i);
				printf("Connexion terminée\n\n");
				shutdown(sock,2);
				close(sock);
				}
				//node8
				strcpy(buffer,"ping");
				printf("Message envoyé au node 8...\n");
				gettimeofday (&temps_avant, NULL);//début du compteur aller-retour
				send_node_8=send(accept_node_8,buffer,sizeof(buffer),0);
				j=j+1;
				send_node_8=recv(accept_node_8,buffer,sizeof(buffer),0);
				gettimeofday (&temps_apres, NULL);//fin du compteur aller-retour
				printf("temps aller-retour données node1 vers node8: %ld µs\n", (temps_apres.tv_sec - temps_avant.tv_sec)*1000000 + (temps_apres.tv_usec - temps_avant.tv_usec));//affichage du temps d'aller-retour
				if(send_node_8!=0)
				{
                		printf("Node8 : %s\n",buffer);
				int delay_s=nanosleep(&time, &time2);//délai en seconde 
				if (delay_s<0){
					printf("erreur avec le délai");
					perror("nanosleep");
					return -1;
				}
				i=i+1;
				}
				else
				{
				printf("Le Node1 a envoyé %i ping, et a reçu %i pong\n", j, i);
				printf("Connexion terminée\n\n");
				shutdown(sock,2);
				close(sock);
				}
			}
			
		}
	}

}


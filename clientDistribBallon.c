#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
<<<<<<< HEAD
#include <netdb.h> 
#define PORT 10001
#include "Stock.h"
=======
#define PORT 10001
>>>>>>> 06165ad47ec004befbee37b1cdafff274e9f7f76



typedef struct ball ball;
struct ball{int ID; char IPjoueur[32]; int chrono};

<<<<<<< HEAD
char IProbot[32]="127.0.0.1"; // adresse provisoire, sera remplacée par l'IP du robot

char* IPjoueur[6]={"127.0.0.1","127.0.0.1","127.0.0.1","127.0.0.1","127.0.0.1","127.0.0.1"}; // 
char* RFIDjoueur[6]={"a","b","c","d","e","f"};

void error(const char *msg) { perror(msg); exit(0); }

//  fonction récupération des données de la partie sous la forme d'un buffer

char* getBeeBotte(){
	char requete[256]="curl \"http://api.beebotte.com/v1/public/data/read/vberry/testDB/msg\"| tee data.txt";
	system(requete);
	printf("\n ici commencent les token\n");

	FILE *file;
  	char *buffer;
  	long lSize;
  	file = fopen("data.txt", "r");
  	fseek( file , 0L , SEEK_END);
  	lSize = ftell( file );
  	rewind( file );
	// allocate memory for entire content 
	buffer = calloc( 1, lSize+1 );
	if( !buffer ){
		fclose(file),fputs("memory alloc fails",stderr),exit(1);
	}
	// copy the file into the buffer 
	if( 1!=fread( buffer , lSize, 1 , file) ){
		fclose(file),free(buffer),fputs("entire read fails",stderr),exit(1);
	}
	return buffer;
}



//  fonction de parsage qui remplit les tableaux de RFID/IP 


void ParseBeeBotte(char* buffer){
	char* token;
	int nbRobots = 0;
	strtok(buffer,"{");
	while (nbRobots<6){
		
		strtok(NULL,"=");
		char *type = strtok(NULL,","); // récupération type données
		strtok(NULL,"=");
		char *entite = strtok(NULL,","); // récupération entite	
		strtok(NULL,"=");
		char *RFID = strtok(NULL,","); // récupération RFID
		strtok(NULL,"=");
		char *IP = strtok(NULL,"\""); // récupération dernière donnee (IP)
		printf("\n %s, %s,%s \n\n",entite,RFID,IP);

		char typetest[24]="";
		strcpy(typetest,type);
		char entitetest[24]="";
		strcpy(entitetest,entite);
		if(strcmp(typetest,"IP")==0 && strcmp(entitetest, "RJ")==0){
			printf("entrechaklign\n");
			RFIDjoueur[nbRobots] = RFID;
			IPjoueur[nbRobots] = IP;
			printf(" RFIDjoueur : %s IPjoueur :%s \n",RFIDjoueur[nbRobots],IPjoueur[nbRobots]);
			nbRobots++;
		}
	}

}




// fonction d'envoi des coordonnées au Beebotte (fonction du prof)

int sendToBeBotte(char *canal, char *clefCanal, char *ressource, char *data[])
{
    // data est un tableau de chaines (char[]), c-a-d un tableau de char a deux dimensions
    // printf("data[0] is %s\n",data[0]);
    //printf("data[3] is %s\n",data[3]);
 
    int i;
    char *host = "api.beebotte.com";
    /* !! TODO remplacer 'testVB' par le canal dans lequel publier (ex: partie12)
        (ici msg est la "ressource" que ce canal attend */
    char path[100] = "/v1/data/write/";
    strcat(path,canal);strcat(path,"/"); strcat(path,ressource);
    struct hostent *server;
    struct sockaddr_in serv_addr;
    int sockfd, bytes, sent, received, total, message_size;
    char *message, response[4096];

    // Necessaire pour envoyer des donnees sur beebotte.com (noter le token du canal a la fin) :
    char headers[300] ="Host: api.beebotte.com\r\nContent-Type: application/json\r\nX-Auth-Token: ";
    strcat(headers,clefCanal);strcat(headers,"\r\n"); 
    
    char donnees[4096] = "{\"data\":\""; // "data" est impose par beebotte.com
    for (i=0;i<3;i++) {
        strcat(donnees,data[i]);strcat(donnees,",");
    }
    strcat(donnees,data[3]);strcat(donnees,"\"}");

    /* How big is the whole HTTP message? (POST) */
    message_size=0;
    message_size+=strlen("%s %s HTTP/1.0\r\n")+strlen("POST")+strlen(path)+strlen(headers);
    message_size+=strlen("Content-Length: %d\r\n")+10+strlen("\r\n")+strlen(donnees); 
    /* allocate space for the message */
    message=malloc(message_size);

    /* Construit le message POST */
    sprintf(message,"POST %s HTTP/1.0\r\n",path); 
    sprintf(message+strlen(message), "%s",headers);
    sprintf(message+strlen(message),"Content-Length: %d\r\n",strlen(donnees));
    strcat(message,"\r\n");              /* blank line     */
    strcat(message,donnees);             /* body           */

    /* What are we going to send? */
    printf("Request:\n%s\n-------------\n",message);

    /* create the socket */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) error("ERROR opening socket");
    /* lookup the ip address */
    server = gethostbyname(host);
    if (server == NULL) error("ERROR, no such host");
    /* fill in the structure */
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(80); // port 80
    memcpy(&serv_addr.sin_addr.s_addr,server->h_addr,server->h_length);
    /* connect the socket */
    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
        error("ERROR connecting");
    /* send the request */
    total = strlen(message);
    sent = 0;
    do {
        bytes = write(sockfd,message+sent,total-sent);
        if (bytes < 0)
            error("ERROR writing message to socket");
        if (bytes == 0)
            break;
        sent+=bytes;
    } while (sent < total);

    /* receive the response */
    memset(response,0,sizeof(response));
    total = sizeof(response)-1;
    received = 0;
    do {
        bytes = read(sockfd,response+received,total-received);
        if (bytes < 0) error("ERROR reading response from socket");
        if (bytes == 0)
            break;
        received+=bytes;
    } while (received < total);

    if (received == total) error("ERROR storing complete response from socket");
    /* close the socket */
    close(sockfd); 

    /* process response */
    printf("Response:\n%s\n",response);

    free(message);
    return 0;
}

// 3 - Communication RPC avec le gestionnaire de stock
char*
distributionballon_1(char *host, char *IP)
{
	CLIENT *clnt;
	reponse1  *result_1;
	data1  distribution_1_arg;

#ifndef	DEBUG
	clnt = clnt_create (host, distributionballon, VERSION_UN, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */
	strcpy(distribution_1_arg.IPjoueur, IP);
	result_1 = distribution_1(&distribution_1_arg, clnt);
	if (result_1 == (reponse1 *) NULL) {
		clnt_perror (clnt, "call failed");
	}
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
	return result_1->cleballon;
}


int
validationballon_1(char *host, char *cleballon)
{
	CLIENT *clnt;
	reponse2  *result_1;
	data2  validation_1_arg;

#ifndef	DEBUG
	clnt = clnt_create (host, validationballon, VERSION_UN, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */
	strcpy(validation_1_arg.cleballon, cleballon);
	result_1 = validation_1(&validation_1_arg, clnt);
	if (result_1 == (reponse2 *) NULL) {
		clnt_perror (clnt, "call failed");
	}
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
	return result_1->ok;
}
















=======
char *IP="127.0.0.1"; // adresse provisoire, sera remplacée par l'IP du robot

int code = 1; // ne pas oublier de l'incrémenter, variable globale

/*function qui génère un ballon à distribuer*/
ball GenerateBall(char *IPjoueur){

  ball Ballon;
  strcpy(Ballon.IPjoueur,IPjoueur);
  /*Initialisation pour la date en seconde*/
  time_t temps;
  time(&temps);

 	Ballon.chrono = temps;

  Ballon.ID = code;
  return Ballon;
}

/*Sérialisation d'un ballon*/

char* Serialize(ball Ballon){

  char str1[1024];
  sprintf(str1,"%d",Ballon.ID);
  fflush(stdout);
  strcat(str1,"*");
  strcat(str1,Ballon.IPjoueur);
  strcat(str1,"*");
  char str3[128];
  sprintf(str3,"%d",Ballon.chrono);
  strcat(str1,str3);
  return str1;

}


// tableau des ballons

ball Ballons[4]; // à mettre dans le gestionnaire de stock de ballon

// 1- fonction récupération logs 
>>>>>>> 06165ad47ec004befbee37b1cdafff274e9f7f76





int main(){

<<<<<<< HEAD
	// réception des données
	char* datagame = getBeeBotte();

	///parsage
	ParseBeeBotte(datagame);

	//initialisations sockets
=======
	// réception des logs

	///parsage

>>>>>>> 06165ad47ec004befbee37b1cdafff274e9f7f76
	int sock;
    struct sockaddr_in server;
    char message[1000] , server_reply[2000];
     
<<<<<<< HEAD
   
	//boucle infinie
	 for(;;){
	 	
	 	// provisoirement : récupérer l'adresse RFID du robot à la main

	 	printf("Rentrez le RFID du robot qui veut recevoir le ballon :\n");

	 	scanf("%s",&demande);
	 	int numero=0;
	 	while (strcmp(demande, RFIDjoueur[numero])!=0){
	 		numero++;
	 	}

	 	IProbot= IPjoueur[numero];


	 	 //Create socket
	    sock = socket(AF_INET , SOCK_STREAM , 0);
	    if (sock == -1)
	    {
	        printf("Could not create socket");
	    }
	    puts("Socket created");
	     
	    server.sin_addr.s_addr = inet_addr(IProbot);
	    server.sin_family = AF_INET;
	    server.sin_port = htons( 10001 );


=======
    //Create socket
    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");
     
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons( 8888 );

	//boucle infinie
	 for(;;){
	 	

	 	//if passage RFID commment le matérialiser ?
>>>>>>> 06165ad47ec004befbee37b1cdafff274e9f7f76
	    //Connexion au serveur robot
	    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
	    {
	        perror("connect failed. Error");
	        return 1;
	    }
	     
	    puts("Connected\n");

	  	/* Reception de donnees du serveur ( Réponse à la question : Avez vous un ballon ?)*/
<<<<<<< HEAD
	  	char buffer[256];
	  	recv(sock, buffer, 256, 0);
=======
	  	char buffer[1024];
	  	recv(sock, buffer, 1024, 0);
>>>>>>> 06165ad47ec004befbee37b1cdafff274e9f7f76
	  	printf("Recu : %s\n", buffer);

	  	/* Initialisation du test ballon */
	  	int BallonValide= 0;
	  	char* ballonRecu[256];

	  	/* Test ballon valide*/

<<<<<<< HEAD
	  	char buffer2[256] = "pas de ballon";

	  	int res = strcmp(buffer, buffer2);

	  	//si il y a un ballon dans le fichier Ballon.txt, on regarde s'il est encore valide
	  	if(res != 0){
	    	  int reponse = validationballon_1("localhost",buffer); // libèrera le ballon si il est dans le tableau.
	    }
	    int cleballon = distributionballon_1("localhost",IProbot);
	    send(sock, cleballon, 32, 0); // envoie le ballon créé au robot

=======
	  	char buffer2[1024] = "pas de ballon";

	  	int res = strcmp(buffer, buffer2);

	  	if(res != 0){
	    	/*Decrypt(buffer, ballonRecu);*/
	    	const char s[2] = "*";

	    	char *token;
	    	token = strtok(ballonRecu,s); // récupération de L'ID
	    	int i = 0;
	    	while(i<=code && BallonValide == 0){
	      		char var = (char)i;
	      		if(strcmp(token,var)!=0){
	        		i++;
	      		}
	      		else{
		        	token = strtok(NULL,s); // récupération de l'IP
		        	token = strtok(NULL,s); // récupération de l'heure en seconde
		        	time_t tempsVerif;
		        	time(&tempsVerif);
		        	int tempsRecup = atoi(token);
	        		if( tempsVerif < tempsRecup+180){
	          			BallonValide = 1; 
	        		}
	      		}
	        }  
	    }
>>>>>>> 06165ad47ec004befbee37b1cdafff274e9f7f76
	}

	return 0;

}
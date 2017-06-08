#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <netdb.h> 
#define PORT 10001
#include "Stock.h"

int main(){
	printf("Rentrez le RFID du robot qui veut recevoir le ballon :\n");
	char demande[24];
	fgets(demande, sizeof(demande), stdin);
	printf("%s",demande);
	return 0;
}
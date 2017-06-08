/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "Validation.h"


void
validationbut_1(char *host, char *cleballon)
{
	CLIENT *clnt;
	reponse  *result_1;
	data  validation_1_arg;

#ifndef	DEBUG
	clnt = clnt_create (host, ValidationBut, VERSION_UN, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	result_1 = validation_1(&validation_1_arg, clnt);
	if (result_1 == (reponse *) NULL) {
		clnt_perror (clnt, "call failed");
	}
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{
	char *host="localhost"; //récupération IP du distributeur (à vous de jouer)
	char *cle="1.127.0.0.1.5000"; // clé du ballon sous la forme "id.IP.chrono" 
	int valide;

	/*if (argc < 2) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	host = argv[1];*/
	valide = validationbut_1 (host, cle); // =0 si le ballon n'est pas valide et 1 sinon. à implémenter dans votre code
	printf("%d",valide);
exit (0);
}
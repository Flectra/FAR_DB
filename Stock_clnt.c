/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include <memory.h> /* for memset */
#include "Stock.h"

/* Default timeout can be changed using clnt_control() */
static struct timeval TIMEOUT = { 25, 0 };

reponse1 *
<<<<<<< HEAD
distribution_1(data1 *argp, CLIENT *clnt)
=======
validation_1(data1 *argp, CLIENT *clnt)
>>>>>>> 06165ad47ec004befbee37b1cdafff274e9f7f76
{
	static reponse1 clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
<<<<<<< HEAD
	if (clnt_call (clnt, distribution,
=======
	if (clnt_call (clnt, Validation,
>>>>>>> 06165ad47ec004befbee37b1cdafff274e9f7f76
		(xdrproc_t) xdr_data1, (caddr_t) argp,
		(xdrproc_t) xdr_reponse1, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

reponse2 *
<<<<<<< HEAD
validation_1(data2 *argp, CLIENT *clnt)
=======
distribution_2(data2 *argp, CLIENT *clnt)
>>>>>>> 06165ad47ec004befbee37b1cdafff274e9f7f76
{
	static reponse2 clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
<<<<<<< HEAD
	if (clnt_call (clnt, validation,
=======
	if (clnt_call (clnt, distribution,
>>>>>>> 06165ad47ec004befbee37b1cdafff274e9f7f76
		(xdrproc_t) xdr_data2, (caddr_t) argp,
		(xdrproc_t) xdr_reponse2, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}
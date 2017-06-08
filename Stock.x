struct data1{
<<<<<<< HEAD
	char IPjoueur[32];
=======
	int ballonDispo;
>>>>>>> 06165ad47ec004befbee37b1cdafff274e9f7f76
};
typedef struct data1 data1;

struct reponse1{
	char cleballon[256];
};
typedef struct reponse1 reponse1;

struct data2{
	char cleballon[256];
};
<<<<<<< HEAD
typedef struct data2 data2;

struct reponse2{
	int ok;
};
typedef struct reponse2 reponse2;

program distributionballon{
	version VERSION_UN{		 
		reponse1 distribution(data1) =1;
=======
typedef struct data1 data1;

struct reponse1{
	int ok;
};
typedef struct reponse1 reponse1;

program Validation{
	version VERSION_UN{		 
		reponse1 Validation(data1) =1;
>>>>>>> 06165ad47ec004befbee37b1cdafff274e9f7f76
	} = 1;
} = 0x20000001;


<<<<<<< HEAD
program validationballon{
	version VERSION_UN{		 
		reponse2 validation(data2) =1;
	} = 1;
=======
program distribution{
	version VERSION_UN{		 
		reponse2 distribution(data2) =1;
	} = 2;
>>>>>>> 06165ad47ec004befbee37b1cdafff274e9f7f76
} = 0x20000001;
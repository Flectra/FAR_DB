struct data1{
	char IPjoueur[32];
};
typedef struct data1 data1;

struct reponse1{
	char cleballon[256];
};
typedef struct reponse1 reponse1;

struct data2{
	char cleballon[256];
};
typedef struct data2 data2;

struct reponse2{
	int ok;
};
typedef struct reponse2 reponse2;

program distributionballon{
	version VERSION_UN{		 
		reponse1 distribution(data1) =1;
	} = 1;
} = 0x20000001;


program validationballon{
	version VERSION_UN{		 
		reponse2 validation(data2) =1;
	} = 1;
} = 0x20000001;
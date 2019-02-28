
#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H


#include "BankClient.h"

class BankAccount{

	//Propiedades

	bool accState; //true = activo, false = inactivo
	char* key;
	int balance;
	BankClient *client;

public:
	int accountnumber;

	//Constructor
	BankAccount(int, char*, BankClient*, int);

	//Metodos
 	void Block();
 	void UnBlock();
 	bool CheckKey(char*);
 	void deposit(int);
 	bool Retirar(int);
 	bool updateKey(char*);
	bool ConsultState();
	int ConsultBalance();
	BankClient* ConsultUser();
	void ChangeClient(BankClient*);
};

#endif


#ifndef ACCOUNT_H
#define ACCOUNT_H
#include "BankClient.h"

struct Balance
 {
 	int Activos:
 	int Debe; 
 	int Saldo;
 }; 

class BankAccount(){

	//Propiedades
	int Accountnumber;
	bool AccState; //true = activo, false = inactivo
	char*  Key;
	char* Owner;
	Balance balance;

	//Constructor
	BankAccount(int accountnumber, bool accstate, char* key, char* Owner);

	//Metodos
 	void Blockacc();
 	void UnBlockacc();
 	bool CheckKey(char* Keyint);
 	void deposit(int moneyVal);
 	void Retirar(int moneyVal);
 	void updateKey(char* accountkey);
	bool ConsultState();
	Balance* ConsultBalance();
	char* ConsultUser();
	void ChangeClient(BankClient* client);
}

#endif

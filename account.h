#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <iostream>
#include <string.h>
BankAccount(int accountnumber, bool accstate, char* key, Valance* valace, BankClient* client);
	int Accountnumber;
	bool AccState;
		char  Key [4];
	Valance balance;
struct Valance
 {
 	int  Activos:
 	int Debe; 
 }; 
 	void Blockacc();
 	void UnBlockacc();
 	bool CheckKey(char* Keyint);
 	void deposit(int moneyVal);
 	void Retirar(int moneyVal);
 	void updateKey(char* accountkey );
	bool ConsultState();
	Valance* ConsultBalance();
	BankClient* ConsultUser();
	void ChangeClient(BankClient* client);
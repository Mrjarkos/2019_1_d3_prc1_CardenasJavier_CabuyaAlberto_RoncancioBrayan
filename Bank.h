
#ifndef BANK_H

#define BANK_H

#include "BankAccount.h"
#include "BankClient.h"

struct Account_information{
	bool state;
	Balance* balance;
	BankClient* cliente;

};

class Bank
{
	char* name;
	BankClient[]* list_clients;
	BankAccount[]* list_accounts;
	int How_many_client; 
	int How_many_account;
	int initial_accounts;
	int initial_clients; 

	Bank();
	~Bank();

	bool create_client();

	bool update_client();

	BankClient consult_client();

	bool create_account();

	BankAccount consult_account();

	bool block_unblock_account();

	bool deposit();

	int withdrawal();

	bool transfer_account();	

	bool id_account_exist(int id_account){}
	
};
	
#endif


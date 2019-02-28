
#ifndef BANK_H
#define BANK_H

#include "BankAccount.h"
#include "BankClient.h"

struct Account_information{
	int id_account;
	bool state;
	int balance;
	BankClient* cliente;
};

class Bank
{
	char* name;
	BankClient** list_clients;
	BankAccount** list_accounts;
	int How_many_client; 
	int How_many_account;
	int initial_accounts;
	int initial_clients; 

public:
	Bank(char*, BankClient**, BankAccount**);
	~Bank();

	char* get_name();

	bool create_client();

	bool update_client();

	BankClient* consult_client();

	bool create_account(int, char*, BankClient*, int);

	Account_information* consult_account(int, char*);

	bool block_unblock_account(int, char*, bool);

	bool deposit(int, int);

	int withdrawal(int, int, char*);

	bool transfer_money(int, char*, int, int);	

	bool id_account_exist(int);
	
	BankAccount* select_count(int);
};
	
#endif


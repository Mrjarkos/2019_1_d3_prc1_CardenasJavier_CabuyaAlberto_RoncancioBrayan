
#ifndef BANK_H
#define BANK_H

#include "BankAccount.h"
#include "BankClient.h"
#include <iostream>
#include <string>
#include <sstream>

struct Account_information{
	char* id_account;
	bool state;
	int balance;
	BankClient* cliente;
	Account_information() {
		id_account = 0;
		state = 0;
		balance = 0;
	}
};

struct Client_information{
	char* firstName;
	char* lastName;
	char* id_client;
	BankAccount** accounts;
	int nAccount;

	Client_information() {
		firstName = 0;
		lastName = 0;
		id_client = 0;
	}
};

class Bank
{
	char* name;
	BankClient** list_clients;
	BankAccount** list_accounts;
	int How_many_client; 
	int How_many_account;
	int next_account;
	int initial_accounts;
	int initial_clients; 

public:
	Bank(char*, BankClient**, BankAccount**);
	~Bank();

	char* get_name();

	bool create_client(char*, char*, char*, int, char**); 

	bool create_client(char*, char*, char*, int, char*, char*, int);

	bool update_client(BankClient*, char*, char*, char*, int);

	Client_information* consult_client(char* id_client);

	bool create_account(char*, char*, BankClient*, int);

	Account_information* consult_account(char*, char*);

	bool block_unblock_account(char*, char*, bool);

	bool deposit(char*, int);

	int withdrawal(char*, int, char*);

	bool transfer_money(char*, char*, char*, Bank* banco, int);	

	bool id_account_exist(char*);

	bool id_client_exist(char*);
	
	BankAccount* select_count(char*);

	BankClient* select_client(char*);
	
	BankClient* select_client_lastName(char*);

	int* get_how_accounts();

	void fail_account();
};
	
#endif


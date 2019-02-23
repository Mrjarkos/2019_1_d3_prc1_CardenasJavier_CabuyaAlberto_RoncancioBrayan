#include "Bank.h"

class Bank
{
	char* name;
	BankClient[]* list_clients;
	BankAccount[]* list_accounts;

public:
	Bank();
	~Bank();

	char[] get_name(){
		return name;
	}

	bool create_client(){}

	bool update_client(){}

	BankClient consult_client(){}

	bool create_account(){}

	BankAccount consult_account(){}

	bool block_unblock_account(){}

	bool deposit(){}

	int withdrawal(){}

	bool transfer_account(){}	



};
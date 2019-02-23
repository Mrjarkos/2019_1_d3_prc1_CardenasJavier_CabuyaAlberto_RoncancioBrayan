
#ifndef BANK_H

#define BANK_H

#include "BankAccount.h"
#include "BankClient.h"

	char* name;
	BankClient[]* list_clients;
	BankAccount[]* list_accounts;

	bool create_client();

	bool update_client();

	BankClient consult_client();

	bool create_account();

	BankAccount consult_account();

	bool block_unblock_account();

	bool deposit();

	int withdrawal();

	bool transfer_account();	

#endif


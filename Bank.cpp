#include "Bank.h"


	Bank::Bank(char* name, BankClient** list_clients, BankAccount** list_accounts){
		int n = 20;
		initial_accounts = n;
		initial_clients = n;

		this->name = name;

		if (list_accounts!=NULL){
			this->list_accounts = list_accounts;
			How_many_account = sizeof(list_accounts)/sizeof(*list_accounts);
		}
		else{
			How_many_account = 0;
			this->list_accounts = new BankAccount*[initial_accounts];	
			}


		if (list_clients!=NULL){
			this->list_clients = list_clients;
			How_many_client = sizeof(list_clients)/sizeof(*list_clients);
		}
		else{
			How_many_client = 0;
			this->list_clients = new BankClient*[initial_accounts];	
			}
	};

	char* Bank::get_name(){
		return name;
	}

	bool Bank::create_client(){
	}

	bool Bank::update_client(){}

	BankClient* Bank::consult_client(){}

	bool Bank::create_account(int id_account, char* key, BankClient* cliente, int initial_value){

		BankAccount* account = new BankAccount(id_account, key, cliente, initial_value);
		How_many_account++;

		if(id_account_exist(id_account)){
			return false;
		}

		if(How_many_account >= initial_accounts-1){
			initial_accounts+=20;
			BankAccount** list_accounts_aux = list_accounts;
			delete list_accounts;
			list_accounts = new BankAccount*[initial_accounts];
			list_accounts = list_accounts_aux;
			delete list_accounts_aux;
		} 

		list_accounts[How_many_account] = account; 
		return true;

	}

 	Account_information* Bank::consult_account(int id_account, char* key){
			Account_information* account;
			BankAccount *cuenta;

			cuenta = select_count(id_account);

			if(cuenta!=NULL){
				if(cuenta->CheckKey(key)==true){
					account->id_account = id_account;
					account->state = cuenta->ConsultState();						
					account->balance = cuenta->ConsultBalance();
					account->cliente = cuenta->ConsultUser();
					return account;
				}
			}

			return NULL;
	}

	bool Bank::block_unblock_account(int id_account, char* key, bool block){
		BankAccount* account;
		account = select_count(id_account);
		if(account!=NULL){
			if(account->CheckKey(key)){
				if(block){
					account->Block();
				}
				else{
					account->UnBlock();
				}	
				return true;
			}
		}
		return false;
	}

	bool Bank::deposit(int id_account, int amount){
		BankAccount* cuenta;
		cuenta = select_count(id_account);

		if(cuenta != NULL){
			cuenta->deposit(amount);
			return true;
			
		}
		return false;	
	}

	int Bank::withdrawal(int id_account, int amount, char* key){
		BankAccount* cuenta;
		cuenta = select_count(id_account);
		if(cuenta != NULL){
			if(cuenta->CheckKey(key)){
				cuenta->Retirar(amount);
				return cuenta->ConsultBalance();
			}
		}
		return -1;

	}

	bool Bank::transfer_money(int id_account1, char* key1, int id_account2, int amount){
		BankAccount* cuenta1;
		BankAccount* cuenta2;
		cuenta1 = select_count(id_account1);
		cuenta2 = select_count(id_account2);
			if(cuenta1 == NULL || cuenta2 == NULL){
				return false;
			}
			else{
				if(cuenta1->CheckKey(key1)){
					cuenta1->Retirar(amount);
					cuenta2->deposit(amount);
					return true;	
				}
			
				return false;
			}
	}	

	bool Bank::id_account_exist(int id_account){
		for(int i=0; i<How_many_account; i++){
			if(id_account == list_accounts[i]->accountnumber){
				return true;
			}
		}
	return false;
	}

	BankAccount* Bank::select_count(int id_account){
		if(id_account_exist(id_account)){
			for(int i=0; i<How_many_account; i++){
				if (id_account==list_accounts[i]->accountnumber)
				{
					return list_accounts[i];
				}
			}
		}
		else{
			return NULL;
		}
	}

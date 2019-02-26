#include "Bank.h"

class Bank
{
	char* name;
	BankClient[]* list_clients;
	BankAccount[]* list_accounts;
	int How_many_client; //Me indica cuantos clientes hay
	int How_many_account; //Me indica cuantas cuentas hay
	int initial_accounts; // con cuantas cuentas maximo puedo empezar
	int initial_clients; // con cuantas cuentas maximo puedo empezar

public:
	Bank(char* _name, BankClient[]* _list_clients, BankAccount[]* _list_accounts){
		int n = 20;
		initial_accounts = n;
		initial_clients = n;

		name = _name;

		if (_list_accounts!=NULL){
			list_accounts = _list_accounts;
			How_many_account = sizeof(list_accounts)/sizeof(*list_accounts);
		}
		else{
			How_many_account = 0;
			list_accounts = new BankAccount[initial_accounts]*;	
			}


		if (_list_clients!=NULL){
			list_clients = _list_clients;
			How_many_client = sizeof(list_clients)/sizeof(*list_clients);
		}
		else{
			How_many_client = 0;
			list_clients = new BankAccount[initial_accounts]*;	
			}

	};

	~Bank();

	char* get_name(){
		return name;
	}

	bool create_client(){
		BankClient ciente = new BankClient();
	}

	bool update_client(){}

	BankClient consult_client(){}

	bool create_account(int id_account, bool accstate, char* key, int* balance, BankClient* cliente){

		BankAccount account = new BankAccount(id_account, accstate, key, balance, cliente);
		How_many_account++;

		if(id_account_exist(id_account)){
			return false;
		}

		if(How_many_account >= initial_accounts-1){
			initial_accounts+=20;
			BankAccount[]* list_accounts_aux = list_accounts;
			free(list_accounts);
			list_accounts = new BankAccount[initial_accounts]*;
			list_accounts = list_accounts_aux;
			free(list_accounts_aux);
		} 

		list_accounts[How_many_account] = account; 
		return true;

	}

	Account_information consult_account(int id_account, char* key){
			Account_information account;

			for(int i=0; i<How_many_account; i++){
				if(id_account == BankAccount[i].Accountnumber){
					if(account.CheckKey(key)){
					account.state = BankAccount[i].ConsultState();						
					account.balance = BankAccount[i].ConsultBalance();
					account.cliente = BankAccount[i].ConsultUser();
					}

			
				}
			}

			return account;
	}

	bool block_unblock_account(bool block, BankAccount* account, char* key){
		if(account.CheckKey(key)){
			if(block){
				account.Block();
			}
			else{
				account.Unblock();
			}	
			return true;
		}
		return false;
	}

	bool deposit(int id_account, int amount){


		

		account.deposit();
	}

	int withdrawal(){}

	bool transfer_account(){}	

	bool id_account_exist(int id_account){

		for(int i=0; i<How_many_account; i++){
			if(id_account == BankAccount[i].Accountnumber){
				return true;
			}
		}
	return false;
	}

};
#include "Bank.h"
#include <string>


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

	bool Bank::create_client(char* firstName, char* lastName, char* id, int age, char** accounts){ //si la cuenta ya esta creada
		BankClient* cliente = new BankClient(firstName, lastName, id, age, accounts);

		How_many_client++;

		if(id_client_exist(id)){
			std::cout << "\nEl cliente ya existe" << std::endl;
			return false;
		}
		if(accounts == NULL){
			return false;
		}

		if(How_many_client >= initial_accounts-1){
			initial_clients+=20;
			BankClient** list_clients_aux = list_clients;
			delete list_clients;
			list_clients = new BankClient*[initial_clients];
			list_clients = list_clients_aux;
			delete list_clients_aux;
		} 

		for(int i=0; i<(sizeof(accounts)/sizeof(*accounts)); i++){
			cliente->Add_account(accounts[i]);
		} 

		list_clients[How_many_client] = cliente;
		return true;
	}

	bool Bank::create_client(char* firstName, char* lastName, char* id, int age, char* id_account, char* key, int initial_value){
	
		BankClient* cliente = new BankClient(firstName, lastName, id, age, NULL);

		bool clients_id=id_client_exist(id);
		
		if(clients_id){
			std::cout << "\nEl cliente ya existe" << std::endl;
			return false;
		}

		if(How_many_client > initial_accounts){
			initial_clients+=20;
			BankClient** list_clients_aux = list_clients;
			delete list_clients;
			list_clients = new BankClient*[initial_clients];
			list_clients = list_clients_aux;
			delete list_clients_aux;
					
		} 
		bool a = create_account(id_account, key, cliente, initial_value);
		 if(!a){
		 	return false;
		 }
		cliente->Add_account(list_accounts[How_many_account-1]->accountnumber);//problemas
		
		list_clients[How_many_client] = cliente;
		How_many_client++;
		return true;
	}

	bool Bank::update_client(BankClient* cliente, char* firstName, char* lastName, char* id, int age){
		cliente->Update_data(firstName, lastName, id, age, cliente->get_accounts());
		return true;
	}

	Client_information* Bank::consult_client(char* id_client){
		Client_information* client = new Client_information();
			BankClient* cliente;
			BankAccount** list_cuentas;
			
			cliente = select_client(id_client);

			if(cliente!=NULL){
					client->firstName = cliente->get_firstName();
					client->lastName = cliente->get_lastName();
					client->id_client = cliente->get_id();
					client->nAccount = cliente->nAccounts();
					char** cuentas = cliente->get_accounts();

					list_cuentas = new BankAccount*[sizeof(cuentas)/sizeof(*cuentas)];

					for(int i=0; i<sizeof(cuentas)/sizeof(*cuentas);i++){
						list_cuentas[i] = select_count(cuentas[i]);
					}

					client->accounts = list_cuentas;

					return client;
				
			}

			return NULL;
	}

	bool Bank::create_account(char* id_account, char* key, BankClient* cliente, int initial_value){

		BankAccount* account = new BankAccount(id_account, key, cliente->id_client, initial_value);

		bool accounts_id=id_account_exist(id_account);
		if(accounts_id){   
			return false;
		}

		if(How_many_account > initial_accounts){
			initial_accounts+=20;
			BankAccount** list_accounts_aux = list_accounts;
			delete list_accounts;
			list_accounts = new BankAccount*[initial_accounts];
			list_accounts = list_accounts_aux;
			delete list_accounts_aux;
		} 

		list_accounts[How_many_account] = account; 
		How_many_account++;
		return true;

	}

 	Account_information* Bank::consult_account(char* id_account, char* key){
			Account_information* account = new Account_information();
			BankAccount *cuenta;

			cuenta = select_count(id_account);

			if(cuenta!=NULL){
				if(cuenta->CheckKey(key)==true){
					account->id_account = id_account;
					account->state = cuenta->ConsultState();						
					account->balance = cuenta->ConsultBalance();
					account->cliente = select_client(cuenta->ConsultUser());
					return account;
				}
			}

			return NULL;
	}

	bool Bank::block_unblock_account(char* id_account, char* key, bool block){
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

	bool Bank::deposit(char* id_account, int amount){
		BankAccount* cuenta;
		cuenta = select_count(id_account);

		if(cuenta != NULL){
			cuenta->deposit(amount);
			return true;
			
		}
		return false;	
	}

	int Bank::withdrawal(char* id_account, int amount, char* key){
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

	bool Bank::transfer_money(char* id_account1, char* key1, char* id_account2, Bank* banco, int amount){
		BankAccount* cuenta1;
		BankAccount* cuenta2;
		cuenta1 = select_count(id_account1);
		cuenta2 = banco->select_count(id_account2);
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

	bool Bank::id_account_exist(char* id_account){
		for(int i=0; i<How_many_account; i++){
			char* a = list_accounts[i]->accountnumber;
			if((*id_account) == (*a)){
				return true;
			}
		}
	return false;
	}


	bool Bank::id_client_exist(char* id_client){

		for(int i=0; i<How_many_client; i++){
			
			char* a = list_clients[i]->get_id();
				int this_n = sizeof(a)/sizeof(*a);
				std::cout << "n" << this_n << std::endl;

				int n = sizeof(id_client)/sizeof(*id_client);
				std::cout << "n" << n << std::endl;
				if (n==this_n){
					for (int i = 0; i < n; ++i)
					{	
						std::cout << "a[i] "<< a[i] << std::endl;
						std::cout << "id_client[i] " << id_client[i] << std::endl;
						if(a[i]!=id_client[i]){
							return false;
						}
					}
					return true;
			}
		}
	return false;
	}

	BankAccount* Bank::select_count(char* id_account){
		if(id_account_exist(id_account)){
			for(int i=0; i<How_many_account; i++){
				char* a = list_accounts[i]->accountnumber;
				int this_n = sizeof(a)/sizeof(*a);
				int n = sizeof(id_account)/sizeof(*id_account);
				if (n==this_n){
					for (int i = 0; i < n; ++i)
					{	
						if(a[i]!=id_account[i]){
							return NULL;
						}
					}
					return list_accounts[i];
				}
				
			}
		}
		else{
			return NULL;
		}
	}	

	BankClient* Bank::select_client(char* id_client){

		if(id_client_exist(id_client)){
			for(int i=0; i<How_many_client; i++){
				char* a = list_clients[i]->get_id();
				int this_n = sizeof(a)/sizeof(*a);
				int n = sizeof(id_client)/sizeof(*id_client);
				if (n==this_n){
					for (int i = 0; i < n; ++i)
					{	
						if(a[i]!=id_client[i]){
							return NULL;
						}
					}
					return list_clients[i];
				}
			}
		}
		else{
			return NULL;
		}
	}

	

	BankClient* Bank::select_client_lastName(char* lastName){

		if(id_client_exist(lastName)){
			for(int i=0; i<How_many_client; i++){
				if (lastName==list_clients[i]->get_lastName())
				{
					return list_clients[i];
				}
			}
		}
		else{
			return NULL;
		}
	}

	int Bank::get_how_accounts(){
		//How_many_account++;
		return How_many_account;
	}


	void  Bank::fail_account() {
		//How_many_account--;
	}
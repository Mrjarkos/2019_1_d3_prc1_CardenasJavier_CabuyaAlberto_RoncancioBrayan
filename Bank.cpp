#include "Bank.h"
#include <string>
#include <exception>
using namespace std;

class myexception: public exception{
  virtual const char* what() const throw()
  {
    return "Banco ya creado";
  }
} CreatedBank;
	Bank::Bank(char* name, BankClient** list_clients, BankAccount** list_accounts){
		memoryexist= shm_open(name, O_RDWR|O_CREAT|O_EXCL, 0666);
		if (memoryexist==-1)
		{
			throw CreatedBank;
		}
		ftruncate(memoryexist, size);
		pointmem= mmap(0, size, PROT_WRITE, MAP_SHARED, memoryexist, 0);
		int n = 20;
		int m;
		initial_accounts = n*10;
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
			m = sizeof(list_clients) / sizeof(*list_clients);
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
			this->list_clients = new BankClient*[initial_clients];
			this->list_clients = list_clients_aux;
			delete list_clients_aux;
		} 

		for(int i=0; i<(sizeof(accounts)/sizeof(*accounts)); i++){
			cliente->Add_account(accounts[i]);
		} 

		this->list_clients[How_many_client] = cliente;
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
			this->list_clients = new BankClient*[initial_clients];
			this->list_clients = list_clients_aux;
			delete list_clients_aux;
					
		} 
		bool a = create_account(id_account, key, cliente, initial_value);
		 if(!a){
		 	return false;
		 }

		//problemas
		
		this->list_clients[How_many_client] = cliente;
		this->How_many_client++;
		return true;
	}

	bool Bank::update_client(BankClient* cliente, char* firstName, char* lastName, char* id, int age){
		cliente->Update_data(firstName, lastName, id, age, cliente->get_accounts());
		for (int i = 0; i < cliente->nAccounts(); i++) {
			BankAccount* cuenta = select_count(cliente->get_accounts()[i]);
			cuenta->ChangeClient(id);
		}
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
					client->accounts = cliente->get_accounts();
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
			this->list_accounts = new BankAccount*[initial_accounts];
			this->list_accounts = list_accounts_aux;
			delete list_accounts_aux;
		} 

		list_accounts[How_many_account] = account;
		cliente->Add_account(account->accountnumber);

		this->How_many_account++;
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
					std::cout << "Cuenta Bloqueada" << std::endl;
				}
				else{
					account->UnBlock();
					std::cout << "Cuenta Desbloqueada" << std::endl;
				}	
				return true;
			}
		}
		return false;
	}

	bool Bank::deposit(char* id_account, int amount){
		BankAccount* cuenta;
		cuenta = select_count(id_account);
		bool state_ac=cuenta-> ConsultState(); 
		if(!state_ac){
			std::cout << "Cuenta bloqueada" << std::endl;
			return false;
		}
		else{
		if(cuenta != NULL){
			cuenta->deposit(amount);
			return true;
			
		}
	}
		return false;	
	}

	int Bank::withdrawal(char* id_account, int amount, char* key){
		BankAccount* cuenta;
		cuenta = select_count(id_account);
		bool state_ac=cuenta-> ConsultState(); 
		if(!state_ac){
			std::cout << "Cuenta bloqueada" << std::endl;
			return -1;
		}
		else{
		if(cuenta != NULL){
			if(cuenta->CheckKey(key)){
				if (cuenta->Retirar(amount)) {
					return cuenta->ConsultBalance();
				}
			}
		}
	}
		return -1;

	}

	bool Bank::transfer_money(char* id_account1, char* key1, char* id_account2, Bank* banco, int amount){
		BankAccount* cuenta1;
		BankAccount* cuenta2;
		cuenta1 = select_count(id_account1);
		cuenta2 = banco->select_count(id_account2);
		bool state_ac=cuenta1-> ConsultState(); 
		bool state_ac2=cuenta2-> ConsultState(); 	
		if(!state_ac|| !state_ac2){
			std::cout << "Cuenta bloqueada" << std::endl;
			return false;
		}
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
		int n = LongitudCadena(id_account);
		int q;
		for (int i = 0; i < How_many_client; i++) {
			q = 0;
			char* a = list_accounts[i]->accountnumber;
			int this_n = LongitudCadena(a);

			if (n == this_n) {
				for (int j = 0; j < n; ++j)
				{
					if (a[j] == id_account[j]) {
						q++;
					}
				}
				if (q == n) {
					return true;
				}
			}
		}
		return false;
	}
	


	bool Bank::id_client_exist(char* id_client){
		int n = LongitudCadena(id_client);
		int q;
		for(int i=0; i<How_many_client; i++){
			q = 0;
			char* a = list_clients[i]->get_id();
				int this_n = LongitudCadena(a);

				if (n==this_n){
					for (int j = 0; j < n; ++j)
					{	
						if(a[j]==id_client[j]){
							q++;
						}
					}
					if (q == n) {
						return true;
					}
			}
		}
	return false;
	}

	BankAccount* Bank::select_count(char* id_account){
		if (id_account_exist(id_account)) {
			int n = LongitudCadena(id_account);
			int q;
			for (int i = 0; i < How_many_client; i++) {
				q = 0;
				char* a = list_accounts[i]->accountnumber;
				int this_n = LongitudCadena(a);

				if (n == this_n) {
					for (int j = 0; j < n; ++j)
					{
						if (a[j] == id_account[j]) {
							q++;
						}
					}
					if (q == n) {
						return list_accounts[i];
					}
				}
			}
			return NULL;
		}
		else{
			return NULL;
		}
	}	

	BankClient* Bank::select_client(char* id_client){
		if (id_client_exist(id_client)) {
			int n = LongitudCadena(id_client);
			int q;
			for (int i = 0; i < How_many_client; i++) {
				q = 0;
				char* a = list_clients[i]->id_client;
				int this_n = LongitudCadena(a);

				if (n == this_n) {
					for (int j = 0; j < n; ++j)
					{
						if (a[j] == id_client[j]) {
							q++;
						}
					}
					if (q == n) {
						return list_clients[i];
					}
				}
			}
			return NULL;
		}
		else {
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
		return NULL;
	}

	int Bank::get_how_accounts(){
		//How_many_account++;
		return How_many_account;
	}


	void  Bank::fail_account() {
		//How_many_account--;
	}

	int Bank::LongitudCadena(char *a) {
		char *p, *q;
		p = a;
		q = a;
		while (*q) q++;
		return q - p;
	}
	int Bank::TransferinterBank(int money, char * name,char * cuenta){
				std::cout<<name<<std::endl;
				int memory_exists;
				void* memorypoint;
				std::cout<<name<<std::endl;
				Bank* banco2= new Bank(name, NULL,NULL);
				std::cout<<name<<std::endl;
				memory_exists= shm_open(name, O_RDWR, 0666);
				printf("exito" );
				if (memory_exists==-1)
				{
					return -1; //-1 error banco no encontrado	
				}
				ftruncate(memory_exists, 400);
				printf("exito" );
				memorypoint= mmap(0,400, PROT_WRITE, MAP_SHARED, memory_exists,0);
				printf("exito%s", memorypoint);
				banco2= (Bank *) memorypoint;
				bool status;
				if (banco2->get_how_accounts()!=0)
				{
					status=banco2->	deposit(cuenta, money);
					if(!status){
						return -3; // error de la cuenta bloqueada o inexistente
					}
					else {
						memorypoint= banco2;
						sprintf((char *)memorypoint, "%s", banco2);
						return 0;
					} //exito
				}
				else {return -2;} // -2 error cuenta en banco no encontrada
	}
	
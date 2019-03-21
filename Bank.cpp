#include "Bank.h"
#include <string.h>
#include <exception>
using namespace std;

class myexception: public exception{
  virtual const char* what() const throw()
  {
    return "Banco ya creado";
  }
} CreatedBank;

	Bank::Bank(char* name, BankClient** list_clients, BankAccount** list_accounts){
		size= 4096;
		memoryexist= shm_open(name, O_RDWR|O_CREAT|O_EXCL, 0666);
		Transfer_info* memtrnasfer;
		if (memoryexist==-1)
		{
			throw CreatedBank;
		}
		ftruncate(memoryexist, size);
		pointmem= mmap(0, size, PROT_WRITE, MAP_SHARED, memoryexist, 0);
		memtrnasfer=(Transfer_info *)pointmem;
		memtrnasfer[0].nAccount=NULL;
		memtrnasfer[0]. originBank= NULL;
		memtrnasfer[0].money= 0;
		memtrnasfer[0].readstate=0;
		printf("%d\n", memtrnasfer[0].readstate);
		close(memoryexist);
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
	Bank::~Bank(){
		shm_unlink(name);
	}

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

	bool Bank::update_client(BankClient* cliente, char *firstName, char *lastName, char* id, int age){
		cliente->Update_data(firstName, lastName, id, age, cliente->get_accounts());
		for (int i = 0; i < cliente->nAccounts(); i++) {
		BankAccount* cuenta = select_count(cliente->get_accounts()[i]);
		cuenta->ChangeClient(id);
		}
		return true; //modificar para que guarde 
	}

	Client_information* Bank::consult_client(char* id_client){
		Client_information* client = new Client_information();
			BankClient* cliente;
			BankAccount** list_cuentas;
			cliente=select_client(id_client);

			if(cliente!=NULL){
					client->firstName = cliente->get_firstName();
					client->lastName = cliente->get_lastName();
					client->id_client = cliente->get_id();
					client->nAccount = cliente->nAccounts();
					client->accounts = cliente->get_accounts(); //mirar en get accounts donde no esta guardando
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
			printf("Exito" );
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

	int Bank::TransferinterBank(int money, char * nombre,char * cuenta, char * cuentaorig, char * key ){
				std::cout<<nombre<<std::endl;
				int memory_exists2;
				void* memorypoint2;
				Transfer_info* data; 
				BankAccount* cuenta1;
				//printf("%s\n", cuentaorig);
				cuenta1 = select_count(cuentaorig);
				printf("Exito" );
				if (cuenta1==NULL)
				{
					return -3;
				}
				bool state_ac=cuenta1-> ConsultState(); 
				//cout<<"Exito"<<endl;
				if(!state_ac){
					std::cout << "Cuenta bloqueada" << std::endl;
					return -2;//-1 cuenta bloqueada
				}
				else{
						if(cuenta1->CheckKey(key)){
							cuenta1->Retirar(money);
						}
					else{
							return -4;//contraseña incorrecta
						}
					}
				printf("Exito");
				memory_exists2= shm_open(nombre, O_RDWR, 0666);//lo hace "bien" 
				if (memory_exists2==-1)
				{
					return -1; //-1 error banco no encontrado	
				}
				printf("Exito" );
				ftruncate(memory_exists2, size);
				printf("Exito" );
				memorypoint2= mmap(0, size, PROT_READ, MAP_SHARED, memory_exists2, 0);
				
				memorypoint2= mmap(0, size, PROT_WRITE, MAP_SHARED, memory_exists2, 0);				
				char * write= (char *)memorypoint2;
				sprintf(write, "%s;\n", cuenta);
				sprintf(write, "%d;\n",money);
				//printf("%s\n", (char *)memorypoint2 );
				//if (memorypoint2!=NULL){
				//	return -5; // Banco ocupado con otra transacción
				//}

				/*data= (Transfer_info *)memorypoint2;
				//printf("%d\n",data[0].readstate);
				printf("nove");
				if (data[0].readstate==0)
				{
					printf("readstate=0");
					return 0;
				}
				else if (data[0].readstate!=0){
					close(memory_exists2);
					return -5; // Banco ocupado con otra transacción
				}

				memorypoint2= mmap(0, size, PROT_WRITE, MAP_SHARED, memory_exists2, 0);				
				data= (Transfer_info *)memorypoint2;
				//cout<<"Exito"<<endl;
				// primer item memory pont nobre banco a transferir, segundo cuenta, tercero cantidad de dinero
				data[0].money= money;
				//cout<<"Exito"<<endl;
				data[0].originBank= nombre;				
				//cout<<"Exito"<<endl;
				data[0].nAccount= cuenta;
				//cout<<"Exito"<<endl;
				data[0].readstate=1;
				//printf("%s\n", (char *)memorypoint2);
				//cout<<(char *)memorypoint2<<endl;
				//int statussave= msync(memorypoint2, size,  MS_SYNC)
				//close(memory_exists2);
				//int memory3= shm_open(nombre, O_RONLY, 0666);
				//void * kks;
				//kks=mmap(0, size, PROT_READ, MAP_SHARED, memory3, 0);
				//printf("%s\n", (char *)memorypoint2);
				//cout<<(char *)kks<<endl;*/
				close(memory_exists2);
				return 0;
	}
	int Bank::readmem(char* nombre){
		int memory3= shm_open(nombre, O_RDWR, 0666);
		void * pointmem3;
		Transfer_info* datin;
		Transfer_info* datout;
		pointmem3=mmap(0, size, PROT_READ, MAP_SHARED, memory3, 0);
		datin=(Transfer_info *)pointmem3;
		pointmem3= mmap(0,size, PROT_WRITE, MAP_SHARED, memory3, 0);
		datout=(Transfer_info *)pointmem3;
		if (datin[0].readstate==1)
		{
			return 1; //indica que el otro banco no ha refrescado sus transferencias entrantes
		}
		else if(datin[0].readstate==0){
			datout[0].readstate=0;
			return 0; //se realizo correctamente la transferencia
		}
		else if(datin[0].readstate==2){
			datout[0].readstate=0;
			return -1; //cuenta destino bloqueada
		}
		else if (datin[0].readstate==3){
			datout[0].readstate=0;
			return-2;//cuenta destino inexistente
		}
	}
	void Bank::receivetransfer(){
			void * pointmem2;
			Transfer_info* datin;
			Transfer_info* datout;
			BankAccount* editedacount;
			printf("Exito\n");
			int memoryexist2= shm_open(name, O_RDWR, 0666);
			pointmem2= mmap(0, size, PROT_READ, MAP_SHARED, memoryexist2, 0);
			char*datinn= (char *)pointmem2;
			printf("Exito\n");
			printf("%s\n",datinn );
			//printf("%s\n", datout[0].readstate);
			//void* pointmem3;
			//int memoryexist3=shm_open(name, O_RDWR,0666);
			pointmem2= mmap(0,size, PROT_WRITE,MAP_SHARED, memoryexist2, 0);
		/*	printf("Exito\n");
			
			
			
		
				datout=(Transfer_info *)pointmem2;
				printf("Exito\n");
				//printf("%s",(char *)pointmem2);
				//printf("%s\n",datin[0].nAccount );
				if(datout[0].readstate!=0){
					printf("Exito\n");
					editedacount=select_count(datin[0].nAccount);
					printf("Exito\n");
					if (editedacount==NULL){
						datout[0].readstate= 3;
						datout[0].nAccount= NULL;
						datout[0].originBank= NULL;
						datout[0].money= 0;
						printf("Exito\n");
					}
					else{
						bool state_ac= editedacount->ConsultState();
						if (!state_ac){
							datout[0].readstate= 2;
							datout[0].nAccount= NULL;
							datout[0].originBank= NULL;
							datout[0].money= 0;
							printf("Exito\n");
						
						}
						else{
							editedacount->deposit(datin[0].money);
							datout[0].readstate=0;
							datout[0].nAccount= NULL;
							datout[0].originBank= NULL;
							datout[0].money= 0;
							printf("Exito\n");
						}
					}
				}*/
			
	}
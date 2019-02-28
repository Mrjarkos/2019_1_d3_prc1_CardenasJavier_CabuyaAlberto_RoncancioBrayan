#include "BankClient.h"
#include "BankAccount.h"

	BankClient::BankClient(char* firstName, char* lastName, char* id, int age, char** accounts){
		Update_data(firstName, lastName, id, age, accounts);
		initial_accounts = 2;
		id_accounts = new char*[initial_accounts];
	}

	void BankClient::Update_data(char* firstName, char* lastName, char* id, int age, char** accounts){
		this->firstName=firstName;
		this->lastName = lastName;
		this->age=age;
		this->id_client=id_client;
		this->id_accounts = accounts;
			if(id_accounts!=NULL){
				how_many_accounts = sizeof(id_accounts)/sizeof(id_accounts);
			}
			else{
				how_many_accounts = 0;
			}
	}

	void BankClient::Add_account(char* id_account){
		how_many_accounts++;

		if(how_many_accounts >= initial_accounts-1){
			initial_accounts+=2;
			char** list_accounts_aux = id_accounts;
			delete id_accounts;
			this->id_accounts = new char*[initial_accounts];
			this->id_accounts = list_accounts_aux;
			delete list_accounts_aux;
		} 

		id_accounts[how_many_accounts] = id_account; 
	}

	bool BankClient::Delete_account(char* id_account){
		
			for(int i=0; i<how_many_accounts; i++){
				if (id_account==this->id_accounts[i])
				{
					delete id_accounts[i];
					return true;
				}
			}
			return false;
	}

	char* BankClient::get_firstName(){
		return firstName;
	}

	char* BankClient::get_lastName(){
		return lastName;
	}

	char* BankClient::get_id(){
		return id_client;
	}

	char** BankClient::get_accounts(){
		return id_accounts;
	}
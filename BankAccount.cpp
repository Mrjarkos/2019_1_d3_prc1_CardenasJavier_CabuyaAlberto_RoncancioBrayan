
#include "BankAccount.h" 
#include "BankClient.h"

	BankAccount::BankAccount(char* accountnumber, char* key, char* id_client, int initial_value){
		this->accountnumber = accountnumber;
		accState = true;
		this->key = key;
		balance = initial_value;
		this->id_client = id_client;
	} 

	void BankAccount::Block(){
		accState = false;
	}

	void BankAccount::UnBlock(){
		accState = true;
	}

	bool BankAccount::CheckKey(char* key){
		if(this->key == key){
			return true;
		}
		else{
			return false;
		}
	}

	void BankAccount::deposit(int amount){
		balance += amount;
	}

	bool BankAccount::Retirar(int amount){				//Resta al activo y compara si hay deuda	
		if(balance-amount<0){
			return false;
		}
		else{
			balance-=amount;
			return true;
		}
	}

	bool BankAccount::ConsultState(){
		return this->accState;
	}

	int BankAccount::ConsultBalance(){
		return this->balance;
	}

	char* BankAccount::ConsultUser(){
		return this->id_client;
	}

	void BankAccount::ChangeClient(char* client){
		this->id_client = id_client;
	}

	bool BankAccount::updateKey(char* key){

		if(sizeof(key)/sizeof(*key)!=4){
			return false;
		}else{
			 this->key = key;
			return true;	
		}
		
	}
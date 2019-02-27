
#include "BankAccount.h" 

class BankAccount(){

	bool AccState;
	char*  Key;
 	Balance balance;
	char* Owner;

public: 
	int Accountnumber; 

	BankAccount(int accountnumber, bool accstate, char* key, char* client, int initial_value){
		Accountnumber= accountnumber;
		AccState=accstate;
		Key= key;
		balance.Activos=initial_value;
		balance.Debe=0;
		balance.Saldo = balance.Activos-balance.Debe;
		Owner= client;
	} 

	void Block(){
		AccState= false;
	}

	void UnBlock(){
		AccState= true;
	}

	bool CheckKey(char* Keyint){
		char* Keyuser = &Key;
		if(Keyuser == Keyint){
			return true;
		}
		else{
			return false;
		}

	}

	void deposit(int moneyVal){
		if(balance.deuda>0){
			balance.deuda-= moneyVal;
			if(balance.deuda<0){
				balance.Activos= (-1)*(balance.deuda);
			}
		}
		else{
			balance.Activos+= moneyVal;
		}			//suma al activo de la cuenta lo que se ingresa
}

	void Retirar(int moneyVal){				//Resta al activo y compara si hay deuda
		balance.Activos-= moneyVal;
		if(balance.Activos<=0){ 
			balance.Debe+=(-1)*(balance.Activos);
			balance.Activos=0;
		 }
	}

	bool ConsultState(){
		bool estado = AccState;
		return estado;
	}

	Balance* ConsultBalance(){
		Balance* Balanceclient = &balance;
		Balanceclient*.Saldo = Balanceclient.Activos - Balanceclient.Debe; 
		return Balanceclient;
	}

	char* ConsultUser(){
		char* client = Owner;
		return client;
	}

	void ChangeClient(BankClient* client){
		Client= client;
	}

	void updateKey(char* accountkey){
		char* newKey= accountkey;
		AccState= newKey;
	}



}

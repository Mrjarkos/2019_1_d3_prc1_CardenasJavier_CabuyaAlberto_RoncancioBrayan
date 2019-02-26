#include <iostream>
#include <string.h>
#include "BankClient.h" 
class BankAccount(){


	bool AccState;
	char  Key [4];
struct Valance
 {
 	int  Activos:
 	int Debe; 
 };  
 Valance balance;
	BankClient* Client;
public: 
		int Accountnumber; 
BankAccount( int accountnumber, bool accstate, char* key, Valance* valace, BankClient* client){
	Accountnumber= accountnumber;
	AccState=accstate;
	Key= key;
	balance= valace;
	Client= client;
} 

void Block(){
	AccState= false;
}
void UnBlock(){
	AccState= true;
}
bool CheckKey(char* Keyint){
	char* Keyuser= &Key;
	if(Keyuser== Keyint){
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
	if(balance.Activos<0){ 
		balance.Debe+=(-1)*(balance.Activos);
		balance.Activos=0;
	 }
}
bool ConsultState(){
	bool estado= AccState;
	return estado;
}
Valance* ConsultBalance(){
	Valance* Balanceclient  = &balance;
	return Balanceclient;
}
BankClient* ConsultUser(){
	BankClient* client= Client;
	return client;
}
void ChangeClient(BankClient* client){
	Client= client;
}

void updateKey(char* accountkey ){
	char newKey [4]= accountkey;
	AccState= newKey;
}



}


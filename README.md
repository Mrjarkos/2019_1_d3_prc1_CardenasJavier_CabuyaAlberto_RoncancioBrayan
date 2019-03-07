# 2019_1_d3_prc1_CardenasJavier_CabuyaAlberto_RoncancioBrayan

#Laboratorio 1 banco
A continuación se desarrolla una breve explicación de cada una de las clases,
y sus métodos, utilizados para el desarrollo del laboratorio.

##BankClient
Esta clase de BankClient, como su nombre lo indica representa los métodos 
y propiedades que tiene el cliente del banco, estos se pueden encontrar de
manera reducida en el BankClient.h, como se muestra en este código:
'''
#ifndef BANKCLIENT_H
#define BANKCLIENT_H

#include<iostream>
#include<string>
#include<stdio.h>

#include "BankAccount.h"

class BankClient
{
		char* firstName;
		char* lastName;
		int age;
		char** id_accounts;
		int how_many_accounts;
		int initial_accounts;

public: 

		char* id_client;
		
	BankClient(char*, char*, char*, int, char**);

	void Update_data(char*, char*, char*, int, char**);

	void Add_account(char*);

	bool Delete_account(char*);

	char* get_firstName();

	char* get_lastName();

	char* get_id();

	char** get_accounts();

	int nAccounts();

};

#endif'''
Donde se decidió hacer las propiedades privadas, para protegerlas de cambios
no deseados, y se puede observar que basicamente las propiedades que se tienen,
son para consultar y editar las propiedades de cliente, se puede observar que 
cliente, no necesariamente depende de cuenta, pero para la aplicación si 
debido a que para crear un cliente, este debe tener una cuenta, o si no, no 
seria cliente, cabe resaltar que en el BankClient.cpp, solo hay que incluir la libreria BankClient.h, debido a que todas las otras ya se incluyeron ahi.

##BankAccount
En esta clase se encuerntra descrito, las propiedades y métodos de una cuenta
creada en el banco, al igual que en la clase anterior, las propiedades estan privadas, para protejerlas, y basicamente los métodos solo sirven de para
consultar, o editar las propiedades de la  cuenta, como se observa en el .h
'''
#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include "BankClient.h"

class BankAccount{

	//Propiedades

	bool accState; //true = activo, false = inactivo
	char* key;
	int balance;
	char* id_client;

public:
	char* accountnumber;

	//Constructor
	BankAccount(char*, char*, char*, int);

	//Metodos
 	void Block();
 	void UnBlock();
 	bool CheckKey(char*);
 	void deposit(int);
 	bool Retirar(int);
 	bool updateKey(char*);
	bool ConsultState();
	int ConsultBalance();
	char* ConsultUser();
	void ChangeClient(char*);
};

#endif
'''

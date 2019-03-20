	#include "Interface.h"
	#include <iostream>
	#include <sstream>
	#include <cstring>
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	using namespace std;

		Interface::Interface(Bank* banco){

				banco1= banco;
		};
		void Interface::mostrar(){

					char optionkey;
					char* key ;
					char* accnum;
					std::cout<<"Bienvenido al banco , ¿que desea hacer?, escoja una de las opciones mostradas\n"<<endl;
					std::cout << "Consultar:\n Nombre del banco: n\n"<<std::endl;
					std::cout << "Cliente : p \n Cuenta : c \n Crear cliente : m \n"<<std::endl;
					std::cout << "Actualizar datos cliente: u\n Crear cuenta: a\n Transferir : t\n"<<std::endl;
					std::cout << "Cambiar estado cuenta: e\n Depositar: d\n Retirar dinero: r \n Transferir a otro banco: k"<<std::endl;
					std::cin>>optionkey ;
					char* id_client = new char [20];
					switch(optionkey){
						
						case 'N':
						case 'n':std::cout<< "Nombre del banco=" << banco1-> get_name()<<"\n"<< endl;
					break;
						case 'K':
						case 'k':{
							char* id_cuenta = new char[20];
							std::cout << "Ingrese el numero de su cuenta" << endl;
							cin >> id_cuenta;
							char* contra = new char[10];
							std::cout << "Ingrese su contraseña" << endl;
							cin >> contra;
							int money = 0;
							int salir=0;
							do{
								try{
							std::cout << "Ingrese el dinero a transferir" << endl;
							cin >> money;
							if(!cin)
								throw 125;
							salir=1;
							}catch(int){
								std::cout<<"\nCantidad no valida"<<std::endl;
								cin.clear();
								cin.ignore();

							}
						}while(salir==0);
							std:cout<<"\nInserte el nombre del banco donde se va a depositar"<<std::endl;
							char* bankname= new char[20];
							cin>> bankname;
							std::cout<< "\nInserte el numero de cuenta a donde va a transferir"<<endl;
							char* accnum2= new char[20];
							cin >> accnum2;
							int transferstate;
							do{
							 transferstate = banco1->TransferinterBank(money, bankname, accnum2,id_cuenta ,contra);
							 
							 if (transferstate==-5)
							 {
							 	char* chekins= new char[20];
							 	std::cout<<"digite cualquier tecla para intentar de nuevo la acción"<<std::endl;
							 	cin>>chekins;
							 }
							}while(transferstate!=-5);

							int kks = banco1-> readmem(bankname);
							//-1 banco no encontrado
							//-2 cuenta bloqueada
							// -3 Dinero unsuficiente inexistente
							//-4 contraseña incorrecta
							//-5 banco ocupado
							if (transferstate==0) {
								std::cout << "\nTransferencia realizada" << endl;
							}
							else { std::cout << "\nError en la transferencia" << endl; }
						
							
							}
						break;
						case 'P':
						case  'p':{ 
							std::cout<< "Inserte numero de identificacion del cliente" << std::endl;
							id_client = new char [20];
							std::cin >> id_client;
							Client_information* cliente = banco1->consult_client(id_client);
							if(cliente==NULL){ std::cout << "Clientre no encontrado" << std::endl; }
							else {
								
								std::cout << "exito" << std::endl;
								std::cout << "Nombre:" << cliente->firstName << std::endl;
								std::cout << "Apellido:" << cliente->lastName << std::endl;
								std::cout << "Id:" << cliente->id_client << std::endl;
								std::cout << "Cuentas:" << endl;
								char* a;
								for (int i = 0; i < cliente->nAccount; i++) {
									a = cliente->accounts[i];
									std::cout << "Numero de Cuenta [" << i << "] = " << a << std::endl;
								}
							}
						}
						break;
						
						case 'C':
						case 'c' :{
							char* id_cuenta = new char[20];
							std::cout << "Ingrese numero de la cuenta" << std::endl;
							cin >> id_cuenta;
							char* contra = new char[10];
							std::cout << "Ingrese su contraseña" << endl;
							cin >> contra;
							Account_information* cuenta = banco1-> consult_account(id_cuenta, contra);
							if (cuenta != NULL) {
								Client_information* cliente = banco1->consult_client(cuenta->cliente->id_client);
								std::cout << "exito" << endl;
								std::cout << "'Propietario:" << cliente->firstName << " " << cliente->lastName << endl;
								std::cout << "Id Cliente:" << cliente->id_client << endl;
								std::cout << "Id Cuenta:" << cuenta->id_account << endl;
								char state[10];
								if (cuenta->state) {
									std::cout << "Estado: Activo" << endl;
								}
								else
								{
									std::cout << "Estado: Inactivo" << endl;
								}
								
								std::cout << "Saldo:" << cuenta->balance << endl;
							}
							else {
								std::cout << "No se encontro la cuenta o contraseña incorrecta" << endl;
							}

						}
						break; 
						
						case 'M':
						case 'm':{ 
							std::cout<< "\nInserte nombre del cliente:"<< endl;
								char*nameclient= new char[15];
								cin>> nameclient+0;
								
								std::cout<< "\nInserte apellido del cliente:"<< endl;
								char*lastnameclient = new char[15];
								cin>> lastnameclient + 0;
							
								std::cout<< "\nInserte numero de identificacion del cliente:"<< endl;
								char* id = new char[20];
								cin>> id + 0;
							
								std::cout<< "\nInserte edad del cliente:"<< endl;
								int age;
								cin>> age;
								
								int a = banco1->get_how_accounts();
								char* id_account = new char[10];
								sprintf(id_account, "%d\0", a);

								std::cout << "\nSe le asigno la cuenta Numero: "<< atoi(id_account) << endl;

								key = ask_key();
								int initial_amount = ask_deposit_money();

								bool state= banco1-> create_client(nameclient, lastnameclient, id, age, id_account, key, initial_amount);
							    if(state){
									std::cout<<"\nCliente creado"<<endl;
							    }
							    else{
									std::cout<<"\nNo se logoro realizar la accion"<<endl;
							    }
							}
						break;
						
						case 'U':
						case 'u':{
							std::cout<< "\nInserte numero de identificacion del cliente:"<< endl;
								id_client = new char[20];
								cin >> id_client;
								bool  clinetstate= banco1->id_client_exist(id_client);
								if(clinetstate){
									BankClient* cliente; 
									Client_information* client; 
									char* tecla = new char[2];
									
										cliente = banco1->select_client(id_client);
										client = banco1->consult_client(id_client);
										std::cout << "Hola " << client->firstName << " " << client->lastName << ".\nQue parametro desea modificar?" << endl;
										std::cout << "1) Nombre" << endl;
										std::cout << "2) Apellido" << endl;
										std::cout << "3) Id" << endl;
										std::cout << "4) Edad" << endl;
										std::cout << "5) Todo" << endl;
										std::cout << "E) Salir" << endl;
										cin >> tecla;
										bool indic = false;
										char* name = new char[20];
										char* lastname = new char[20];
										char* ID = new char[20];
										int age = 0;
										switch (*tecla)
										{
										case '1':
											std::cout << "Inserte su nuevo Nombre" << endl;
											cin >> name;
											indic = banco1->update_client(cliente, name, cliente->get_lastName(), cliente->id_client, cliente->get_age());
											break;
										case '2':
											std::cout << "Inserte su nuevo Apellido" << endl;
											cin >> lastname;
											indic = banco1->update_client(cliente, cliente->get_firstName(), lastname, cliente->id_client, cliente->get_age());
											break;
										case '3': 
											std::cout << "Inserte su nuevo ID" << endl;
											cin >> ID;
											indic = banco1->update_client(cliente, cliente->get_firstName(), cliente->get_lastName(), ID, cliente->get_age());
											id_client = ID;
											break; 
										case '4': 
											std::cout << "Inserte su nueva Edad" << endl;
											cin >> age;
											indic = banco1->update_client(cliente, cliente->get_firstName(), cliente->get_lastName(), cliente->id_client, age);
											break;
										case '5': 
											std::cout << "Inserte su nuevo Nombre" << endl;
											cin >> name;
											std::cout << "Inserte su nuevo Apellido" << endl;
											cin >> lastname;
											std::cout << "Inserte su nuevo ID" << endl;
											cin >> ID;
											std::cout << "Inserte su nueva Edad" << endl;
											cin >> age;
											indic = banco1->update_client(cliente, name, lastname, ID, age);
											id_client = ID;

											break;
										default: 
											std::cout << "Tecla no valida\nPor favor ingrese segun el menu" << endl;
											break;
										}
										if (indic) {
											std::cout << "Datos Actualizados con Exito" << endl;
										}
										else {
											std::cout << "No se ha podido realizar operacion" << endl;
										}
										delete name;
										delete lastname;
										delete ID;
									delete tecla;
								}
								
								else {
									std::cout<<"\ncliente no encontrado"<<endl;
								}

							}
						break;
						
						case 'A':
						case 'a':{
							
							std::cout << "\nInserte numero de identificacion del cliente:" << endl;
							char* client_id = new char[20];
							cin >> client_id;

							bool clientexists= banco1-> id_client_exist(client_id);

							if(clientexists){
									BankClient* clientee= banco1->select_client(client_id);
									int money= ask_deposit_money();
									key= ask_key();
									int a = banco1->get_how_accounts();
									char* id_account = new char[10];
									sprintf(id_account, "%d\0", a);
									std::cout << "Numero de cuenta:" << atoi(id_account) << std::endl;
									bool createclientstate= banco1->create_account(id_account, key, clientee, money );
									 if(createclientstate){
										 std::cout<<"\nCuenta creada"<<endl;
									}
									else {
										 std::cout<<"\nNo se pudo realizar la operacion"<<endl;
									}

							}
							else{
								std::cout << "\nCliente no encontrado" << endl;

								std::cout << "\nCrear Cliente" << endl;

								std::cout<< "\nInserte nombre del cliente:"<< endl;
								char*nameclient= new char[15];
								cin>> nameclient+0;
								
								std::cout<< "\nInserte apellido del cliente:"<< endl;
								char*lastnameclient = new char[15];
								cin>> lastnameclient + 0;

							
								std::cout<< "\nInserte edad del cliente:"<< endl;
								int age;
								cin>> age;
								
								int a = banco1->get_how_accounts();
								char* id_account = new char[10];
								sprintf(id_account, "%d\0", a);

								std::cout << "\nSe le asigno la cuenta Numero: "<< atoi(id_account) << endl;

								key = ask_key();
								int initial_amount = ask_deposit_money();

								bool state= banco1-> create_client(nameclient, lastnameclient, client_id, age, id_account, key, initial_amount);

								if (state) {
									std::cout << "\nCuenta creada" << endl;
								}
								else {
									std::cout << "\nNo se logoro realizar la accion" << endl;
								}
							}
						}
						break;
						
						case 'T':
						case 't':{
							char* id_cuenta = new char[20];
							std::cout << "Ingrese el numero de su cuenta" << endl;
							cin >> id_cuenta;
							char* contra = new char[10];
							std::cout << "Ingrese su contraseña" << endl;
							cin >> contra;
							int money = 0;
							int salir=0;
							do{
								try{
							std::cout << "Ingrese el dinero a transferir" << endl;
							cin >> money;
							if(!cin)
								throw 125;
							salir=1;
							}catch(int){
								std::cout<<"\nCantidad no valida"<<std::endl;
								cin.clear();
								cin.ignore();

							}
						}while(salir==0);
							std::cout<< "\nInserte el numero de cuenta a donde va a transferir"<<endl;
							char* accnum2= new char[20];
							cin >> accnum2;

							bool transferstate = banco1->transfer_money(id_cuenta, contra, accnum2, banco1, money);
							if (transferstate) {
								std::cout << "\nTransferencia realizada" << endl;
							}
							else { std::cout << "\nError en la transferencia" << endl; }
						
						}
							break;

						case 'E':
						case 'e':{
							char* id_cuenta = new char[20];
							std::cout << "Ingrese numero de la cuenta" << endl;
							cin >> id_cuenta;
							char* contra = new char[10];
							std::cout << "Ingrese su contraseña" << endl;
							cin >> contra;
							std::cout << "\nPresione 1 para activar la cuenta y 2 o cualquier tecla para bloquear" << endl;
							char* getstatus = new char[2];
							cin >> getstatus;
							bool status;
							switch (*getstatus)
							{
							case '1':
								status = true;
								break;
							case '2':
								status = false;
								break;
							default:
								status=false;
								break;
							}
							if (status != NULL) {
								bool askopstate = banco1->block_unblock_account(id_cuenta, contra, !status);
								if (askopstate) std::cout << "\nProceso realizado correctamente" << endl;
								else std::cout << "\nProceso no completado satisfactoriamente" << endl;
							}
							else {
								std::cout << "\nSeleccione una operacion valida" << endl;
							}

						}
							break;

						case 'D':
						case 'd':{
							char* id_cuenta = new char[20];
							std::cout << "Ingrese numero de la cuenta" << endl;
							cin >> id_cuenta;
							int money = ask_deposit_money();
							
							
							bool status = false;
							if (banco1->get_how_accounts()!=0) {
								status = banco1->deposit(id_cuenta, money);
							}
							if(status) std::cout<<"\nProceso realizado correctamente"<<endl;
							else std::cout<<"\nProceso completado insatisfactoriamente, por favor verifique los datos"<<endl;
						}
						break;
						
						case 'R':
						case 'r':{
							char* id_cuenta = new char[20];
							std::cout << "Ingrese numero de la cuenta" << endl;
							cin >> id_cuenta;
							char* contra = new char[10];
							std::cout << "Ingrese su contraseña" << endl;
							cin >> contra;
							int money = 0;
							int salir=0;
							do{
							try{
								std::cout << "Ingrese el dinero a retirar" << endl;
								cin >> money;
								if(!cin)
									throw 125;
								salir=1;
							}catch(int){
									std::cout << "Cantidad no valida" << endl;
									cin.clear();
									cin.ignore();
								}
							}while(salir==0);
							int saldo = -1;
							if (banco1->get_how_accounts() != 0 && banco1->id_account_exist(id_cuenta)) {
								saldo = banco1->withdrawal(id_cuenta, money, contra);
								if (saldo == -1) {
									cout << "No tiene suficiente dinero" << endl;
								}
								else {
									ask_consulsaldo(saldo);
								}
							}
							else {
								cout << "No se pudo realizar el retiro, verifique los datos" << endl;
							}
						}
						break;
						default:{
							std::cout<<"\nOpcion no valida"<<endl;
						}
						break;

					}	
		}
	/*	int  TransferinterBank(int money, char * name,char * cuenta){
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
	}*/
		char* ask_accountnum(){
			std::cout<< "\nInserte su numero de cuenta"<<endl;
						char* accnum = 0;
						cin >> accnum ;
						return accnum;
		}
		char* ask_key(){
			std::cout<< "\nInserte la clave de su cuenta"<< endl;
			char* enteredkey= new char[20];
			cin>> enteredkey;
			return enteredkey;
		}

		int ask_deposit_money(){
			
			int money=0;
			do{
				try{
					std::cout<<"\nDigite la cantidad de dinero a depositar"<<endl;		
					cin>> money;
					 if(!cin)
		            throw 127;
					return money;
				}catch(int ){
					std::cout<<"\nCantidad no valida"<<std::endl;
					cin.clear();
					cin.ignore();
					money=0;
				}
			}while(1);
		}
		bool ask_status(){
			std::cout<<"\nPresione 1 para activar la cuenta y 2 para bloquear"<<endl;
			char* getstatus = new char[10];
			cin>> getstatus;
			switch (*getstatus)
			{
			case 'a':
			case 'A':
				return true;

			case 'b':
			case 'B':
				return false;
			default: 

				break;
			}
		}
		void ask_consulsaldo(int saldo){
			std::cout<<"\nDesea consultar su saldo? y:si, n:no\n"<<endl;
			char op;
			cin>> op;
			switch(op){
				case'y':
					std::cout<<"\nSu saldo es: "<< saldo<<endl;
				case 'n':
				break;
				default:
					std::cout<<"\nOpcion no valida"<<endl;
				break;
			}
		} 
		char* ask_name(){
			std::cout<<"\nInserte su nombre"<<endl;
			char* name= new char[20];
			cin>> name ;
			return name;
		}
		char* ask_lastname(){
			std::cout<<"\nInserte su apellido"<<endl;
			char* lastname= new char[20];
			cin>> lastname;
			return lastname;
		}
		int ask_age(){
			do{
				try{
				std::cout<<"\nInsete su edad"<<endl;
				int age;
				cin>> age;
					if(!cin)
		            throw 127;
					return age;
				}catch(int ){
					std::cout<<"\nCantidad no valida"<<std::endl;
					cin.clear();
					cin.ignore();
				
				}
			}while(1);
		}
		char* ask_id(){
			std::cout<<"\nInserte id de la cuenta "<<endl;
			char* acc_id = new char[12];
			cin>> acc_id;
			return acc_id;
		}
		char* ask_id_client(){
			std::cout<<"\nInserte id del cliente "<<endl;
			char* acc_id= new char [12];
			cin>> acc_id;
			return acc_id;
		}
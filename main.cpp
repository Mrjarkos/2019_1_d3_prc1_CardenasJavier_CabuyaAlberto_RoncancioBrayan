

#include "main.h"

#define TRUE 1
#define FALSE 0

#pragma warning(disable : 4996) 

int main(int argc, char **argv)
{
	char name1 []= "Banco ccv";
	char name2 []= "Cranks Bank";
	char* Name1= name1;
	char* Name2= name2;
	Bank* banco1= new Bank(Name1, NULL, NULL);
	Bank* banco2= new Bank(Name2, NULL, NULL);
	do{
		std::cout<<"Digite 1 para probar banco1\nDigite 2 para probar banco2"<<endl;
		optionkey= cin.get();
		if(optionkey=='1'){
			std::cout<<"Bienvenido al banco 1, ¿que desea hacer?, escoja una de las opciones mostradas\n"<<endl;
			std::cout << "Consultar:\n Nombre del banco: n\n"<<endl;
			std::cout << "Cliente : p \n Cuenta : c \n Crear cliente : m \n"<<endl;
			std::cout << "Actualizar datos cliente: u\n Crear cuenta: a\n Transferir : t\n"<<endl;
			std::cout << "Cambiar estado cuenta: e\n Depositar: d\n Retirar dinero: r \n"<<endl;
			cin>>optionkey ;
			char* id_client = new char [20];
			switch(optionkey){
				
				case 'N':
				case 'n':std::cout<< "Nombre del banco1=" << banco1-> get_name()<<"\n"<< endl;
			break;

				case 'P':
				case  'p':{ 
					std::cout<< "Inserte numero de identificacion del cliente" << endl;
					id_client = new char [20];
					cin >> id_client;
					Client_information* cliente = banco1->consult_client(id_client);
					if(cliente==NULL){ std::cout << "Clientre no encontrado" << endl; }
					else {
						
						std::cout << "exito" << endl;
						std::cout << "Nombre:" << cliente->firstName << endl;
						std::cout << "Apellido:" << cliente->lastName << endl;
						std::cout << "Id:" << cliente->id_client << endl;
						std::cout << "Cuentas:" << endl;
						char* a;
						for (int i = 0; i < cliente->nAccount; i++) {
							a = cliente->accounts[i];
							std::cout << "Numero de Cuenta [" << i << "] = " << a << endl;
						}
					}
				}
				break;
				
				case 'C':
				case 'c' :{
					char* id_cuenta = new char[20];
					std::cout << "Ingrese numero de la cuenta" << endl;
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
					std::cout << "Ingrese el dinero a transferir" << endl;
					cin >> money;
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
					if(*getstatus=='1'){
						status= true;
					}
					else{
						status= false;
					}
					
						bool askopstate = banco1->block_unblock_account(id_cuenta, contra, !status);
						if (askopstate) std::cout << "\nProceso realizado correctamente" << endl;
						else std::cout << "\nProceso no completado satisfactoriamente" << endl;
			
					

				}
					break;

				case 'D':
				case 'd':{
					char* id_cuenta = new char[20];
					std::cout << "Ingrese numero de la cuenta" << endl;
					cin >> id_cuenta;
					int money = 0;
					std::cout << "Ingrese el dinero a consignar" << endl;
					cin >>money;

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
					std::cout << "Ingrese el dinero a retirar" << endl;
					cin >> money;
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
		else if(optionkey=='2'){
			std::cout<<"Bienvenido al banco 2, ¿que desea hacer?, escoja una de las opciones mostradas\n"<<endl;
			std::cout << "Consultar:\n Nombre del banco: n\n"<<endl;
			std::cout << "Cliente : p \n Cuenta : c \n Crear cliente : m \n"<<endl;
			std::cout << "Actualizar datos cliente: u\n Crear cuenta: a\n Transferir : t\n"<<endl;
			std::cout << "Cambiar estado cuenta: e\n Depositar: d\n Retirar dinero: r \n"<<endl;
			cin>>optionkey ;
			char* id_client = new char [20];
			switch(optionkey){
				
				case 'N':
				case 'n':std::cout<< "Nombre del banco2=" << banco2-> get_name()<<"\n"<< endl;
			break;

				case 'P':
				case  'p':{ 
					std::cout<< "Inserte numero de identificacion del cliente" << endl;
					id_client = new char [20];
					cin >> id_client;
					Client_information* cliente = banco2->consult_client(id_client);
					if(cliente==NULL){ std::cout << "Clientre no encontrado" << endl; }
					else {
						
						std::cout << "exito" << endl;
						std::cout << "Nombre:" << cliente->firstName << endl;
						std::cout << "Apellido:" << cliente->lastName << endl;
						std::cout << "Id:" << cliente->id_client << endl;
						std::cout << "Cuentas:" << endl;
						char* a;
						for (int i = 0; i < cliente->nAccount; i++) {
							a = cliente->accounts[i];
							std::cout << "Numero de Cuenta [" << i << "] = " << a << endl;
						}
					}
				}
				break;
				
				case 'C':
				case 'c' :{
					char* id_cuenta = new char[20];
					std::cout << "Ingrese numero de la cuenta" << endl;
					cin >> id_cuenta;
					char* contra = new char[10];
					std::cout << "Ingrese su contraseña" << endl;
					cin >> contra;
					Account_information* cuenta = banco2-> consult_account(id_cuenta, contra);
					if (cuenta != NULL) {
						Client_information* cliente = banco2->consult_client(cuenta->cliente->id_client);
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
						
						int a = banco2->get_how_accounts();
						char* id_account = new char[10];
						sprintf(id_account, "%d\0", a);

						std::cout << "\nSe le asigno la cuenta Numero: "<< atoi(id_account) << endl;

						key = ask_key();
						int initial_amount = ask_deposit_money();

						bool state= banco2-> create_client(nameclient, lastnameclient, id, age, id_account, key, initial_amount);
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
						bool  clinetstate= banco2->id_client_exist(id_client);
						if(clinetstate){
							BankClient* cliente; 
							Client_information* client; 
							char* tecla = new char[2];
							
								cliente = banco2->select_client(id_client);
								client = banco2->consult_client(id_client);
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
									indic = banco2->update_client(cliente, name, cliente->get_lastName(), cliente->id_client, cliente->get_age());
									break;
								case '2':
									std::cout << "Inserte su nuevo Apellido" << endl;
									cin >> lastname;
									indic = banco2->update_client(cliente, cliente->get_firstName(), lastname, cliente->id_client, cliente->get_age());
									break;
								case '3': 
									std::cout << "Inserte su nuevo ID" << endl;
									cin >> ID;
									indic = banco2->update_client(cliente, cliente->get_firstName(), cliente->get_lastName(), ID, cliente->get_age());
									id_client = ID;
									break; 
								case '4': 
									std::cout << "Inserte su nueva Edad" << endl;
									cin >> age;
									indic = banco2->update_client(cliente, cliente->get_firstName(), cliente->get_lastName(), cliente->id_client, age);
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
									indic = banco2->update_client(cliente, name, lastname, ID, age);
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

					bool clientexists= banco2-> id_client_exist(client_id);

					if(clientexists){
							BankClient* clientee= banco2->select_client(client_id);
							int money= ask_deposit_money();
							key= ask_key();
							int a = banco2->get_how_accounts();
							char* id_account = new char[10];
							sprintf(id_account, "%d\0", a);
							std::cout << "Numero de cuenta:" << atoi(id_account) << std::endl;
							bool createclientstate= banco2->create_account(id_account, key, clientee, money );
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
						
						int a = banco2->get_how_accounts();
						char* id_account = new char[10];
						sprintf(id_account, "%d\0", a);

						std::cout << "\nSe le asigno la cuenta Numero: "<< atoi(id_account) << endl;

						key = ask_key();
						int initial_amount = ask_deposit_money();

						bool state= banco2-> create_client(nameclient, lastnameclient, client_id, age, id_account, key, initial_amount);

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
					std::cout << "Ingrese el dinero a transferir" << endl;
					cin >> money;
					std::cout<< "\nInserte el numero de cuenta a donde va a transferir"<<endl;
					char* accnum2= new char[20];
					cin >> accnum2;

					bool transferstate = banco2->transfer_money(id_cuenta, contra, accnum2, banco2, money);
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
					if(*getstatus=='1'){
						status= true;
					}
					else{
						status= false;
					}
					
						bool askopstate = banco1->block_unblock_account(id_cuenta, contra, !status);
						if (askopstate) std::cout << "\nProceso realizado correctamente" << endl;
						else std::cout << "\nProceso no completado satisfactoriamente" << endl;
			

				}
					break;

				case 'D':
				case 'd':{
					char* id_cuenta = new char[20];
					std::cout << "Ingrese numero de la cuenta" << endl;
					cin >> id_cuenta;
					int money = 0;
					std::cout << "Ingrese el dinero a consignar" << endl;
					cin >>money;

					bool status = false;
					if (banco2->get_how_accounts()!=0) {
						status = banco2->deposit(id_cuenta, money);
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
					std::cout << "Ingrese el dinero a retirar" << endl;
					cin >> money;
					int saldo = -1;
					if (banco2->get_how_accounts() != 0 && banco2->id_account_exist(id_cuenta)) {
						saldo = banco2->withdrawal(id_cuenta, money, contra);
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
		
		
		

		std::cout << "Presione dos veces Esc  y enter para salir o cualquier tecla volver al inicio" << endl;
		exitkey=cin.get();

	}while(exitkey!=27);

	return 0;
}
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
	std::cout<<"\nDigite la cantidad de dinero a depositar"<<endl;
	int money;
	cin>> money;
	return money;
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
	std::cout<<"\nInsete su edad"<<endl;
	int age;
	cin>> age;
	return age;
}
char* ask_id(){
	std::cout<<"\nInserte id de la cuenta "<<endl;
	char* acc_id = 0;
	cin>> acc_id;
	return acc_id;
}

char* ask_id_client(){
	std::cout<<"\nInserte id del cliente "<<endl;
	char* acc_id= new char [12];
	cin>> acc_id;
	return acc_id;
}

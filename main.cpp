
#include "main.h"

#define TRUE 1
#define FALSE 0

int main(int argc, char **argv)
{
	char name1 []= "Banco ccv";
	char name2 []= "Cranks Bank";
	char* Name1= name1;
	char* Name2= name2;
	Bank* banco1= new Bank(Name1, NULL, NULL);
	Bank* banco2= new Bank(Name2, NULL, NULL);
	do{
		cout<<"Digite 1 para probar banco1\nDigite 2 para probar banco2"<<endl;
		cin>>optionkey;
		if(optionkey=='1'){
			cout<<"Bienvenido al banco 1, ¿que desea hacer?, escoja una de las opciones mostradas\n"<<endl;
			cout << "Consultar:\n Nombre del banco: n\n"<<endl;
			cout << "Cliente : p \n Cuenta : c \n Crear cliente : m \n"<<endl;
			cout << "Actualizar datos cliente: u\n Crear cuenta: a\n Transferir : t\n"<<endl;
			cout << "Cambiar estado cuenta: e\n Depositar: d\n Retirar dinero: r \n"<<endl;
			cin>>optionkey ;
			char*id_client = new char [20];
			switch(optionkey){

				case 'n':cout<< "Nombre del banco1=" << banco1-> get_name()<<"\n"<< endl;
		break;
				case  'p':{ 
					cout<< "Inserte numero de identificacion del cliente" << endl;
					id_client = new char [20];
					cin >> id_client;
					Client_information* cliente = banco1->consult_client(id_client);
					if(cliente==NULL){ cout << "Clientre no encontrado" << endl; }
					else {
						
						cout << "exito" << endl;
						cout << "Nombre:" << cliente->firstName << endl;
						cout << "Apellido:" << cliente->lastName << endl;
						cout << "Id:" << cliente->id_client << endl;
						cout << "Id de cuentas" << endl;
						char* a = cliente->accounts[0]->accountnumber;
						for (int i = 0; i < cliente->nAccount; i++) {
							cout << "Número de Cuenta [" << i << "] = " << atoi(cliente->accounts[0]->accountnumber) << endl;
						}
					}
				}
				break;
				case 'c' :{
					accnum= ask_accountnum();
					key= ask_key();
					banco1-> consult_account(accnum, key);
				}
				break; 
				case 'm':{ 
						cout<< "\nInserte nombre del cliente:"<< endl;
						char*nameclient= new char[15];
						cin>> nameclient;
						
						cout<< "\nInserte apellido del cliente:"<< endl;
						char*lastnameclient = new char[15];
						cin>> lastnameclient;
					
						cout<< "\nInserte numero de identificacion del cliente:"<< endl;
						char*id = new char[20];
						cin>> id;
					
						cout<< "\nInserte edad del cliente:"<< endl;
						int age;
						cin>> age;
					
						char* id_account=(char*)banco1->get_how_accounts();
						cout << "\nSe le asigno la cuenta Numero: "<< atoi(id_account) << endl;
						key = ask_key();
						int initial_amount = ask_deposit_money();

						bool state= banco1-> create_client(nameclient, lastnameclient, id, age, id_account, key, initial_amount);
					    if(state){
					    	cout<<"\nCliente creado"<<endl;
					    }
					    else{
					    	cout<<"\nNo se logoro realizar la accion"<<endl; 
							banco1->fail_account();
					    }
					}
				break;
				case 'u':{
						cout<< "\nInserte nombre del cliente:"<< endl;
						char* nameclient = 0;
						cin>> nameclient;
						

						cout<< "\nInserte apellido del cliente:"<< endl;
						char* lastnameclient = 0;
						cin>> lastnameclient;
					
						cout<< "\nInserte numero de identificacion del cliente:"<< endl;
						
						cin>> id_client;
					
						cout<< "\nInserte edad del cliente:"<< endl;
						int age;
						cin>> age;
						bool  clinetstate= banco1->id_client_exist(id_client);
						if(clinetstate){
							cout<< "\n A continuacion iserte sus nuevos datos"<<endl;
							char* newname= ask_name();

							cout<< "\nInserte apellido del cliente:"<< endl;
							char* newlastnameclient= new char[20];
							cin>> newlastnameclient;

							char* newid=ask_id();

							int newage= ask_age();

							BankClient* cliented =banco1->select_client(id_client);
							banco1-> update_client(cliented, newname, newlastnameclient, newid, newage);
						}
						
						else {
							cout<<"\ncliente no encontrado"<<endl;
						}

					}
				break; 
				case 'a':{
					char* nameclient=ask_name();
					char* lastnameclient= ask_lastname();
					accnum= ask_accountnum();
					int age= ask_age();
					char* client_id= ask_id_client();
					bool clientexists= banco1-> id_client_exist(client_id);
					if(clientexists){
							BankClient* clientee= banco1->select_client(client_id);
							char* id_account= ask_id();
							int money= ask_deposit_money();
							key= ask_key();
							bool createclientstate= banco1->create_account(id_account, key, clientee, money );
							 if(createclientstate){
							 cout<<"\nCuenta añadida"<<endl;
							}
							else {
								cout<<"\n No se pudo realizar la operacion"<<endl;
							}

					}
					else{
						cout<<"\nCliente no encontrado"<<endl;
					}
				}
				break;
				case 't':{
					accnum=ask_accountnum();
						key= ask_key();
					cout<< "\nInserte el numero de cuenta a donde va atransferir"<<endl;
					char* accnum2= new char[20];
					cin >> accnum2;
						cout<< "\nInserte Banco "<< endl;
						char* enteredkey= new char[20];
						cin>> enteredkey;
						Bank* bancopunt;
						int money;
						if(enteredkey== banco1->get_name()){
								bancopunt= banco1;
								money= ask_deposit_money();
								bool transferstate= banco1->transfer_money(accnum,key, accnum2, bancopunt, money );
								if(transferstate){
									cout<<"\nTransferencia realizada"<<endl;
								}
								else { cout<< "\nError en la transferencia"<< endl;}
							}
						else if (enteredkey== banco2-> get_name()){
							bancopunt= banco2;
							money= ask_deposit_money();
							bool transferstate= banco1->transfer_money(accnum,key, accnum2, bancopunt, money );
								if(transferstate){
									cout<<"\nTransferencia realizada"<<endl;
								}
								else { cout<< "\nError en la transferencia"<< endl;}
							}
						else {
							cout<<"\n Banco no encontrado"<<endl;
						}

				
				}
					break;
				case 'e':{
					accnum= ask_accountnum();
					key= ask_key();
					bool status= ask_status();
					bool askopstate=banco1->block_unblock_account(accnum,key, status);
					if(askopstate) cout<<"\nProceso realizado correctamente"<<endl;
					else cout<<"\nProceso no completado satisfactoriamente"<<endl;
				}
					break;
					case 'd':{
					accnum= ask_accountnum();
					int money= ask_deposit_money();
					bool status= banco1-> deposit(accnum, money);
					if(status) cout<<"\nProceso realizado correctamente"<<endl;
					else cout<<"\nProceso no completado satisfactoriamente"<<endl;
				}

					break;
					case 'r':{
					accnum= ask_accountnum();
					key= ask_key();
					int money =ask_deposit_money();
					int saldo=banco1->withdrawal(accnum, money, key);
					ask_consulsaldo(saldo);
				}
				break;
				default:{
					cout<<"\nOpcion no valida"<<endl;
				}
				break;

			}
		}

		else if(optionkey=='2'){
			cout<<"Bienvenido al banco 2, ¿que desea hacer?, escoja una de las opciones mostradas\n"<<endl;
			cout << "Consultar:\n Nombre del banco: n\n"<<endl;
			cout << " Cliente : p \n Cuenta : c \n Crear cliente : m \n"<<endl;
			cout << "Actualizar datos cliente: u\n Crear cuenta: a\n Transferir : t\n"<<endl;
			cout << "Cambiar estado cuenta: e\n Depositar: d\n Retirar dinero: r \n"<<endl;
			cin >> optionkey;
			char* id_client= new char[12];
			switch(optionkey){
				

				case 'n':cout<< "Nombre del banco2=" << banco2-> get_name()<<"\n"<< endl;
				break;
				case  'p':{ 
					cout<< "Inserte numero de identificacion del cliente" << endl;
					
					cin >> id_client;
					banco2-> consult_client(id_client);
				}
				break;
				case 'c' :{
					accnum= ask_accountnum();
					key= ask_key();
					banco2-> consult_account(accnum, key);
				}
				break; 
				case 'm':{ 
						cout<< "\nInserte nombre del cliente:"<< endl;
						char* nameclient= new char[20];
						cin>> nameclient;
					
						cout<< "\nInserte apellido del cliente:"<< endl;
						char* lastnameclient= new char[20];
						cin>> lastnameclient;
					
						cout<< "\nInserte numero de identificacion del cliente:"<< endl;
						
						cin>> id_client;
					
						cout<< "\nInserte edad del cliente:"<< endl;
						int age;
						cin>> age;
					
						char* id_account=(char*)banco2->get_how_accounts();
						key = ask_key();
						int initial_amount = ask_deposit_money();

					    bool state= banco2-> create_client(nameclient, lastnameclient, id_client, age, id_account, key, initial_amount);
					    if(state){
					    	cout<<"\nCliente creado"<<endl;
					    }
					    else{
					    	cout<<"\nNo se logoro realizar la accion"<<endl; 
					    }
				}
				break;
				case 'u':{
						cout<< "\nInserte nombre del cliente:"<< endl;
						char* nameclient= new char[20];
						cin>> nameclient;
						

						cout<< "\nInserte apellido del cliente:"<< endl;
						char* lastnameclient= new char[20];
						cin>> lastnameclient;
					
						cout<< "\nInserte numero de identificacion del cliente:"<< endl;
						
						cin>> id_client;
					
						cout<< "\nInserte edad del cliente:"<< endl;
						int age;
						cin>> age;
						bool  clinetstate= banco2->id_client_exist(id_client);
						if(clinetstate){
							cout<< "\n A continuacion iserte sus nuevos datos"<<endl;
							char* newname= ask_name();

							cout<< "\nInserte apellido del cliente:"<< endl;
							char* newlastnameclient= new char[20];
							cin>> newlastnameclient;

							char* newid=ask_id();

							int newage= ask_age();

							BankClient* cliented =banco2->select_client(id_client);
							banco1-> update_client(cliented, newname, newlastnameclient, newid, newage);
						}
						
						else {
							cout<<"\ncliente no encontrado"<<endl;
						}

				}
				break; 
				case 'a':{
					char* nameclient=ask_name();
					char* lastnameclient= ask_lastname();
					accnum= ask_accountnum();
					int age= ask_age();
					char* client_id= ask_id_client();
					bool clientexists= banco2-> id_client_exist(client_id);
					if(clientexists){
					BankClient* clientee= banco2->select_client(client_id);
					char* id_account= ask_id();
					int money= ask_deposit_money();
					key= ask_key();
					bool createclientstate= banco2->create_account(id_account, key, clientee, money );
					 if(createclientstate)
					 cout<<"\nCuenta añadida"<<endl;
					else {
						cout<<"\n No se pudo realizar la operacion"<<endl;
					}

					}
					else{
						cout<<"\nCliente no encontrado"<<endl;
					}
				}
				break;
				case 't':{
					accnum=ask_accountnum();
						key= ask_key();
					cout<< "\nInserte el numero de cuenta a donde va atransferir"<<endl;
					char* accnum2= new char[20];
					cin >> accnum2;
						cout<< "\nInserte Banco "<< endl;
						char* enteredkey = 0;
						cin>> enteredkey;
						Bank* bancopunt;
						int money;
						if(enteredkey== banco1->get_name()){
								bancopunt= banco1;
								money= ask_deposit_money();
								bool transferstate= banco2->transfer_money(accnum,key, accnum2, bancopunt, money );
								if(transferstate){
									cout<<"\nTransferencia realizada"<<endl;
								}
								else { cout<< "\nError en la transferencia"<< endl;}
							}
						else if (enteredkey== banco2-> get_name()){
							bancopunt= banco2;
							money= ask_deposit_money();
							bool transferstate= banco2->transfer_money(accnum,key, accnum2, bancopunt, money );
								if(transferstate){
									cout<<"\nTransferencia realizada"<<endl;
								}
								else { cout<< "\nError en la transferencia"<< endl;}
							}
						else {
							cout<<"\n Banco no encontrado"<<endl;
						}

				
				}
					break;
				case 'e':{
					accnum= ask_accountnum();
					key= ask_key();
					bool status= ask_status();
					bool askopstate=banco2->block_unblock_account(accnum,key, status);
					if(askopstate) cout<<"\nProceso realizado correctamente"<<endl;
					else cout<<"\nProceso no completado satisfactoriamente"<<endl;
				}
					break;
					case 'd':{
					accnum= ask_accountnum();
					int money= ask_deposit_money();
					bool status= banco2-> deposit(accnum, money);
					if(status) cout<<"\nProceso realizado correctamente"<<endl;
					else cout<<"\nProceso no completado satisfactoriamente"<<endl;
				}

					break;
					case 'r':{
					accnum= ask_accountnum();
					key= ask_key();
					int money =ask_deposit_money();
					int saldo=banco1->withdrawal(accnum, money, key);
					ask_consulsaldo(saldo);
				}
				break;
				default:{
					cout<<"\nOpcion no valida"<<endl;
				}
				break;

			}
		}
		
		

		cout << "Presione Esc para salir o cualquier tecla volver al inicio" << endl;
		exitkey=getch();

	}while(exitkey!=27);

	return 0;
}
char* ask_accountnum(){
	cout<< "\nInserte su numero de cuenta"<<endl;
				char* accnum = 0;
				cin >> accnum ;
				return accnum;
}
char* ask_key(){
	cout<< "\nInserte la clave de su cuenta"<< endl;
	char* enteredkey= new char[20];
	cin>> enteredkey;
	return enteredkey;
}

int ask_deposit_money(){
	cout<<"\nDigite la cantidad de dinero a depositar"<<endl;
	int money;
	cin>> money;
	return money;
}
bool ask_status(){
	cout<<"\nPresione a para activar la cuenta y b para bloquear"<<endl;
	char getstatus;
	cin>> getstatus;
	if (getstatus= 'a') return TRUE;
	else return FALSE;
}
void ask_consulsaldo(int saldo){
	cout<<"\nDesea consultar su saldo? y:si, n:no\n"<<endl;
	char op;
	cin>> op;
	switch(op){
		case'y':
		cout<<"\nSu saldo es: "<< saldo<<endl;
		case 'n':
		break;
		default:
		cout<<"\nOpcion no valida"<<endl;
		break;
	}
	} 
char* ask_name(){
	cout<<"\nInserte su nombre"<<endl;
	char* name= new char[20];
	cin>> name ;
	return name;
}
char* ask_lastname(){
	cout<<"\nInserte su apellido"<<endl;
	char* lastname= new char[20];
	cin>> lastname;
	return lastname;
}
int ask_age(){
	cout<<"\nInsete su edad"<<endl;
	int age;
	cin>> age;
	return age;
}
char* ask_id(){
	cout<<"\nInserte id de la cuenta "<<endl;
	char* acc_id;
	cin>> acc_id;
	return acc_id;
}

char* ask_id_client(){
	cout<<"\nInserte id del cliente "<<endl;
	char* acc_id= new char [12];
	cin>> acc_id;
	return acc_id;
}


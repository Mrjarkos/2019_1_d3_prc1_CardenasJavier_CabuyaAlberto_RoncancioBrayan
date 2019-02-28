#include "Bank.h"
#include <curses.h>

using namespace std;

char exitkey;
char optionkey;
char* key ;
char* accnum;

int main(int argc, char const *argv[])
{
	char* name1= "Banco ccv";
	char* name2= "Cranks Bank";
	Bank* banco1= new Bank(name1, NULL, NULL);
	Bank* banco2= new Bank(name2, NULL, NULL);
	do{
		cout<<"Digite 1 para probar banco1\n Digite 2 para probar banco2"<<endl;
		cin>>optionkey;
		if(optionkey=='1'){
			cout<<"Bienvenido al banco 1, ¿que desea hacer?, escoja una de las opciones mostradas\n"<<endl;
			cout << "Consultar:\n Nombre del banco: n\n"<<endl;
			cout << "Cliente : p \n Cuenta : c \n Crear cliente : m \n"<<endl;
			cout << "Actualizar datos cliente: u\n Crear cuenta: a\n Transferir : t\n"<<endl;
			cout << "Cambiar estado cuenta: e\n Depositar: d\n Retirar dinero: r \n"<<endl;
			cin >> optionkey;
			switch(optionkey){
				case 'n':cout<< "Nombre del banco1=" << banco1-> get_name()<<"\n"<< endl;
				break;
				case  'p': 
				cout<< "Inserte numero de identificacion del cliente" << endl;
				char* id_client;
				cin >> id_client;
				banco1-> consult_client(id_client);
				break;
				case 'c' :
				accnum= ask_accountnum();
				key= ask_key();
				banco1-> consult_account(accnum, key);
				break; 
				case 'm': 
					cout<< "\nInserte nombre del cliente:"<< endl;
					cin>> char* nameclient;
					cout<< "\nInserte apellido del cliente:"<< endl;
					cin>> char* lastnameclient;
					cout<< "\nInserte numero de identificacion del cliente:"<< endl;
					cin>> char* id_client;
					cout<< "\nInserte edad del cliente:"<< endl;
					cin>> int age;
					char* id_account=banco1->get_how_accounts();
					key = ask_key();
					int initial_amount = ask_deposit_money();

				banco1-> create_client(nameclient, lastnameclient, id_client, age, id_account, key, initial_amount);
				break;
				case 'u':
				banco1-> update_client();
				break; 
				case 'a':
				char* nameclient=ask_name();
				char* lastnameclient= ask_lastname();
				accnum= ask_accountnum();
				int age= ask_age();
				char* id_account= ask_id();
				int money= ask_deposit_money();
				key= ask_key();
				BankClient cliente= new BankClient(nameclient, lastnameclient,accnum, age, id_account,money);
				 banco1-> create_client(BankClient* clientepoint= cliente);
				 cout<<"Cliente añadido"<<endl;
				break;
				case 't':
				accnum=ask_accountnum();
					key= ask_key();
				cout<< "\nInserte el numero de cuenta a donde va atransferir"<<endl;
				cin >>int accnum2;
					cout<< "\nInserte Banco "<< endl;
					cin>> string enteredkey;
					char*bankn= enteredkey;
					if(bankn== banco1->name){
						Bank * bancopunt= banco1;
					}
					else (bankn== banco2-> name2){
						Bank* bancopunt= banco2;
					}
				int money= ask_deposit_money();
				bool transferstate= banco1->trasfer_money(accnum,key, accnum2, bancopunt, money );
				if(transferstate){
					cout<<"\nTransferencia realizada"<<endl;
				}
				else { cout<< "\nError en la transferencia"<< endl;}
				break;
				case 'e':
				accnum= ask_accountnum();
				key= ask_key();
				bool status= ask_status();
				bool askopstate=banco1->block_unblock_account(accnum,key, status);
				if(askopstate) cout<<"\nProceso realizado correctamente"<<endl;
				else cout<<"\nProceso no completado satisfactoriamente"<<endl;
				break;
				case 'd':
				accnum= ask_accountnum();
				int money= ask_deposit_money();
				bool status= banco1-> deposit(accnum, money);
				if(status) cout<<"\nProceso realizado correctamente"<<endl;
				else cout<<"\nProceso no completado satisfactoriamente"<<endl;
				break;
				case 'r':
				accnum= ask_accountnum();
				key= ask_key();
				int money ask_deposit_money();
				int saldo= withdrawal(accnum, money, key);
				ask_consulsaldo(saldo);
				break;
				default:
				cout<<"\nOpcion no valida"<<endl;
				break;

			}
			if(optionkey=="2"){
			cout<<"Bienvenido al banco 2, ¿que desea hacer?, escoja una de las opciones mostradas\n"<<endl;
			cout << "Consultar:\n Nombre del banco: n\n"<<endl;
			cout << "Cliente : p \n Cuenta : c \n Crear cliente : m \n"<<endl;
			cout << "Actualizar datos cliente: u\n Crear cuenta: a\n Transferir : t\n"<<endl;
			cout << "Cambiar estado cuenta: e\n Depositar: d\n Retirar dinero: r \n"<<endl;
			cin >> optionkey;
			switch(optionkey){
				case 'n':cout<< "Nombre del banco2=" << banco2-> get_name()<<"\n"<< endl;
				break;
				case  'p': banco2-> consult_client();
				break;
				case 'c' :
				accnum= ask_accountnum();
				key= ask_key();
				banco2-> consult_account(accnum, key);
				break; 
				case 'm': 
				cout<< "\nInserte nombre de cliente "<< endl;
				cin>> string client_name;
				banco2-> create_client();
				break;
				case 'u':
				banco2-> update_client();
				break; 
				case 'a':
				char* nameclient=ask_name();
				char* lastnameclient= ask_lastname();
				accnum= ask_accountnum();
				int age= ask_age();
				char* id_account= ask_id();
				int money= ask_deposit_money();
				key= ask_key();
				BankClient cliente= new BankClient(nameclient, lastnameclient,accnum, age, id_account,money);
				banco2-> create_client(BankClient* clientepoint= cliente);
				cout<<"Cliente añadido"<<endl;
				break;
				case 't':
				accnum=ask_accountnum();
					key= ask_key();
				cout<< "\nInserte el numero de cuenta a donde va atransferir"<<endl;
				cin >>int accnum2;
					cout<< "\nInserte 	nombre banco \n Bnacos disponibles:\n "<< banco1-> get_name() << "\n"<< banco2-> get_name()<< endl;
					cin>> char enteredkey[];
					char*bankn= enteredkey;
					if(bankn== banco1->name){
						Bank * bancopunt= banco1;
					}
					else (bankn== banco2-> name2){
						Bank* bancopunt= banco2;
					}
				int money= ask_deposit_money();
				bool transferstate= banco2->trasfer_money(accnum,key, accnum2, bancopunt, money );
				if(transferstate){
					cout<<"\nTransferencia realizada"<<endl;
				}
				else { cout<< "\nError en la transferencia"<< endl;}
				break;
				case 'e':
				accnum= ask_accountnum();
				key= ask_key();
				bool status= ask_status();
				bool askopstate=banco2->block_unblock_account(accnum,key, status);
				if(askopstate) cout<<"\nProceso realizado correctamente"<<endl;
				else cout<<"\nProceso no completado satisfactoriamente"<<endl;
				break;
				case 'd':
				accnum= ask_accountnum();
				int money= ask_deposit_money();
				bool status= banco2-> deposit(accnum, money);
				if(status) cout<<"\nProceso realizado correctamente"<<endl;
				else cout<<"\nProceso no completado satisfactoriamente"<<endl;
				break;
				case 'r':
				accnum= ask_accountnum();
				key= ask_key();
				int money ask_deposit_money();
				int saldo= withdrawal(accnum, money, key);
				ask_consulsaldo(saldo);
				break;
				default:
				cout<<"\nOpcion no valida"<<endl;
				break;

			}
		}

	cout << "Presione Esc para salir o cualquier tecla volver al inicio" << endl;
	exitkey=getch();

	}while(exitkey==27);
	return 0;
}
char* ask_accountnum(){
	cout<< "\nInserte su numero de cuenta"<<endl;
				cin >>char accnum [];
				char* pointaccnum=accnum;
				return pointaccnum;
}
string ask_key(){
	cout<< "\nInserte su clave"<< endl;
	cin>> string enteredkey;
	return enteredkey;
}
int ask_deposit_money(){
	cout<<"Digite la cantidad de dinero a depositar"<<endl;
	cin>> int money;
	return money;
}
bool ask_status(){
	cout<<"Presione a para activar la cuenta y b para bloquear"<<endl;
	cin>> char getstatus;
	if (getstatus= 'a') return TRUE;
	else return FALSE;
}
void ask_consulsaldo(int saldo){
	cout<<"Desea consultar su saldo? y:si, n:no\n"<<endl;
	cin>>char op;
	switch(op){
		case'y':
		cout<<"\nSu saldo es: "<< saldo<<endl;
		case 'n':
		break;
		default:
		cout<<"\n Opcion no valida"<<endl;
		break;
	}
	} 
char* ask_name(){
	cout<<"\nInserte su nombre"<<endl;
	cin>>char name [];
	char* pointname=name;
	return pointname;
}
char* ask_lastname(){
	cout<<"\nInserte su apellido"<<endl;
	cin>>char lastname [];
	char* pointlastname=lastname;
	return pointlastname;
}
int ask_age(){
	cout<<"\nInsete su edad"<<endl;
	cin>>int age;
	return age;
}
char* ask_id(){
	cout<<"\nInserte id de la cuenta nueva"<<endl;
	cin>>char acc_id [];
	char* pointacc_id=acc_id;
	return pointacc_id;
}


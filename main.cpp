

#include "main.h"
#include <iostream>
#include <sstream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>        
#include <fcntl.h>  
#include <unistd.h>
#define TRUE 1
#define FALSE 0
using namespace std;
#pragma warning(disable : 4996) 
const int size =400; //tamaño memoria compartida
int main(int argc, char **argv)
{	
	//cout<< argv[1]<<endl;
//	cout << argv[0]<<endl;
//	cin>> argv [0];
	//cout<< memory_exists<<endl;
	//char nombre []= "Cranks bank";
	//char* Nombre= nombre;
	char * name= argv[1];// Nombre memoria compartida
	
try{
			Bank* banco1= new Bank(argv[1], NULL, NULL); // nombre del banco igual al argumento	
			Interface* interface1= new Interface(banco1);
			cout << sizeof(banco1)<<endl;
			do{

				interface1-> mostrar();
				std::cout << "Presione dos veces Esc para salir o cualquier tecla volver al inicio" << endl;
				
			
			cin>>exitkey;
			}while(exitkey!=27);
			delete banco1;
			return 0;
	} catch (exception& e)
	  {
	    cout << e.what() << '\n';
	    //shm_unlink(name);
	    return 0;
	  }
}
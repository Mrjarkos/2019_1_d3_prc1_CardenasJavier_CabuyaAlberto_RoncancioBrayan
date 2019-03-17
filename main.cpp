

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
#define TRUE 1
#define FALSE 0
using namespace std;
#pragma warning(disable : 4996) 
const int size = 8172; //tamaño memoria compartida
const char * name= "bankk";// Nombre memoria compartida
int main(int argc, char **argv)
{	

	int memory_exists;
	void*  memorypont;
	memory_exists= shm_open(name, O_RDWR|O_CREAT , 0666 ); // abre la memoria si existe, revisar el numero
	//cout<< argv[1]<<endl;
//	cout << argv[0]<<endl;
//	cin>> argv [0];
	//cout<< memory_exists<<endl;
	//char nombre []= "Cranks bank";
	//char* Nombre= nombre;
	Bank* banco1= new Bank(argv[1], NULL, NULL); // nombre del banco igual al argumento	
	Interface* interface1= new Interface(banco1);
	do{
		interface1-> mostrar();
		std::cout << "Presione dos veces Esc para salir o cualquier tecla volver al inicio" << endl;
		
	memorypont= mmap(0, size, PROT_WRITE, MAP_SHARED, memory_exists,0);
	printf("%s\n",(char* )memorypont);
	cin>>exitkey;
	}while(exitkey!=27);

	return 0;
}

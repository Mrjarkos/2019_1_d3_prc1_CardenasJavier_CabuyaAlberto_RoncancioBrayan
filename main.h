
#ifndef MAIN_H
#define MAIN_H

#include "Bank.h"
#include <curses.h>

using namespace std;
char exitkey;
char optionkey;
char* key ;
char* accnum;
int main (int, char**);
char* ask_name();
char* ask_lastname();
int ask_age();
char* ask_id();
char* ask_id_client();
void ask_consulsaldo(int);
bool ask_status();
int ask_deposit_money();
char* ask_key();
char* ask_accountnum();

#endif
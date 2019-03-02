all: main
	
main: main.o Bank.o BankAccount.o BankClient.o
	g++ -o main main.o  Bank.o BankAccount.o BankClient.o -lncurses

main.o: main.cpp
	g++ -c main.cpp

Bank.o: Bank.cpp
	g++ -c Bank.cpp

BankAccount.o: BankAccount.cpp
	g++ -c BankAccount.cpp

BankClient.o: BankClient.cpp
	g++ -c BankClient.cpp

run: main
	./main

.PHONY: clean

clean:
	rm -f main *.o

/*
Anthony Tran
CS 1337-501
11/5/2022

Program to read a inputed bankInfo.txt file and insert the infomation into
a dynamically allocated array. The program then outputs the bank information 
using both a regular function and a friend function. The first table is
printed using the regular function and the second table is from using the 
friend function
This program assumes that every new user will have a starting amount of 500
*/

#include "Bank.h"
#include <iostream>
#include <fstream>
#include <iomanip>


using namespace std;

void displayAccountInfo(Bank * thisBank);
int countNumTransactions(char * fileName);
int countUniqueAccounts(char * fileName, int numTransactions);
bool searchArray(long long int * accounts, int size, long long int target);
int searchObjectArray(Bank * portfolio, int size, long long int target);
bool readInputFile(Bank * portfolio, int size, char * fileName);
void changeAmount(Bank &thisBank, TRANSACTION_TYPE type, double amount);

int main() {
    char fileName[] = "bankInfo.txt";
    int numTransactions = countNumTransactions(fileName);
    int uniqueAccounts = countUniqueAccounts(fileName, numTransactions);
    
    Bank *portfolio = nullptr;
    portfolio = new Bank[uniqueAccounts];
    
    readInputFile(portfolio, uniqueAccounts, fileName);
    
    //displays accounts using normal function
    cout << setw(12) << "Account" << setw(10) << "Amount" << setw(30) << "Name" << endl;
    for (int i = 0; i < uniqueAccounts; i++) {
        displayAccountInfo(&portfolio[i]);
    }
    cout << endl;
    
    //displays accounts using friend function
    cout << setw(12) << "Account" << setw(10) << "Amount" << setw(30) << "Name" << endl;
    for (int i = 0; i < uniqueAccounts; i++) {
        accountInfo(portfolio[i]);
    }
    
    return 0;
}

//displays the account number, amount, and owner name of a bank object
void displayAccountInfo(Bank *thisBank) {
    cout << setw(12) << thisBank->getAccountNum()
    << setw(10) << fixed << setprecision(2) << thisBank->getAmount()
    << setw(30) << thisBank->getOwnerName() << endl;
}

//displays account info using private class variables bc its a friend function
void accountInfo(Bank thisBank) {
    cout << setw(12) << thisBank.accountNumber
    << setw(10) << fixed << setprecision(2) << thisBank.amount
    << setw(30) << thisBank.owner << endl;
}

//Counts the number of transactions in the file
int countNumTransactions(char * fileName) {
    ifstream input;
    input.open(fileName);
    if(!input.is_open()) {
        cout << "File could not open" << endl;
        return -1;
    }
    int counter;
    char buffer[1000];
    while(!input.eof()) {
        input.getline(buffer, 1000);
        input.getline(buffer, 1000);
        input.getline(buffer, 1000);
        input.getline(buffer, 1000);
        counter++;
    }
    input.close();
    return counter;
}

//counts the number of unique accounts
int countUniqueAccounts(char * fileName, int numTransactions) {
    long long int accounts[numTransactions];
    ifstream input;
    input.open(fileName);
    if(!input.is_open()) {
        cout << "File could not open" << endl;
        return -1;
    }
    int counter = 0;
    char buffer[1000];
    while(!input.eof()) {
        int temp;
        input >> temp;
        input.getline(buffer, 1000);
        input.getline(buffer, 1000);
        input.getline(buffer, 1000);
        input.getline(buffer, 1000);
        if (!searchArray(accounts, numTransactions, temp)) {
            accounts[counter] = temp;
            counter++;
        }
    }
    input.close();
    return counter;
}

//returns true if target int is inside array
bool searchArray(long long int * accounts, int size, long long int target) {
    for (int i = 0; i < size; i++) {
        if (target == accounts[i]) {
            return true;
        }
    }
    return false;
}

//Searches object array for matching account number
//returns the index of the searched object, or -1 if not found
int searchObjectArray(Bank * portfolio, int size, long long int target) {
    for (int i = 0; i < size; i++) {
        if (target == portfolio[i].getAccountNum()) {
            return i;
        }
    }
    return -1;
}

//reads the input file information into the portfolio array
//calls changeAmount() for each transaction, depending on deposit or withdraw
bool readInputFile(Bank * portfolio, int size, char * fileName) {
    ifstream input;
    input.open(fileName);
    if(!input.is_open()) {
        cout << "File could not open" << endl;
        return false;
    }
    int numAccounts = 0;
    while(!input.eof()) {
        long long int tempAccountNum;
        int tempType;
        double tempAmount;
        char buffer[1000];
        
        input >> tempAccountNum;
        input.getline(buffer, 1000);
        input >> tempType;
        input.getline(buffer, 1000);
        input >> tempAmount;
        input.getline(buffer, 1000);
        input.getline(buffer, 1000); //gets name
        
        int index = searchObjectArray(portfolio, size, tempAccountNum);
        if (index == -1) {
            portfolio[numAccounts].setAccountNum(tempAccountNum);
            portfolio[numAccounts].setType((TRANSACTION_TYPE) tempType);
            portfolio[numAccounts].setName(buffer);
            changeAmount(portfolio[numAccounts], portfolio[numAccounts].getType(), tempAmount);
            numAccounts++;
        } else {
            portfolio[index].setType((TRANSACTION_TYPE) tempType);
            changeAmount(portfolio[index], portfolio[index].getType(), tempAmount);
        }
        
    }
    input.close();
    return true;
}

//deposits or withdraws amount based on type
void changeAmount(Bank &thisBank, TRANSACTION_TYPE type, double amount) {
    if (type == DEPOSIT) {
        thisBank.deposit(amount);
    } else {
        thisBank.withdraw(amount);
    }
}
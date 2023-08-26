#include "Bank.h"
#include <iostream>

using namespace std;

//getters
long long int Bank::getAccountNum() const {
    return accountNumber;
}
TRANSACTION_TYPE Bank::getType() const {
    return type;
}
double Bank::getAmount() const {
    return amount;
}
char * Bank::getOwnerName() const {
    return owner;
}

//setters
void Bank::setAccountNum(long long int newNum) {
    accountNumber = newNum;
}
void Bank::setType(TRANSACTION_TYPE newType) {
    type = newType;
}
void Bank::setAmount(double newAmount) {
    amount = newAmount;
}
void Bank::setName(const char * newName) {
    if (owner != nullptr) {
        delete [] owner;
    }
    int size = 0;
    while (newName[size++] != '\0'); //nullptr is at newName[size]
    owner = new char[size];
    int count = 0;
    while (count < size) {
        owner[count] = newName[count];
        count++;
    }
    owner[count] = '\0';
}

void Bank::withdraw(double withDrawAmt) {
    if (withDrawAmt <= amount) {
        amount -= withDrawAmt;
    } else {
        cout << "Insufficient balance, " << owner << endl;
        amount = 0;
    }
}
void Bank::deposit(double depositAmt) {
    amount += depositAmt;
}

Bank::Bank() {
    accountNumber = 9999999999;
    amount = 500;
    owner = nullptr;
}
Bank::Bank(long long int newAccountNum, double newBalance) {
    accountNumber = newAccountNum;
    amount = newBalance;
    owner = nullptr;
}
Bank::Bank(long long int newAccountNum, double newBalance, char * newOwner) {
    accountNumber = newAccountNum;
    amount = newBalance;
    owner = nullptr;
    setName(newOwner);
}

Bank::~Bank() {
    if (owner != nullptr) {
        delete [] owner;
    }
}


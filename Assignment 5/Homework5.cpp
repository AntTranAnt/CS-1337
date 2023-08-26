
/* things to fix:

*/
#include <iostream>
#include <fstream>
#include <iomanip>
#include "address.h"
#include "employee.h"
#include "record.h"
#include "allRecords.h"

using namespace std;

int countNumAddresses(char * fileName);
bool readAddress(address * addressList, int size, char * fileName);
void printMenu();
int searchAddressID(address * addressList, int ID, int size);
bool readEmployee(allRecords * &recordList, address * addressList, char * fileNameEmployee, int numAddresses);

int address::counter = 0;
int employee::counter = 0;

int main()
{
    allRecords recordList;
    char filenameAddress[] = "addresses.txt";
    int numAddresses = countNumAddresses(filenameAddress);
    address * addressList = nullptr;
    addressList = new address[numAddresses];
    readAddress(addressList, numAddresses, filenameAddress);
    
    char fileNameEmployee[] = "employees.txt";
    readEmployee(recordList, addressList, fileNameEmployee, numAddresses);
    recordList.show();
    
    if (addressList != nullptr) {
        delete [] addressList;
    }
    
    // record person;
    // person.setAddress(1);
    // person.setName("Hello");
    // person.setStreetNum(1234);
    // person.setStreetName("Drive");
    // person.setCityName("Garland");
    // person.setState("TX");
    // person.setZip(54281);
    // person.setDepartment((DEPARTMENT) 2);
    // allRecords recordList;
    // recordList.append(&person);
    // record *person2 = new record(person);
    // person2->setName("Robert");
    // recordList.append(person2);
    // recordList.show();
    
    return 0;
}

bool readEmployee(allRecords * &recordList, address * addressList, char * fileNameEmployee, int numAddresses) {
    ifstream input;
    input.open(fileNameEmployee);
    if(!input.is_open()) {
        cout << "File could not open" << endl;
        return false;
    }
    while (!input.eof()) {
        record * newPerson = new record();
        int newAddressID, newDep;
        char buffer[1000];
        input >> newAddressID;
        input.getline(buffer, 1000);
        input >> newDep;
        newPerson->setAddress(newAddressID);
        newPerson->setName(buffer);
        newPerson->setDepartment((DEPARTMENT) newDep);
        //newPerson.display();
        if (newAddressID != 0) {
            int addressIndex = searchAddressID(addressList, newAddressID, numAddresses);
            if (addressIndex != -1) {
                newPerson->setStreetNum(addressList[addressIndex].getStreetNum());
                newPerson->setStreetName(addressList[addressIndex].getStreetName());
                newPerson->setState(addressList[addressIndex].getState());
                newPerson->setZip(addressList[addressIndex].getZip());
            }
        }
        //newPerson.display();
        recordList->append(newPerson);
    }
    return true;
}

//searches the dynamic array of addresses to find matching ID
int searchAddressID(address * addressList, int ID, int size) {
    for (int i = 0; i < size; i ++) {
        if (addressList[i].getAddress() == ID) {
            return i;
        }
    }
    return -1;
}

//reads the given addresses into array of possible addresses
bool readAddress(address * addressList, int size, char * fileName) {
    ifstream input;
    input.open(fileName);
    if(!input.is_open()) {
        cout << "File could not open" << endl;
        return false;
    }
    int counter = 0;
    while(!input.eof()) {
        int ID, street, zip;
        char buffer[1000];
        input >> ID ;
        input >> street;
        
        input.getline(buffer, 1000);
        addressList[counter].setAddressID(ID);
        addressList[counter].setStreetNum(street);
        addressList[counter].setStreetName(buffer);
        input.getline(buffer,1000);
        addressList[counter].setCityName(buffer);
        input >> buffer;
        addressList[counter].setState(buffer);
        input >> zip;
        addressList[counter].setZip(zip);
        counter++;
    }
    input.close();
    return true;
}

//counts the number of given addresses
int countNumAddresses(char * fileName) {
    ifstream input;
    input.open(fileName);
    if(!input.is_open()) {
        cout << "File could not open" << endl;
        return -1;
    }
    int counter = 0;
    char buffer[1000];
    while(!input.eof()) {
        input.getline(buffer, 1000);
        input.getline(buffer, 1000);
        input.getline(buffer, 1000);
        counter++;
    }
    input.close();
    return counter;
}


//prints menu for user
void printMenu() {
    cout << "a.  Enter address file location" << endl;
    cout << "b.  Enter employee file location" << endl;
    cout << "c.  Read files"<< endl;
    cout << "d.  Display data" << endl;
    cout << "e.  Search" << endl;
    cout << "        i.  ID" << endl;
    cout << "       ii.  Zipcode" << endl;
    cout << "      iii.  City" << endl;
    cout << "f.  Sort" << endl;
    cout << "        i.  ID" << endl;
    cout << "       ii.  Zipcode" << endl;
    cout << "      iii.  City" << endl;
    cout << "g.  Display" << endl;
    cout << "h.  Exit" << endl;
}

void showAddress(address thisAddress) {
    
}

void showEmployee(employee thisEmployee) {
    
}


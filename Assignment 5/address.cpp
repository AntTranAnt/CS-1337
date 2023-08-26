#include "address.h"
#include <iostream>

using namespace std;

int address::getAddress() const {return addressID;}
int address::getStreetNum() const {return streetNum;}
int address::getZip() const {return zipCode;}
char * address::getStreetName() const {return streetName;}
char * address::getCityName() const {return cityName;}
char * address::getState() const {return state;}

void address::setAddressID(int newAddress) {
    addressID = newAddress;
}
void address::setStreetNum(int newStreetNum) {
    streetNum = newStreetNum;
}
void address::setZip(int newZip) {
    zipCode = newZip;
}
void address::setStreetName(const char * newStreetName) {
    setName(newStreetName, streetName);
}
void address::setCityName(const char * newCityName) {
    setName(newCityName, cityName);
}
void address::setState(const char * newState) {
    setName(newState, state);
}
void address::setName(const char * newName, char * &name) {
    if (name != nullptr) {
        delete [] name;
    }
    int size = 0;
    while (newName[size++] != '\0'); //nullptr is at newName[size]
    name = new char[size];
    int count = 0;
    while (count < size) {
        name[count] = newName[count];
        count++;
    }
    name[count] = '\0';
}

void address::display() {
    if (addressID != 0) {
        cout << getAddress() << endl;
    }
    if (streetNum != 0) {
        cout << streetNum << endl;
    }
    if (streetName != nullptr) {
        cout << streetName << endl;
    }
    if (cityName != nullptr) {
        cout << getCityName() << endl;
    }
    if (state != nullptr) {
        cout << getState() << endl;
    }
    if (zipCode != 0) {
        cout << getZip() << endl;
    }
    
}

address::address() {
    addressID = 0;
    streetNum = 0;
    zipCode = 0;
    streetName = nullptr;
    cityName = nullptr;
    state = nullptr;
    counter++;
}
address::address(const address &o) {
    addressID = o.addressID;
    streetNum = o.streetNum;
    zipCode = o.zipCode;
    streetName = nullptr;
    cityName = nullptr;
    state = nullptr;
    setStreetName(o.streetName);
    setCityName(o.cityName);
    setState(o.state);
    counter++;
}
address::~address() {
    counter--;
    if (streetName != nullptr) {
        delete [] streetName;
    }
    if (cityName != nullptr) {
        delete [] cityName;
    }
    if (state != nullptr) {
        delete [] state;
    }
}

/*
Anthony Tran
CS 1337-501
10/26/2022

1. how to return a ponter to a structure
2. how to read in values
*/

#include <iostream>
#include <fstream> 
#include <cmath>
#include <iomanip>
#include <stdio.h>

using namespace std;

enum ServiceType {POLICE_DEPARTMENT, HOSPITAL, FIRE_STATION};

struct services {
    int serviceID, numCalls;
    double xCord, yCord;
    char cityName[50];
    ServiceType thisService;
};

char printMenu();
int getNumberOfRecords(char *);
int findLen(char *buffer);
bool readInputFiles(services *serviceList, int size, char *);
services * getNearestService(services *, int, double, double);
services * getNearestPoliceDepartment(services *, int, double, double);
services * getNearestHospital(services *, int, double, double);
services * getNearestFireStation(services *, int, double, double);
void printClosestService(services *serviceList, ServiceType closestService);
void sortArray(services *serviceList, int size);

const double MAX_CORD = 180; //180 is the largest possible coordinate on Earth

int main()
{
    
    char inputName[] = "serviceInfo.txt";
    int numServices = getNumberOfRecords(inputName);
    if (numServices > 0) {
        services *serviceList = nullptr;
        serviceList = new services[numServices];
        if (!readInputFiles(serviceList, numServices, inputName)) { 
            cout << "File could not be read" << endl; //File couldn't be open
            return -1;
        }
        char choice = printMenu();

        double xCord, yCord;
        bool cordCheck = false; //Checks if user has entered coordinates.
        while(choice != 'f') { //As long as user hasn't entered f, loop through menu
            if (choice == 'a') { //if user entered a, ask for coordinates.
                cout << "Enter x-coordinate: ";
                cin >> xCord;
                cout << "Enter y-coordinate: ";
                cin >> yCord;
                cordCheck = true;
            } else if (choice != 'f') { //only allow access to b, c, d, e if coords has been entered.
                if (!cordCheck) {
                    cout << "Please enter coordinates first before choosing options b, c, d, e" << endl;
                } else {
                    services *servicePtr;
                    ServiceType closestService;
                    if (choice == 'b') {
                        servicePtr = getNearestService(serviceList, numServices, xCord, yCord);
                        closestService = servicePtr->thisService;
                        cout << "(" << closestService << ") ";
                        printClosestService(servicePtr, closestService);
                    } else if (choice == 'c') {
                        servicePtr = getNearestPoliceDepartment(serviceList, numServices, xCord, yCord);
                        closestService = servicePtr->thisService;
                        cout << "(" << closestService << ") ";
                        printClosestService(servicePtr, closestService);
                    } else if (choice == 'd') {
                        servicePtr = getNearestHospital(serviceList, numServices, xCord, yCord);
                        closestService = servicePtr->thisService;
                        cout << "(" << closestService << ") ";
                        printClosestService(servicePtr, closestService);
                    } else if (choice == 'e') {
                        servicePtr = getNearestFireStation(serviceList, numServices, xCord, yCord);
                        closestService = servicePtr->thisService;
                        cout << "(" << closestService << ") ";
                        printClosestService(servicePtr, closestService);
                    }
                }
            }
            choice = printMenu();
        }
        sortArray(serviceList, numServices);
        delete [] serviceList;
    } else {
        cout << "Either the file does not exist, or there are 0 services" << endl;
    }
    return 0;
}

//Prints a menu and returns the user's inputed choice
char printMenu() {
    cout << "\na) Enter your location (x, y)" << endl;
    cout << "b) Find the nearest service" << endl;
    cout << "c) Find the nearest POLICE DEPARTMENT" << endl;
    cout << "d) Find the nearest HOSPITAL" << endl;
    cout << "e) Find the nearest FIRE STATION" << endl;
    cout << "f) Exit" << endl;
    char choice;
    cin >> choice; 
    if (!(choice >= 'a' && choice <= 'f')) {
        cout << "\nInvalid input\nEnter only a, b, c, d, e, or f" << endl;
        choice = printMenu();
    }
    return choice;
}

//returns the number of records in the file, or -1 if file wasn't found
int getNumberOfRecords(char *inputName) {
    ifstream input;
    input.open(inputName);
    int counter;

    if(!input.is_open()) {
        cout << "file could didn't open" << endl;
        return -1;
    }
    while (!input.eof()) {
        char buffer[50];
        input.getline(buffer, 50);
        if (findLen(buffer) > 0) { //only increments if it isn't a empty line
            counter++;  
        }
    }
    input.close();
    return counter;
}

//returns length of c-string
int findLen(char *buffer) {
    int counter;
    while (buffer[counter] != '\0') {
        counter++;;
    }
    return --counter; //removes empty char at end of c-string
}

//reads the input file and inserts info into the array of services
//returns false if failure occured and true otherwise.
bool readInputFiles(services *serviceList, int size, char *inputName) {
    ifstream input;
    input.open(inputName);
    int counter;
    if(!input.is_open()) {
        cout << "file could didn't open" << endl;
        return false;
    }
    while (!input.eof() && counter < size) {
        input >> serviceList[counter].serviceID;
        input >> serviceList[counter].xCord;
        input >> serviceList[counter].yCord;
        int temp;
        input >> temp;
        serviceList[counter].thisService = (ServiceType) temp;
        input >> serviceList[counter].cityName;
        input >> serviceList[counter].numCalls;
        counter++;
    }
    return true;
    
}

//Returns a pointer that points to the service inside the servistList[] array that is closest to the (x, y) cord
services * getNearestService(services *serviceList, int size, double xCord, double yCord) {
    int counter, index;
    double min = MAX_CORD;
    while (counter < size) {
        double distance = sqrt(pow((xCord - serviceList[counter].xCord), 2.0)
                            + pow((yCord - serviceList[counter].yCord), 2.0));
        if (distance < min) {
            min = distance;
            index = counter;
        }
        counter++;
    }
    if (index < 0 || index >= size) { //returns nullptr if out of bounds of array.
        return nullptr;
    }
    return &serviceList[index];
}

//Prints the closest service along with the coordinates and cityname.
void printClosestService(services *serviceList, ServiceType closestService) {
    cout << "Closest service is ";
    if (closestService == 0) {
        cout << "POLICE DEPARTMENT ";
    } else if (closestService == 1) {
        cout << "HOSPITAL ";
    } else {
        cout << "FIRE STATION ";
    }
        cout << "at (" << serviceList->xCord << ", " << serviceList->yCord << "), in the city of "
        << serviceList->cityName << endl;
}

//returns pointer to nearest police department
services * getNearestPoliceDepartment(services *serviceList, int size, double xCord, double yCord) {
    int counter, index;
    double min = MAX_CORD;
    while (counter < size) {
        if (serviceList[counter].thisService == POLICE_DEPARTMENT) {
            double distance = sqrt(pow((xCord - serviceList[counter].xCord), 2.0)
                            + pow((yCord - serviceList[counter].yCord), 2.0));
            if (distance < min) {
                min = distance;
                index = counter;
            }
        }
        counter++;
    }
    if (index < 0 || index >= size) { //returns nullptr if out of bounds of array.
        return nullptr;
    }
    return &serviceList[index];
}

//points to nearest hospital
services * getNearestHospital(services *serviceList, int size, double xCord, double yCord) {
    int counter, index;
    double min = MAX_CORD;
    while (counter < size) {
        if (serviceList[counter].thisService == HOSPITAL) {
            double distance = sqrt(pow((xCord - serviceList[counter].xCord), 2.0)
                            + pow((yCord - serviceList[counter].yCord), 2.0));
            if (distance < min) {
                min = distance;
                index = counter;
            }
        }
        counter++;
    }
    if (index < 0 || index >= size) { //returns nullptr if out of bounds of array.
        return nullptr;
    }
    return &serviceList[index];
}

//returns pointer to nearest fire station
services * getNearestFireStation(services *serviceList, int size, double xCord, double yCord) {
    int counter, index;
    double min = MAX_CORD;
    while (counter < size) {
        if (serviceList[counter].thisService == FIRE_STATION) {
            double distance = sqrt(pow((xCord - serviceList[counter].xCord), 2.0)
                            + pow((yCord - serviceList[counter].yCord), 2.0));
            if (distance < min) {
                min = distance;
                index = counter;
            }
        }
        counter++;
    }
    if (index < 0 || index >= size) { //returns nullptr if out of bounds of array.
        return nullptr;
    }
    return &serviceList[index];
}

//sorts the array in increasing order of service type
//Sends each array entry into a new file.
void sortArray(services *serviceList, int size) {
    int minVal, index;
    for (int i = 0; i < size - 1; i++) {
        index = i;
        minVal = serviceList[i].thisService;
        for (int j = i + 1; j < size; j++) {
            int varOne = serviceList[j].thisService;
            int varTwo = minVal;
           
            if (varOne < varTwo) {
                minVal = serviceList[i].thisService;
                index = j;
            }
        }
        services tempService;
        tempService.serviceID = serviceList[i].serviceID;
        tempService.xCord = serviceList[i].xCord;
        tempService.yCord = serviceList[i].yCord;
        tempService.thisService = serviceList[i].thisService;
        for(int len = 0; len < 50; len++) {
            tempService.cityName[len] = serviceList[i].cityName[len];
        }
        tempService.numCalls = serviceList[i].numCalls;
        serviceList[i].serviceID = serviceList[index].serviceID;
        serviceList[i].xCord = serviceList[index].xCord;
        serviceList[i].yCord = serviceList[index].yCord;
        serviceList[i].thisService = serviceList[index].thisService;
        for(int len = 0; len < 50; len++) {
            serviceList[i].cityName[len] = serviceList[index].cityName[len];
        }
        serviceList[i].numCalls = serviceList[index].numCalls;


        serviceList[index].serviceID = tempService.serviceID;
        serviceList[index].xCord = tempService.xCord;
        serviceList[index].yCord = tempService.yCord;
        serviceList[index].thisService = tempService.thisService;
        for(int len = 0; len < 50; len++) {
            serviceList[index].cityName[len] = tempService.cityName[len];
        }
        serviceList[index].numCalls = tempService.numCalls;
    }

    ofstream output;
    char fileName[] = "sortedServiceInfo.txt";
    output.open(fileName);
    for (int i = 0; i < size; i++) {
        output << serviceList[i].serviceID << " " << serviceList[i].xCord << " " << serviceList[i].yCord
        << " " << serviceList[i].thisService << " " << serviceList[i].cityName << " " << serviceList[i].numCalls << endl;
    }
}



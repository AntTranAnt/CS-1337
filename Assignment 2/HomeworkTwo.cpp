/*
Anthony Tran
CS 1337-501
10/14/2022
 
This program was written to read a txt file containing a list of cities no more than 1000. The program then
displays a menu ranging from a, b, c, d, e, or f. The program then asks the user to select a choice. a) prints
the list of cities between[min, max]. b) prints the list of cities with the group n. c) asks user to input city
1. d) asks user to input city 2. e) conputes the distance between city 1 and 2. f) Exits out of the program

Pseudocode:
Create city structure.
Create input object and link in filename.
open file
if file didn't open
    return a error
while not reaching the end of the file
    input the id, group, xcord, ycord, and cityname
    increment counter to keep track of size
print menu for user and ask for input
while the input isn't 'f'
    if input is 'a'
        ask for the minimum and maximum
        check if the minimum and maximum satisfy conditions
        loop through array of cityList and print out the cities that had ID's between [min,max]
    if input is 'b'
        ask for the group character
        check if group character between [A,Z]
        loop thorugh array of cityList and print out the cities with group n
    if input is 'c' 
        ask user for city ID
        check if city ID is found or if it equals the other city ID
    if input is 'd'
        ask user for city ID
        check if city ID is found or if it equals the other city ID
    if input is 'e'
        use city one ID and city two ID to search cityList and return the index of those two cities
        use the xcord and ycord from the index of the two cities to calculate distance
        print out the distance.
    display the menu again and ask user for input.
program ends when user enters 'f'.
*/

#include <iostream>
#include <fstream> 
#include <cmath>
#include <iomanip>
#include <stdio.h>

using namespace std;

const int NOT_FOUND = -1; //Anything with an index of -1 is considered not found

struct city { //structure to represent a city and its ID, xcord, ycord, group, and cityname.
    int ID;
    double xCord, yCord;
    char group;
    char cityName[50];
};

char printMenu();
void printByID(city cityList[], int size);
void printByGroup(city cityList[], int size);
int askForID();
int askForCityID(city cityList[], int size, int otherCity);
void printCity(city cityList[], int index);
int search(city cityList[], int size, int target);
double calculateDistance(city cityList[], int cityOne, int cityTwo);

int main()
{
    const int maxSize = 1000;
    city cityList[1000];
    char inputName[] = "cityList.txt";
    ifstream input;
    input.open(inputName);

    if(!input.is_open()) {
        cout << "didn't open" << endl;
        return NOT_FOUND;
    }

    int counter = 0;
    while (!input.eof()) {
        input >> cityList[counter].ID;
        input >> cityList[counter].group;
        input >> cityList[counter].xCord;
        input >> cityList[counter].yCord;
        input.getline(cityList[counter].cityName, 50);
        counter++;
    }
    int cityOneID = NOT_FOUND;
    int cityTwoID = NOT_FOUND;
    char choice = printMenu();
    while(choice != 'f') {
        if (choice == 'a') {
            printByID(cityList, counter);
        } else if ( choice == 'b') {
            printByGroup(cityList, counter);
        } else if (choice == 'c') {
            cityOneID = askForCityID(cityList, counter, cityTwoID);
        } else if (choice == 'd') {
            cityTwoID = askForCityID(cityList, counter, cityOneID);
        } else if (choice == 'e') {
            int cityOneIndex = search(cityList, counter, cityOneID);
            int cityTwoIndex = search(cityList, counter, cityTwoID);
            double distance = calculateDistance(cityList, cityOneIndex, cityTwoIndex);
            if (distance != NOT_FOUND) {
                cout << "Linear Distance: " << setw(8) << fixed << setprecision(2) << left << distance << endl;
            }
        }
        choice = printMenu();
    }
    
    return 0;
}

//Prints the menu for the user and returns their input.
char printMenu() {
    cout << endl;
    cout << "a. Display cities by ID range" << endl;
    cout << "b. Display cities by group" << endl;
    cout << "c. Enter City 1" << endl;
    cout << "d. Enter City 2" << endl;
    cout << "e. Compute Distance" << endl;
    cout << "f. Exit" << endl;
    char input;
    cin >> input;
    if (!(input >= 'a' && input <= 'f')) {
        cout << "\nInvalid input\nEnter only a, b, c, d, e, or f" << endl;
        input = printMenu();
    }
    return input;
}

//prints the list of cities between the inputed values of [min, max]
void printByID(city cityList[], int size) {
    int min, max;
    cout << "Enter minimum ID: ";
    min = askForID();
    cout << "Enter maximum ID: ";
    max = askForID();
    while ((min >= max) || (min <= 0) || (max <= 0)) {
        cout << "Requirements: min < max, min > 0, max > 0\n" << endl;
        cout << "Enter minimum ID: ";
        min = askForID();
        cout << "Enter maximum ID: ";
        max = askForID();
    }
    int counter = 0;
    while (counter < size) {
        if (cityList[counter].ID >= min && cityList[counter].ID <= max) {
            printCity(cityList, counter);
        }
        counter++;
    }
}

//prints the list of cities based on the inputed group.
void printByGroup(city cityList[], int size) {
    char choice;
    cout << "Enter a group: ";
    cin >> choice;
    while (!(choice >= 'A' && choice <= 'Z')) {
        cout << "Requirements: Enter A-Z (Must be capitalized)\n" << endl;
        cout << "Enter a group: ";
        cin >> choice;
    }
    int counter = 0;
    while (counter < size) {
        if (cityList[counter].group == choice) {
            printCity(cityList, counter);
        }
        counter++;
    }
}

//Prints out the information of a city based on the index argument.
//In format of ID group xcord ycord cityname
void printCity(city cityList[], int index) {
    cout << setw(6) << left << cityList[index].ID;
    cout << setw(8) << cityList[index].group << left;
    cout << setw(10) << fixed << setprecision(2) << cityList[index].xCord << left;
    cout << setw(10) << fixed << setprecision(2) << cityList[index].yCord << left;
    cout << setw(30) << cityList[index].cityName << left << endl;;
}

//returns cin value for ID
int askForID() {
    int ID;
    cin >> ID;
    return ID;
}

//asks for ID and sees if ID exists and if ID equals the ID of the other city.
int askForCityID(city cityList[], int size, int otherCity) {
    int city;
    cout << "Enter city ID: ";
    cin >> city;
    while (search(cityList, size, city) == NOT_FOUND || city == otherCity) {
                if (search(cityList, size, city) == NOT_FOUND) {
                    cout << "The ID: " << city << " does not exist. " << endl;
                } else if (city == otherCity) {
                    cout << "The ID you have entered cannot match the other city ID of " << otherCity << endl;
                }
                city = askForCityID(cityList, size, otherCity);
    }
    return city;
}

//returns Index if found, else returns not found (-1).
int search(city cityList[], int size, int target) {
    int counter = 0;
    while (counter < size) {
        if (cityList[counter].ID == target) {
            return counter;
        }
        counter++;
    }
    return NOT_FOUND;
}

//returns the linear distance between city one and city two.
double calculateDistance(city cityList[], int cityOne, int cityTwo) {
    if (cityOne == NOT_FOUND || cityTwo == NOT_FOUND) {
        cout << "Please enter ID's for city one and city two before computing the distance" << endl;
        return NOT_FOUND;
    } else {
        int squared = 2;
        double xDiff = pow((cityList[cityOne].xCord) - cityList[cityTwo].xCord, squared);
        double yDiff = pow((cityList[cityOne].yCord) - cityList[cityTwo].yCord, squared);
        double distance = sqrt(xDiff + yDiff);
        return distance;
    }
}

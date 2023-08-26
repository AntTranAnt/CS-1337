/*
Anthony Tran
CS 1337-501
9/22/2022
 
This program was writting to ask the user for the min, max, sample size(n),
and delta. The program will then check for input validation, if the validation
doesn't meet the expected values, the program will stop. After receiving the
values, the program will then give n random values in a table with 4 columns.
Afterwards, the program will compute the average, standard deviation, and
variation of the random values generated.
*/
 
#include <iostream>
#include <cmath>
#include <iomanip>
#include <stdio.h>
 
int main() {
    int min, max, sample;
    double delta, total, average, standardDev, variance;
    std::cout << "Enter the minimum value: ";
    std::cin >> min;
    std::cout << "Enter the maximum value: ";
    std::cin >> max;
    if (min >= max) {
        std::cout << "Error: min must be greater than max";
        return 1;
    }
   
    std::cout << "Enter the sample size: ";
    std::cin >> sample;
    if (sample < 1 || sample > 80) {
        std::cout << "Error: sample must be greater than 1 and less than 80";
        return 2;
    }
   
    std::cout << "Enter the smallest difference(delta): ";
    std::cin >> delta;
    if (delta > abs(max - min)) {
        std::cout << "Error: delta must be less than the difference between max and min";
        return 3;
    }
   
    min /= delta;
    max /= delta;
 
    int counter = 0;
    for (int i = 0; i < sample; i++) {
       
        int upperBound = max - min + 1;
        double temp = (double)(min + (rand() % upperBound))*delta;
        total += temp;
        variance += pow(temp, 2);
       
        if (i == sample - 1) {
            std::cout << std::setw(10) << std::setprecision(3) << temp << std::endl;
        } else if (counter < 3) {
            std::cout << std::setw(10) << std::setprecision(3) << temp;
            counter++;
        } else {
            std::cout << std::setw(10) << std::setprecision(3) << temp << std::endl;
            counter = 0;
        }
    }
 
    average = total / sample;
    variance = (variance - average*average*sample)/sample;
    standardDev = sqrt(variance);
   
    std::cout << "Average:            " << std::setw(10) << std::setprecision(3) << average << std::endl;
    std::cout << "Standard Deviation: " << std::setw(10) << std::setprecision(3) << standardDev << std::endl;
    std::cout << "Variance:           " << std::setw(10) << std::setprecision(3) << variance << std::endl;
}


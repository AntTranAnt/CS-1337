/*

*/

#include <iostream>
#include <fstream> 
#include <cmath>
#include <iomanip>
#include <stdio.h>

using namespace std;

enum SERVICE_TYPE {HOSPITAL, FIRE_STATION, POLICE_STATION};

class service {
    public:
        int id;
        double x, y;
        SERVICE_TYPE st;
        char * cityname;
        int calls;

        void setServiceType(int j) {
            st = (SERVICE_TYPE) j;
        }

        void setname(const char *src) {
            //1 release any memory
            if (cityname != nullptr) {
                delete [] cityname;
            }
            //2 find length of src
            int count = 0;
            while (src[count] != '\0') {
                count++;
            }
            //3 allocate memory for cityname(every char + null char)
            cityname = new char[count + 1];
            //4 create copy of each element in src
            int count = 0;
            while (src[count] != '\0') {
                cityname[count] = src[count];
                count++;
            }
            cityname[count] = '\0';

        }

        service() {
            cityname = nullptr;
        }
        ~service() {
            if(cityname != nullptr) {
                delete [] cityname;
            }
        }
}

int main() {

}

int getNumberOfLines(const char *fn) {
    ifstream in;
    in.open(fn);
    if (!in.is_open()) {
        return -1;
    }
    int counter = 0;
    char buffer[1000];
    while(!in.eof()) {
        in.getline(buffer, 1000);
        counter++;
    }
    in.close();
    return counter;
}

//& allows you to pass by reference
int readInputFile(const char *fn, service *& data) {
    ifstream in;
    in.open(fn);
    if (!in.is_open()) {
        return -1;
    }
    int counter = 0;
    int dummy;
    char buffer[100];

    while(!in.eof()) {
        in >> data[counter].id >> data[counter].x >> data[counter].y >> dummy;
        data[counter].setServiceType(dummy);
        in >> buffer;
        data[counter].setname(buffer);
        in >> data[counter].calls;
        counter++;
    }
    in.close();
}

service * getNearestService(service * data, int N, double ux, double uy) {
    double distance; //current distance
    double minDistance = 0;
    int maxIndex;
    service *tmp; //index using pointers

    for (int i = 0; i < N; i++) {
        distance = sqrt((data[i].x - ux) * (data[i].x - ux) + (data[i].y - uy) * (data[i].y - uy));
        if (distance > minDistance) {
            minDistance = distance;
            maxIndex = i;
            tmp = &data[i];
        }
    }

    return &data[maxIndex];
}

void sortArray (service *& data, int N) {
    bool swap;
    do {
        swap = false;
        for (int i = 0; i < N-1; i++) {
            if (data[i].st >data[i+1].st) {
                swap = true;
                service tmp;

                tmp.id = data[i].id;
                tmp.x = data[i].x;
                tmp.y = data[i].y;
                tmp.st = data[i].st;
                tmp.calls = data[i].calls;
                tmp.setname(data[i].cityname);
                //do data[i] = data[i+1]
                //do data[i+1] = temp;
            }
        }

    } while (swap);
}

void writeToFile(service *data, int N, const char *fn) {
    ofstream out;
    out.open(fn);
    if(!out.is_open()) {
        return; //return exits out of functions, exit closes program
    }
}
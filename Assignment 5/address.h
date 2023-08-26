#ifndef ADDRESS_H
#define ADDRESS_H

class address {
    private:
        int addressID, streetNum, zipCode;
        char * streetName;
        char * cityName;
        char * state;
        static int counter;
    public:
        //getters
        int getAddress() const;
        int getStreetNum() const;
        int getZip() const;
        char * getStreetName() const;
        char * getCityName() const;
        char * getState() const;
        
        //setters
        void setAddressID(int newAddress);
        void setStreetNum(int newStreetNum);
        void setZip(int newZip);
        void setStreetName(const char * newStreetName);
        void setCityName(const char * newCityName);
        void setState(const char * newState);
        void setName(const char * newName, char * &name);
        
        //displays all attributes in address class
        void display();
        //displays all attributes in address class using friend function
        friend void showEmployee(address thisAddress);
        
        //constructor and destructor
        address();
        //copy constructor
        address(const address &o);
        ~address();
};

#endif
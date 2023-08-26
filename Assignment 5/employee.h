#ifndef EMPLOYEE_H
#define EMPLOYEE_H

enum DEPARTMENT {DEFAULT, SALES, CUSTOMER_SERVICE, PRODUCTION, HUMAN_RESOURCES,
    ACCOUNTING, RESEARCH_AND_DEVELOPMENT};
class employee {
    private:
        char * name;
        int addressID;
        DEPARTMENT dep;
        static int counter;
    public:
        //getters
        char * getName() const;
        int getAddress() const;
        DEPARTMENT getDepartment() const;
        
        //setters
        void setName(const char * newName);
        void setAddress(int newAddress);
        void setDepartment(DEPARTMENT newDepartment);
        
        //displays all attributes in employee class.
        void display();
        //displays all attributes in employee class using friend function.
        friend void showEmployee(employee thisEmployee);
        
        //constructor and destructor
        employee();
        //copy constructor
        employee(const employee &o);
        ~employee();
};

#endif
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

class person {
    int id;
    char * name;
    public:
        int getID() const {
            return id;
        }
        char * getName() const{
            return name;
        }
        void setID(int newID) {
            id = newID;
        }
        void setName(const char * newName) {
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
        virtual void show() {
            cout << "(" << id << ", ";
            if (name == nullptr) {
                cout << "NONAME)" << endl;
            } else {
                cout << getName() << ")" << endl;
            }
        }
        person() {
            id = 0;
            name = nullptr;
        }
        person(int i, const char * n) {
            id = i;
            setName(n);
        }
        ~person() {
            if (name != nullptr) {
                delete [] name;
            }
        }
};

enum DEPARTMENT {BMEN = 95,CS = 100, ECE = 105, MECH = 110};

class record : public person {
    protected:
        DEPARTMENT dep;
    public:
        DEPARTMENT getDep() const {return dep;}
        void setMajor(int d) {
            dep = (DEPARTMENT) d;
        }
        void show() {
            cout << "(" << getID() << ", ";
            if (getName() == nullptr) {
                cout << "NONAME" << endl;
            } else {
                cout << getName();
            }
            cout << ", ";
            if (dep == BMEN) {
                cout << "BMEN";
            } else if (dep == CS) {
                cout << "CS";
            } else if (dep == ECE) {
                cout << "ECE";
            } else {
                cout << "MECH";
            }
            cout << ")" << endl;
        }
        record(int i, const char * n, int m):person(i, n) {
            setMajor(m);
        }
};

class node {
    public:
        record * data;
        node * next;
        static int counter;
        node() {
            data = nullptr;
            next = nullptr;
            counter++;
        }
        ~node() {
            if (data != nullptr) {
                delete data;
            }
            counter--;
        }
};

int node::counter = 0;

void addNode(node * &head, record * nr) {
    node * nn = new node();
    nn->data = nr;
    nn->next = nullptr;

    if(head == nullptr) {
        head = nn;
    } else {
        node*iter = head;
        while (iter->next != nullptr) {
            iter = iter->next;
        }
        iter->next = nn;
    }   
}

void show(node * head) {
    node * iter = head;
    while(iter != nullptr) {
        iter->data->show();
        cout << "->" << node::counter << endl;
        iter = iter->next;
    }
}

int getSize(node * h) {
    if (h == nullptr) {
        return 0;
    }
    return 1 + getSize(h->next);
}

int main() {
    // node* n = new node();

    //   n->data->show();

    //   delete n;

    //   return 0;
    
    
    const char* names[] = { "John Smith", "Homer Simpson", "Jack Sparrow" };

       int ids[] = { 1020, 2340, 6789 };

       DEPARTMENT deps[] = { ECE, MECH, CS };

       node* h=nullptr;

       for (int i = 0; i < sizeof(names)/4; i++) {

              record* r = new record(ids[i], names[i], deps[i]);

              addNode(h, r);

       }

       show(h);

       return 0;
}

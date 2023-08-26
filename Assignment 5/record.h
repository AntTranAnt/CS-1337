#ifndef RECORD_H
#define RECORD_H


class record: public address, public employee {
    public: 
        record * next;
        void display();
        record();
        
};

#endif
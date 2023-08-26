#ifndef BANK_H
#define BANK_H

enum TRANSACTION_TYPE {
    DEPOSIT, WITHDRAWAL
};

class Bank {
    private:
        long long int accountNumber;
        TRANSACTION_TYPE type;
        double amount;
        char * owner;
    public:
        //getters
        long long int getAccountNum() const;
        TRANSACTION_TYPE getType() const;
        double getAmount() const;
        char * getOwnerName() const;

        //setters
        void setAccountNum(long long int newNum);
        void setType(TRANSACTION_TYPE newType);
        void setAmount(double newAmount);
        void setName(const char * newName);

        void withdraw(double withDrawAmt);
        void deposit(double depositAmt);
        
        friend void accountInfo(Bank thisBank);

        Bank();
        Bank(long long int newAccountNum, double newBalance);
        Bank(long long int newAccountNum, double newBalance, char * newOwner);

        ~Bank();

};
#endif
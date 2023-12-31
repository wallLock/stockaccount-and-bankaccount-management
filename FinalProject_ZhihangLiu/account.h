#ifndef ACCOUNT_H
#define ACCOUNT_H

class account{
    private:
        double balance;
    public:
        void setbalance(double n){balance = n;}
        double getbalance(){return balance;}
        virtual void displayHistory()=0;
        virtual ~account(){}
};



#endif
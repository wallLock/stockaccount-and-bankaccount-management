#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H
#include "account.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
using namespace std;



class bankaccount: public account{
    private:
        struct Hnode{
            string event;
            double amount;
            string date;
            double storedbalance;
            Hnode* prev;
            Hnode* next;
        };


        Hnode* head; //used for storing the history of account
    public:
        void viewCurrentBalance();
        
        bankaccount(const string historyFilename, const string balanceFilename);

        ~bankaccount() override;

        void deposit(double amount );

        void withdraw(double amount );

        void append(string event, double amount, string date, double balance);

        void initializeHistory(const string &filename); //load the txt file into the hnode so the code will remember the balance since last time
        
        void displayHistory() override; //convert template method to display history
            
        void storetoHistory(const string& filename);

        void storeBalance(const string& filename); //use a separate file to store the case balance 
            
        void initializeBalance();

        void initializeBalanceFromTxt(const string &filename);


};


#endif
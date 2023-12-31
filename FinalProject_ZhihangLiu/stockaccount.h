#ifndef STOCKACCOUNT_H
#define STOCKACCOUNT_H
#include "account.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include "bankaccount.h"
using namespace std;

struct Pnode{ //this is used for storing protoflio
            string symbol;
            double price;
            int shares;
            double totalValue;
            Pnode* prev;
            Pnode* next;
        };

struct HTnode{ //This is used for store history of actions
            string event;
            string symbol;
            int shares;
            double price;
            double totalValue;
            string Time;
            HTnode *prev;
            HTnode* next;
        };

class SortingStrategy {
public:
    virtual void sort(Pnode*) = 0;
    virtual ~SortingStrategy() {}
};

class BubbleSort: public SortingStrategy { //strategy for sort: bubblesort
public:
    void sort(Pnode* head) override {
        cout<<"bubblesort kick in\n";
        if (head == nullptr || head->next == nullptr){
            cout<<"head is null pointer";
            return;
        }
            

        Pnode *end = nullptr, *temp;
        bool swapped = true;

        while (swapped){
            swapped = false;
            temp = head;

            while (temp->next != end) {
                if (temp->totalValue < temp->next->totalValue) {
                    cout<<temp->totalValue<<" "<<temp->next->totalValue<<endl;
                    swap(temp, temp->next);
                    swapped = true;
                }
                temp = temp->next;
            }
            end = temp;

        } 
    }


    void swap(Pnode* a, Pnode* b) {
        string tempSymbol = a->symbol;
        double tempPrice = a->price;
        int tempShares = a->shares;
        double tempTotalValue = a->totalValue;

        a->symbol = b->symbol;
        a->price = b->price;
        a->shares = b->shares;
        a->totalValue = b->totalValue;

        b->symbol = tempSymbol;
        b->price = tempPrice;
        b->shares = tempShares;
        b->totalValue = tempTotalValue;
    }
};

class SelectionSort:public SortingStrategy { //mergesort method
public:
    void sort(Pnode* head) override{
        if (head == nullptr || head->next == nullptr)
            return;

        Pnode *current = head;
        while (current->next != nullptr) {
            Pnode *maxNode = current;
            Pnode *temp = current->next;

            while (temp != nullptr) {
                if (temp->totalValue > maxNode->totalValue)
                    maxNode = temp;
                temp = temp->next;
            }

            if (maxNode != current)
                swap(current, maxNode);

            current = current->next;
        }
    }


     void swap(Pnode* a, Pnode* b) {
        string tempSymbol = a->symbol;
        double tempPrice = a->price;
        int tempShares = a->shares;
        double tempTotalValue = a->totalValue;

        a->symbol = b->symbol;
        a->price = b->price;
        a->shares = b->shares;
        a->totalValue = b->totalValue;

        b->symbol = tempSymbol;
        b->price = tempPrice;
        b->shares = tempShares;
        b->totalValue = tempTotalValue;
    }
};

class stockaccount:public account{
    private:
        Pnode* Phead;
        HTnode* Hhead;
        SortingStrategy* strategy;
        vector<double> totalPortfolio;
        vector<string> timestamps;
    public:

        void loadGraphinfo(const string filename); //load informtaion for graphing
            
        void storeGraphinfo(const string filename); //store info to txt files.
            
        void displayGraphinfo(const string filename);

        stockaccount(const string balancefilname1, const string historyfilename, const string protofliofilename, const string graphfilename);

        ~stockaccount() override;

        void deletePNodes();

        void deleteHTNodes();

        void setStrategy(SortingStrategy* newstrategy);

        void applysort();

        void displayHistory() override;

        void dispalyProtoflio();

        double calculateCurrentPortfolioValue(); //calculate current time portfolio value balance + share worth
            

        void appendPnode(string symbol, double price, int shares);

        void appenHTnode(const string event, const string symbol, int shares, double price, double totalValue, string time);

        Pnode* searchNodeBySymbol(const string symbolToFind);

        void displayStock(const string filename1, const string filename2); //Used for display the stock information


        void buyShare(const string filename1, const string filename2, bankaccount &bank);


        void sellshare(const string filename1, const string filename2, bankaccount &bank);
            

        void startbalance(const string filename);

        void storeStockbalance(const string filename);

        void loadhistory(const string filename);

        void storehistory(const string filename);

        void loadportofolio(const string filename);

        void storePortfolio(const string filename);
        


};




#endif
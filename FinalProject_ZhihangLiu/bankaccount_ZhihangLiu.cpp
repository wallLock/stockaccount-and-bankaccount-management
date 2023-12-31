#include "bankaccount.h"
using namespace std;

void bankaccount::viewCurrentBalance(){
    cout<<"current balance is "<<getbalance()<<endl;
}

bankaccount::bankaccount(const string historyFilename, const string balanceFilename){
            head = nullptr;
            initializeHistory(historyFilename);
            initializeBalanceFromTxt(balanceFilename);
}

bankaccount::~bankaccount(){
            Hnode* current = head;
            Hnode* next = nullptr;
            while (current != nullptr) {
                next = current->next;
                delete current;
                current = next;
            }
            head = nullptr;
}

void bankaccount::deposit(double amount ){
            double newbalance = getbalance()+amount;
            setbalance(newbalance);
            cout<<"deposit successful"<<endl;

            //get current date like 2023-12-11 year month day
            time_t currentTime = time(nullptr);
            tm* localTime = std::localtime(&currentTime);

            ostringstream oss;
            oss << (localTime->tm_year + 1900) << '-'
            << (localTime->tm_mon + 1) << '-'
            << localTime->tm_mday;

            string currentDate = oss.str();

            append("deposit", amount, currentDate, getbalance()); // store success activity to history nodes
}

void bankaccount::withdraw(double amount ){
            if(amount>getbalance()){
                cout<<"Warning withdraw amount larger than current balance, action cancelled\n";
            }else{
                double newbalance = getbalance()-amount;
                setbalance(newbalance);
                cout<<"Withdraw successful\n";


                //get current date like 2023-12-11 year month day
                time_t currentTime = time(nullptr);
                tm* localTime = std::localtime(&currentTime);

                ostringstream oss;
                oss << (localTime->tm_year + 1900) << '-'
                << (localTime->tm_mon + 1) << '-'
                << localTime->tm_mday;

                string currentDate = oss.str();

                append("withdraw", amount, currentDate, getbalance()); //store success activity to history nodes
            }
}

void bankaccount::append(string event, double amount, string date, double balance){
        Hnode* newNode = new Hnode;
        newNode->event = event;
        newNode->amount = amount;
        newNode->date = date;
        newNode->storedbalance = balance;
        newNode->next = nullptr;

        if (head == nullptr) {
            newNode->prev = nullptr;
            head = newNode;
            return;
        }

            Hnode* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->prev = temp;
}

void bankaccount::initializeHistory(const string &filename){
        ifstream inputFile(filename);
        if (!inputFile.is_open()) {
            cerr<<"Unable to open the file."<<endl;
            return;
        }

        string line;
        while (getline(inputFile, line)) {
            istringstream iss(line);
            string event;
            double amount;
            string date;
            double balance;

            if (iss>>event>>amount>>date>>balance) {
                append(event, amount, date, balance);
            }
        }
        inputFile.close();    
}


void bankaccount::displayHistory(){
    cout<<"Account activities\n";

            Hnode* temp = head;
            while (temp != nullptr) {
            cout<<"Event: "<<temp->event<<", Amount: "<<temp->amount<<", Date: "<<temp->date<<", Current balance: "<<temp->storedbalance<<endl;
            temp = temp->next;
        }

            cout<<"End of Account activity\n";
}

void bankaccount::storetoHistory(const string& filename) {
            ofstream outputFile(filename);
            if (!outputFile.is_open()) {
                cerr << "Unable to open the file for writing." << endl;
                return;
            }

            Hnode* temp = head;
            while (temp != nullptr) {
                 if (temp->next == nullptr) { // Check for the last node
                    outputFile << temp->event << " " << temp->amount << " " << temp->date << " " << temp->storedbalance << endl;
                    break; // Exit the loop after writing the last node
                }
                outputFile<<temp->event<<" "<<temp->amount<<" "<<temp->date<<" "<<temp->storedbalance<< endl;
                temp = temp->next;
            }
            outputFile.close();
        }


void bankaccount::storeBalance(const string& filename){ //use a separate file to store the case balance 
            ofstream outputFile(filename);
            if (!outputFile.is_open()) {
                cerr << "Unable to open the file for writing." << endl;
                return;
            }

            outputFile<<getbalance(); //store the balance to file
            outputFile.close();
            

        }

void bankaccount::initializeBalance(){
            if (head == nullptr) {
                cout << "List is empty." << endl;
                return;
            }

            Hnode* temp = head;

            while(temp->next != nullptr){
                temp = temp->next;
            }

            setbalance(temp->storedbalance);
        }

void bankaccount::initializeBalanceFromTxt(const string &filename){
            ifstream inputFile(filename);
            if (!inputFile.is_open()) {
                cerr<<"Unable to open the file."<<endl;
                return;
            }

            string line;
            while (getline(inputFile, line)) {
            istringstream iss(line);
            double currentBalance;

            if (iss>>currentBalance) {
                setbalance(currentBalance);
            }
        }
        inputFile.close();
        }
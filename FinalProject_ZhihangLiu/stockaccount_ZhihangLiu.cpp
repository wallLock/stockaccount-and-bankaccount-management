#include "stockaccount.h"
void stockaccount::loadGraphinfo(const string filename){ //load informtaion for graphing
            ifstream inputFile(filename);
            if (!inputFile.is_open()) {
                cerr<<"Unable to open the file."<<endl;
                return;
            }

            string line;
            while (getline(inputFile, line)) {
                istringstream iss(line);
                double totalaccountvalue;
                string timestamp;


                if (iss>>totalaccountvalue>>timestamp) {
                    totalPortfolio.push_back(totalaccountvalue);
                    timestamps.push_back(timestamp);
                }
            }
            inputFile.close();
        }

void stockaccount::storeGraphinfo(const string filename){ //store info to txt files.
            ofstream outputFile(filename);
            if (!outputFile.is_open()) {
                cerr << "Unable to open the file for writing." << endl;
                return;
            }

            for(size_t i=0; i<totalPortfolio.size(); ++i){
                outputFile << totalPortfolio[i] << " " << timestamps[i] << endl;
            }

            outputFile.close();
        }

void stockaccount::displayGraphinfo(const string filename){
            cout<<"total value change data along with time stamp is displayed\n";
            cout<<"data also store in the graph.txt file, to view the graph run the R script in the folder to view the plot\n";

            storeGraphinfo(filename);
            for(size_t i=0; i<totalPortfolio.size(); ++i){
                cout << totalPortfolio[i] << " " << timestamps[i] << endl;
            }

            cout<<"end\n";
        }

stockaccount::stockaccount(const string balancefilname1, const string historyfilename, const string protofliofilename, const string graphfilename){
            Phead = nullptr;
            Hhead = nullptr;
            strategy = nullptr;
            startbalance(balancefilname1);
            loadhistory(historyfilename);
            loadportofolio(protofliofilename);
            loadGraphinfo(graphfilename);
        }

stockaccount::~stockaccount(){
            deletePNodes();

        
            deleteHTNodes();

            delete strategy;
        }

void stockaccount::deletePNodes() {
            Pnode* currentP = Phead;
            Pnode* next = nullptr;
            while (currentP != nullptr) {
                next = currentP->next;
                delete currentP;
                currentP = next;
            }
            Phead = nullptr;
        }

void stockaccount::deleteHTNodes() {
            HTnode* currentHT = Hhead;
            HTnode* next = nullptr;
            while (currentHT != nullptr) {
                next = currentHT->next;
                delete currentHT;
                currentHT = next;
                
            }
            Hhead = nullptr; 
        }

void stockaccount::setStrategy(SortingStrategy* newstrategy){
            delete strategy;
            strategy = newstrategy;
        }

void stockaccount::applysort(){
            if(strategy != nullptr){
                strategy->sort(Phead);
            }else{
                cout<<"no strategy is chosen\n";
            }
        }

void stockaccount::displayHistory(){
            
            HTnode* temp = Hhead;
            

            while (temp != nullptr){
                cout<<"event: "<<temp->event<<", company: "<<temp->symbol<<", number of shares: "<<temp->shares<<", price per share: "<<temp->price
                <<", totalvalue: "<<temp->totalValue<<", Time: "<<temp->Time<<endl;
                temp = temp->next;
            }

        }

void stockaccount::dispalyProtoflio(){
            cout<<"current balance is $"<<getbalance()<<endl;
            if (Phead == nullptr) {
            cout << "Portfolio is empty." << endl;
            return;
            }

            Pnode* temp = Phead;
            double curBalance = getbalance();
            while(temp != nullptr){
                cout<<"Company symbol: "<<temp->symbol<<", Number of shares: "<<temp->shares<<", price per share: "<<temp->price<<", total value: "
                <<temp->totalValue<<endl;
                curBalance += temp->totalValue;
                temp = temp->next;
            }

            cout<<"Total portfolio value: $"<<curBalance<<endl;
        }

double stockaccount::calculateCurrentPortfolioValue(){ //calculate current time portfolio value balance + share worth
            if(Phead == nullptr){
                cout<<"Portfolio is empty\n";
                return getbalance();
            }

            Pnode* temp = Phead;
            double curBalance = getbalance();

            while(temp != nullptr){
                curBalance += temp->totalValue;
                temp = temp->next;
            }

            return curBalance;
        }

void stockaccount::appendPnode(string symbol, double price, int shares){
            Pnode *newNode = new Pnode;
            newNode->symbol = symbol;
            newNode->shares = shares;
            newNode->price = price;
            newNode->totalValue = price*shares; // number of shares x price per share
            newNode->next = nullptr;

            if (Phead == nullptr) {
                newNode->prev = nullptr;
                Phead = newNode;
                return;
            }

            Pnode* temp = Phead;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->prev = temp;


        }

void stockaccount::appenHTnode(const string event, const string symbol, int shares, double price, double totalValue, string time){
            HTnode *newNode = new HTnode;
            newNode->event = event;
            newNode->symbol = symbol;
            newNode->shares = shares;
            newNode->price = price;
            newNode->totalValue = totalValue;
            newNode->Time = time;
            newNode->next = nullptr;

            if (Hhead == nullptr) {
                newNode->prev = nullptr;
                Hhead = newNode;
                return;
            }

            HTnode* temp = Hhead;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->prev = temp;
        }

Pnode* stockaccount::searchNodeBySymbol(const string symbolToFind) {
            Pnode* current = Phead;

            while (current != nullptr) {
                if (current->symbol == symbolToFind) {
                    return current; // Return the node if symbol matches
                }
                current = current->next;
            }

            return nullptr; // Return nullptr if the symbol is not found in the list
        }

void stockaccount::displayStock(const string filename1, const string filename2){ //Used for display the stock information

            srand(static_cast<unsigned int>(time(nullptr)));
            int randomNum = rand() % 11; //generate a random number between 0 to 10

            cout<<"Please type in the company symbol you want to check\n";
            string name;
            cin>>name;

            if(randomNum >= 5){ //if random number greater than 5 then read the price from result1_txt
                ifstream inputFile(filename1);
                if (!inputFile.is_open()) {
                    cerr<<"Unable to open the file."<<endl;
                    return;
                }

                string line;
            while (getline(inputFile, line)) {
                istringstream iss(line);
                string symbol;
                double price;
                string date;

                if (iss>>symbol>>price>>date) {
                    if(symbol == name){
                        cout<<"Company name: "<<name<<" price per shares: $"<<price<<endl;
                        return;
                    }
                }
            }
                cout<<"Company symbol not found\n";
                inputFile.close();
            }else{//if random number greater than 5 then read the price from result1_txt

                ifstream inputFile(filename2);
                if (!inputFile.is_open()) {
                    cerr<<"Unable to open the file."<<endl;
                    return;
                }

                string line;
                while (getline(inputFile, line)) {
                istringstream iss(line);
                string symbol;
                double price;
                string date;
                
                if (iss>>symbol>>price>>date) {
                    if(symbol == name){
                        cout<<"Company name: "<<name<<" price per shares: $"<<price<<endl;
                        return;
                    }
                }
                }
                cout<<"Company symbol not found\n";
                inputFile.close();
            }

        }

void stockaccount:: buyShare(const string filename1, const string filename2, bankaccount &bank){
            srand(static_cast<unsigned int>(time(nullptr)));
            int randomNum = rand() % 11; //generate a random number between 0 to 10

            cout<<"Please type in the company symbol you want to buy\n";
            string name;
            cin>>name;
            cout<<"Please indicate the number of shares you want to buy\n";
            int numberofshares;
            cin>>numberofshares;

            if(randomNum >= 5){ //if random number greater than 5 then read the price from result1_txt
                ifstream inputFile(filename1);
                if (!inputFile.is_open()) {
                    cerr<<"Unable to open the file."<<endl;
                    return;
                }

                string line;
            while (getline(inputFile, line)) {
                istringstream iss(line);
                string symbol;
                double price;
                string date;
                

                if (iss>>symbol>>price>>date) {
                    if(symbol == name){
                        cout<<"Company name: "<<name<<" price per shares: $"<<price<<endl;
                        if(price*numberofshares>getbalance()){
                            cout<<"unable to process transaction purchase amount exceed current balance\n";
                            return;
                        }else{
                            Pnode* foundNode = searchNodeBySymbol(symbol);
                            if(foundNode != nullptr){ //the shares to buy is already exist
                                //update node informations
                                foundNode->shares += numberofshares;
                                foundNode->price = price;
                                foundNode->totalValue = foundNode->shares * foundNode->price;
                                //acquire current time
                                time_t currentTime = time(nullptr);
                                ostringstream oss;
                                oss<<put_time(localtime(&currentTime), "%Y-%m-%d-%H:%M:%S");
                                string timeString = oss.str(); //store time information into strings
                                appenHTnode("BuyShare", symbol, numberofshares, price, price*numberofshares, timeString);
                                // set new balance and add to bank account history
                                double newbalance = getbalance()-price*numberofshares;
                                bank.append("withdraw ", price*numberofshares, timeString, newbalance);
                                setbalance(newbalance);

                                //add to graph info
                                totalPortfolio.push_back(calculateCurrentPortfolioValue());
                                timestamps.push_back(timeString);
                                return;

                            }else{ //the shares to buy is not found in portfolio data
                                appendPnode(symbol, price, numberofshares); //add purchased item to Pnodes linked list
                            
                                time_t currentTime = time(nullptr);
                                ostringstream oss;
                                oss<<put_time(localtime(&currentTime), "%Y-%m-%d-%H:%M:%S");
                                string timeString = oss.str(); //store time information into strings

                                appenHTnode("BuyShare", symbol, numberofshares, price, price*numberofshares, timeString);

                                double newbalance = getbalance()-price*numberofshares;
                                bank.append("withdraw ", price*numberofshares, timeString, newbalance);
                                setbalance(newbalance);


                                //add to graph info
                                totalPortfolio.push_back(calculateCurrentPortfolioValue());
                                timestamps.push_back(timeString);
                                return;
                            }
                            
                        }
                    }
                }
            }

                cout<<"Company symbol not found\n";
                inputFile.close();


            }else{//if random number greater than 5 then read the price from result1_txt


                ifstream inputFile(filename2);
                if (!inputFile.is_open()) {
                    cerr<<"Unable to open the file."<<endl;
                    return;
                }

                string line;
                while (getline(inputFile, line)) {
                istringstream iss(line);
                string symbol;
                double price;
                string date;
                

                if (iss>>symbol>>price>>date) {
                    if(symbol == name){
                        cout<<"Company name: "<<name<<" price per shares: $"<<price<<endl;
                        if(price*numberofshares>getbalance()){
                            cout<<"unable to process transaction purchase amount exceed current balance\n";
                            return;
                        }else{
                            Pnode* foundNode = searchNodeBySymbol(symbol);
                            if(foundNode != nullptr){ //the shares to buy is already exist
                                //update node informations
                                foundNode->shares += numberofshares;
                                foundNode->price = price;
                                foundNode->totalValue = foundNode->shares * foundNode->price;
                                //acquire current time
                                time_t currentTime = time(nullptr);
                                ostringstream oss;
                                oss<<put_time(localtime(&currentTime), "%Y-%m-%d-%H:%M:%S");
                                string timeString = oss.str(); //store time information into strings
                                appenHTnode("BuyShare", symbol, numberofshares, price, price*numberofshares, timeString);
                                // set new balance and add to bank account history
                                double newbalance = getbalance()-price*numberofshares;
                                bank.append("withdraw ", price*numberofshares, timeString, newbalance);
                                setbalance(newbalance);

                                //add to graph info
                                totalPortfolio.push_back(calculateCurrentPortfolioValue());
                                timestamps.push_back(timeString);
                                return;

                            }else{ //the shares to buy is not found in portfolio data
                                appendPnode(symbol, price, numberofshares); //add purchased item to Pnodes linked list
                            
                                time_t currentTime = time(nullptr);
                                ostringstream oss;
                                oss<<put_time(localtime(&currentTime), "%Y-%m-%d-%H:%M:%S");
                                string timeString = oss.str(); //store time information into strings

                                appenHTnode("BuyShare", symbol, numberofshares, price, price*numberofshares, timeString);

                                double newbalance = getbalance()-price*numberofshares;
                                bank.append("withdraw ", price*numberofshares, timeString, newbalance);
                                setbalance(newbalance);



                                //add to graph info
                                totalPortfolio.push_back(calculateCurrentPortfolioValue());
                                timestamps.push_back(timeString);
                                return;
                            }
                        }
                    }
                }
                }

                cout<<"Company symbol not found\n";
                inputFile.close();
            }
        }

void stockaccount::sellshare(const string filename1, const string filename2, bankaccount &bank){
            cout<<"please indicate the name of the stock you want to sell\n";
            string name;
            cin>>name;
            cout<<"please indicate the number of shares you want to sell\n";
            int numberofshares;
            cin>>numberofshares;

            srand(static_cast<unsigned int>(time(nullptr)));
            int randomNum = rand() % 11; //generate a random number between 0 to 10

            Pnode* temp = Phead;
            while (temp != nullptr){
                if(temp->symbol == name){ //find the user owned stock and then proceed
                    if(randomNum >= 5){ //if random number greater than 5 then read the price from result1_txt
                        ifstream inputFile(filename1);
                        if (!inputFile.is_open()) {
                            cerr<<"Unable to open the file."<<endl;
                            return;
                        }

                        string line;
                        while (getline(inputFile, line)) {
                            istringstream iss(line);
                            string symbol;
                            double price;
                            string date;
                

                            if (iss>>symbol>>price>>date) {
                                if(symbol == name){ //find the corresponding stock in new price
                                    cout<<"Company name: "<<name<<" price per shares: $"<<price<<endl;
                                    if(price < temp->price){ //compare new price, new price is lower than old price, cant proceed
                                        cout<<"transaction failed, selling price is lower than previous price\n";
                                        return;
                                    }else{ //new price is higher than old price
                                        if(numberofshares > temp->shares){ //share number exceeds, cant proceed
                                            cout<<"transaction failed, selling shares number exceed owned share number\n";
                                            return;
                                        }else{
                                            if(numberofshares < temp->shares){
                                                temp->shares -= numberofshares; //deduct sold shares
                                                temp->price = price;
                                                temp->totalValue = temp->price*temp->shares;

                                                double earning = numberofshares * price;

                                                setbalance(getbalance()+earning); //add earning to balance
                                                time_t currentTime = time(nullptr);
                                                ostringstream oss;
                                                oss<<put_time(localtime(&currentTime), "%Y-%m-%d-%H:%M:%S");
                                                string timeString = oss.str(); //store time information into strings

                                                appenHTnode("Sellshare", symbol, numberofshares, price, earning, timeString);
                                                bank.append("deposit", earning, timeString, getbalance()+earning);

                                                //add to graph info
                                                totalPortfolio.push_back(calculateCurrentPortfolioValue());
                                                timestamps.push_back(timeString);
                                                return;
                                                
                                            }else{ //number of shares are equal to the holding shares delete that node

                                                double earning = numberofshares * price;
                                                setbalance(getbalance()+earning); //add earning to balance
                                                time_t currentTime = time(nullptr);
                                                ostringstream oss;
                                                oss<<put_time(localtime(&currentTime), "%Y-%m-%d-%H:%M:%S");
                                                string timeString = oss.str(); //store time information into strings

                                                appenHTnode("Sellshare", symbol, numberofshares, price, earning, timeString); //store action into history
                                                bank.append("deposit", earning, timeString, getbalance()+earning);


                                                
                                                if(temp == Phead){ //delete the node if all shares of it are sold
                                                    Phead = temp->next;
                                                    if(Phead != nullptr){
                                                        Phead->prev = nullptr;
                                                    }

                                                }else{
                                                    if(temp->prev != nullptr){
                                                        temp->prev->next = temp->next;
                                                    }
                                                    if(temp->next != nullptr){
                                                        temp->next->prev = temp->prev;
                                                    }
                                                }

                                                delete temp;
                                                //function should stop here in case of overwhelming while loop

                                                //add to graph info
                                                totalPortfolio.push_back(calculateCurrentPortfolioValue());
                                                timestamps.push_back(timeString);
                                                return;

                                            }
                                        }
                                    }
                                }
                            }
                        }

                        cout<<"Company symbol not found\n";
                        inputFile.close();


                }else{//if random number greater than 5 then read the price from result1_txt


                    ifstream inputFile(filename2);
                    if (!inputFile.is_open()) {
                        cerr<<"Unable to open the file."<<endl;
                        return;
                    }

                    string line;
                    while (getline(inputFile, line)) {
                    istringstream iss(line);
                    string symbol;
                    double price;
                    string date;
                

                        if (iss>>symbol>>price>>date) {
                            
                            if(symbol == name){ //find the corresponding stock in new price
                                    cout<<"Company name: "<<name<<" price per shares: $"<<price<<endl;
                                    if(price < temp->price){ //compare new price, new price is lower than old price, cant proceed
                                        cout<<"transaction failed, selling price is lower than previous price\n";
                                        return;
                                    }else{ //new price is higher than old price
                                        if(numberofshares > temp->shares){ //share number exceeds, cant proceed
                                            cout<<"transaction failed, selling shares number exceed owned share number\n";
                                            return;
                                        }else{
                                            if(numberofshares < temp->shares){
                                                temp->shares -= numberofshares; //deduct sold shares
                                                temp->price = price;
                                                temp->totalValue = temp->price*temp->shares;

                                                double earning = numberofshares * price;

                                                setbalance(getbalance()+earning); //add earning to balance
                                                time_t currentTime = time(nullptr);
                                                ostringstream oss;
                                                oss<<put_time(localtime(&currentTime), "%Y-%m-%d-%H:%M:%S");
                                                string timeString = oss.str(); //store time information into strings

                                                appenHTnode("Sellshare", symbol, numberofshares, price, earning, timeString);
                                                bank.append("deposit", earning, timeString, getbalance()+earning);

                                                //add to graph info
                                                totalPortfolio.push_back(calculateCurrentPortfolioValue());
                                                timestamps.push_back(timeString);
                                                return;
                                                
                                            }else{ //number of shares are equal to the holding shares delete that node

                                                double earning = numberofshares * price;
                                                setbalance(getbalance()+earning); //add earning to balance
                                                time_t currentTime = time(nullptr);
                                                ostringstream oss;
                                                oss<<put_time(localtime(&currentTime), "%Y-%m-%d-%H:%M:%S");
                                                string timeString = oss.str(); //store time information into strings

                                                appenHTnode("Sellshare", symbol, numberofshares, price, earning, timeString); //store action into history
                                                bank.append("deposit", earning, timeString, getbalance()+earning);

                                                if(temp == Phead){ //delete the node if all shares of it are sold
                                                    Phead = temp->next;
                                                    if(Phead != nullptr){
                                                        Phead->prev = nullptr;
                                                    }

                                                }else{
                                                    if(temp->prev != nullptr){
                                                        temp->prev->next = temp->next;
                                                    }
                                                    if(temp->next != nullptr){
                                                        temp->next->prev = temp->prev;
                                                    }
                                                }

                                                delete temp;
                                                //function should stop here in case of overwhelming while loop

                                                //add to graph info
                                                totalPortfolio.push_back(calculateCurrentPortfolioValue());
                                                timestamps.push_back(timeString);
                                                return;

                                            }
                                        }
                                    }
                                }
                            
                        }
                    }

                    cout<<"Company symbol not found\n";
                    inputFile.close();
                }
                }

                temp = temp->next;
            }

            cout<<"Stock not found\n";

        }

void stockaccount::startbalance(const string filename){
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

void stockaccount::storeStockbalance(const string filename){
            ofstream outputFile(filename);
            if (!outputFile.is_open()) {
                cerr << "Unable to open the file for writing." << endl;
                return;
            }

            outputFile<<getbalance(); //store the balance to file
            outputFile.close();
        }

void stockaccount::loadhistory(const string filename){
            ifstream inputFile(filename);
        if (!inputFile.is_open()) {
            cerr<<"Unable to open the file."<<endl;
            return;
        }

        string line;
        while (getline(inputFile, line)) {
            istringstream iss(line);
            string event;
            string symbol;
            int shares;
            double price;
            double totalValue;
            string time;

            if (iss>>event>>symbol>>shares>>price>>totalValue>>time) {
                appenHTnode(event, symbol, shares, price, totalValue, time);
            }
        }
        inputFile.close();
        }

void stockaccount::storehistory(const string filename){
            ofstream outputFile(filename);
            if (!outputFile.is_open()) {
                cerr << "Unable to open the file for writing." << endl;
                return;
            }

            HTnode *temp = Hhead;

            while (temp != nullptr) {
                 if (temp->next == nullptr) { // Check for the last node
                    outputFile << temp->event << " " << temp->symbol << " " << temp->shares << " " << temp->price<< " " <<temp->totalValue << " " <<
                    temp->Time<< endl;
                    break; // Exit the loop after writing the last node
                }
                outputFile << temp->event << " " << temp->symbol << " " << temp->shares << " " << temp->price<< " " <<temp->totalValue << " " <<
                temp->Time<< endl;
                temp = temp->next;
            }
            outputFile.close();
        }

void stockaccount::loadportofolio(const string filename){
            ifstream inputFile(filename);
        if (!inputFile.is_open()) {
            cerr<<"Unable to open the file."<<endl;
            return;
        }

        string line;
        while (getline(inputFile, line)) {
            istringstream iss(line);
            
            string symbol;
            int shares;
            double price;
            double totalValue;
            

            if (iss>>symbol>>shares>>price>>totalValue) {
                appendPnode(symbol, price, shares);
            }
        }
        inputFile.close();
        }

void stockaccount::storePortfolio(const string filename){
            ofstream outputFile(filename);
            if (!outputFile.is_open()) {
                cerr << "Unable to open the file for writing." << endl;
                return;
            }
            Pnode *temp = Phead;
            while (temp != nullptr) {
                 if (temp->next == nullptr) { // Check for the last node
                    outputFile << temp->symbol << " " << temp->shares << " " << temp->price<< " " <<temp->totalValue << endl;
                    break; // Exit the loop after writing the last node
                }
                outputFile << temp->symbol << " " << temp->shares << " " << temp->price<< " " <<temp->totalValue << endl;
                temp = temp->next;
            }
            outputFile.close();

        }
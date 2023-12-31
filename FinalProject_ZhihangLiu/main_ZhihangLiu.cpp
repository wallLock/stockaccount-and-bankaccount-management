#include "account.h"
#include "bankaccount.h"
#include "stockaccount.h"

void thirdMenu(bankaccount &b1, stockaccount &s1);
void secondMenu(bankaccount &b1, stockaccount &s1);

void firstmenu(bankaccount &b1, stockaccount &s1){
    cout<<"Welcome to the Account Management System."
            "\nPlease select an account to access:\n";
            cout<<"1. stock portfolio account\n";
            cout<<"2. bank account\n";
            cout<<"3. exit\n";
    int choice;
    cin>>choice;

    switch (choice)
    {
    case 1: {
        secondMenu(b1, s1);
    }
    case 2: {
        thirdMenu(b1, s1);
    }
    
    case 3:{
        b1.storeBalance("accountbalance.txt");
        b1.storetoHistory("bankaccounthistory.txt");
        s1.storeStockbalance("accountbalance.txt");
        s1.storehistory("stock_transaction_history.txt");
        s1.storePortfolio("portfolio.txt");
        s1.storeGraphinfo("graph.txt");
        exit(0);
    }
    }
}


void thirdMenu(bankaccount &b1, stockaccount &s1){
    cout<<"\nPlease select an option: \n";
    cout<<"1. View account balance\n";
    cout<<"2. Deposit money\n";
    cout<<"3. Withdraw money\n";
    cout<<"4. print out history\n";
    cout<<"5. Return to previous menu\n";

    int choice;
    cin>>choice;
    switch(choice){
        case 1: {
            b1.viewCurrentBalance();
            thirdMenu(b1, s1);
            break;
        }
        case 2: {
            double amount;
            cout<<"Enter the amount you want to deposit\n";
            cin>>amount;
            b1.deposit(amount);
            thirdMenu(b1, s1);
        }

        case 3: {
            double withdrawAmount;
            cout<<"Enter the amount you want to withdraw\n";
            cin>>withdrawAmount;
            b1.withdraw(withdrawAmount);
            thirdMenu(b1,s1);
        }

        case 4:{
            b1.displayHistory();
            thirdMenu(b1, s1);
        }

        case 5:{
            b1.storeBalance("accountbalance.txt");
            b1.storetoHistory("bankaccounthistory.txt");
            firstmenu(b1, s1);
        }

        default: {
            cout<<"Invalid choice, Please enter again\n";
            thirdMenu(b1, s1);
        }
    }
            
}

void secondMenu(bankaccount &b1, stockaccount &s1){

    cout<<"\nHow do you want to sort the stored portfolio\n";
    cout<<"1. bubblesort\n";
    cout<<"2. selectionsort\n";
    int sortchoice;
    cin>>sortchoice;
    if(sortchoice == 1){
        s1.setStrategy(new BubbleSort());
    }else if( sortchoice == 2){
        s1.setStrategy(new SelectionSort());
    }else{
        cout<<"Invalid choice\n";
        secondMenu(b1,s1);
    }

    cout<<"\nPlease select an option: \n";
    cout<<"1. Display the price for a stock symbol\n";
    cout<<"2. Display the current portfolio\n";
    cout<<"3. Buy shares\n";
    cout<<"4. Sell shares\n";
    cout<<"5. View a graph for portfolio value\n";
    cout<<"6. View transaction history\n";
    cout<<"7. Return to previous menu\n";

    int choice;
    cin>>choice;

    switch(choice){
        case 1: {
            s1.displayStock("Result_1.txt", "Result_2.txt");
            secondMenu(b1, s1);
            break;
        }

        case 2: {
            s1.applysort();
            s1.dispalyProtoflio();
            secondMenu(b1, s1);
            break;
        }

        case 3: {
            s1.buyShare("Result_1.txt", "Result_2.txt", b1);
            s1.applysort();
            secondMenu(b1, s1);
        }

        case 4: {
            s1.sellshare("Result_1.txt", "Result_2.txt", b1);
            s1.applysort();
            secondMenu(b1, s1);
        }

        case 5: {
            s1.displayGraphinfo("graph.txt");
            secondMenu(b1, s1);
            break;
        }

        case 6: {
            s1.displayHistory();
            secondMenu(b1, s1);
            break;
        }

        case 7:{
            s1.storeStockbalance("accountbalance.txt");
            s1.storehistory("stock_transaction_history.txt");
            s1.storePortfolio("portfolio.txt");
            s1.storeGraphinfo("graph.txt");
            firstmenu(b1, s1);
        }

        default: {
            cout<<"invalid choice please enter agian\n";
            secondMenu(b1, s1);
        }
    }
}

int main(){


    

    bankaccount sample1("bankaccounthistory.txt", "accountbalance.txt");
    stockaccount sample2("accountbalance.txt", "stock_transaction_history.txt", "portfolio.txt", "graph.txt");

    firstmenu(sample1, sample2);
    //sample1.deposit(2000.00);

    //sample2.buyShare("Result_1.txt", "Result_2.txt", sample1);
    //sample2.buyShare("Result_1.txt", "Result_2.txt", sample1);

    //sample2.sellshare("Result_1.txt", "Result_2.txt", sample1);

    //sample2.dispalyProtoflio();
    //sample2.displayHistory();

    //sample1.displayHistory();
    //sample2.displayGraphinfo("graph.txt");

    //cout<<"\n";
    //sample2.setStrategy(new SelectionSort());
    //sample2.applysort();
    //sample2.dispalyProtoflio();
    //cout<<"\n";

    //sample2.storehistory("stock_transaction_history.txt");
    //sample2.storePortfolio("portfolio.txt");
    //sample2.storeStockbalance("accountbalance.txt");
    //sample2.storeGraphinfo("graph.txt");

    //sample1.storetoHistory("bankaccounthistory.txt"); 

    //sample2.displayStock("Result_1.txt", "Result_2.txt");

    //sample.viewCurrentBalance();
    //sample.deposit(1.01);

    //sample.printoutHistory();

    //sample.storeBalance("accountbalance.txt");
    //sample.storetoHistory("bankaccounthistory.txt");



}
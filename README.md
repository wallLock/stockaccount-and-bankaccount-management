This is the academic project of my graduate course. A terminal operation program for manage bank accounts and stock accounts. 

The final project deployed two design patterns, they are behavioral pattern template and behavioral pattern strategy. There are 3 header files in the folder which are account.h, stockaccount.h and bankaccount.h. Account is the base class for stockaccount and bankaccount. In the base class, one pure virtual function is developed as displayHistory(), this action is required for both classes, therefore it can act as a template for both classes to declare the content of the function separately. In the meanwhile, there are also separate strategies classes for stockaccount. There are 2 strategies to sort the doubled linked list that stores the content of the portfolio. One is bubble sort and one is selection sort, user need to choose how they want their contents to be sorted by entering the options when entering the option page of stockaccount.
Bankaccount class and stockaccount class store many member functions including constructor, destructor, helper function, and require functionality functions. There are 10 member functions in the bankaccount class excluding the constructor and destructor. There are 2 variables balance(inherited from base), head(Hnode*, a double linked list head pointer point to the double linked list store history).

●	viewCurrentBalance() to check current account balance
●	deposit() take double number input to deposit certain amount in account
●	withdraw() take double number input to withdraw certain amount in account
●	append() add history node to store the history information when deposit or withdraw
●	initialiazeHistory() load exist history txt file, so the program “remember what happened”
●	dispalyHistory() pure virtual function inherit from base to display the history activity
●	storetohistory() store the all history to txt files
●	storeBalance() store balance number to txt files so all accounts can access it.
●	initializeBalance() load balance from the last history node where record all total balance, later find this method can’t read the accurate balance when there are also stockaccount. So this function is not used in the program
●	initializeBalanceFromTxt() load balance from stored balance txt.

Stockaccount class have 21 member functions, 6 variables: balance(inherit from base class), Phead(Pnode* store portfolio info double linked list), Hhead(HTnode* store history info double linked list), SortingStrategy* strategy (store selected sort method class), totalportfolio(vector store the total portfolio values whenever buy or sell shares action happen), timestamp(vector store the time stamps when buy or sell shares).

●	loadGraphinfo() load graphing info to vectors
●	storeGraphingo() store vector info to graph.txt
●	displayGraphinfo() display content for graph and update graph.txt. To view the graph run example2.R in vscode that can generate a pdf file store the plot called Rplots.pdf. Or run example2.R in RStudio, graph can display in plot panel.
●	deletePNodes() deallocate Pnode double linked list
●	deleteHTNodes() deallocate HTnode double linked list
●	setStrategy() update strategy variable
●	applysort() sort the Portfolio linked list
●	displayHistory() pure virtual function from base to display transaction history
●	displayProtoflio() display portfolio owned
●	calculateCurrentPortfolioValue() calculate current time portfolio value when get called
●	appendPnode() add Pnode to portfolio linked list
●	appenHTnode() add HTnode to history linked list
●	searchNodeBySymbol() return the node with match symbol name
●	displayStock() display the stock price you want search
●	buyShare() purchase share by company symbol and number of shares
●	sellShare() sell owned shares
●	startbalance() load balance from txt file
●	storeStockbalance() store balance to txt file
●	loadhistory() load history from txt file
●	storehistory() store history to txt file
●	loadportfolio() load portfolio info from txt file
●	storePortfolio() store portfolio info to txt file

There are 6 txt files in this folder, accountbalance.txt(store the the account balance), bankacconthistory.txt(store the bank account activity), graph.txt(store the total portfolio value and time stamp for graphing), portfolio.txt(store owned stocks), Result1.txt, Result2.txt(from assignment downloaded), stock_transaction_history.txt(store all buy and sell share activity)

Txt files already store the information of previous program history as a proof of successful running of program. If you want to start all over, you can clear bankacconthistory.txt(store the bank account activity), graph.txt(store the total portfolio value and time stamp for graphing), portfolio.txt(store owned stocks), stock_transaction_history.txt(store all buy and sell share activity), and change the number in accountbalance.txt into 10000.00.

There are image files showing the successful run of the final project. Please use ./program in terminal to run the code

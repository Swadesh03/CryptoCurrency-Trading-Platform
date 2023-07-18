
#include "MerkelMain.h"
#include <iostream>
#include <vector>
#include <string>
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include "wallet.h"

using namespace std;

MerkelMain::MerkelMain()
{
    
}

void MerkelMain::init()
{
    //loadOrderBook();
    currentTime = OrderBook.getEarliestTime();
    //nextTime = OrderBook.getNextTime(currentTime);
    int input; 
    wallet.insertCurrency("BTC", 10);
    while(true){
        printMenu();
        input = getUserOption();
        processUserOption(input);
    }
}

//void MerkelMain::loadOrderBook()
//{
//        orders =  CSVReader::readCSV("20200317.csv");
//
//}

void MerkelMain::printMenu() {
    // 1 Print help
    cout << "1: Print help" << endl;
    // 2 print exchange stats
    cout << "2: Print exchange stats" << endl;
    // 3 make an offer
    cout << "3: Place an ask" << endl;
    // 4 make a bid
    cout << "4: Place a bid" << endl;
    // 5 print wallet
    cout << "5: Print wallet" << endl;
    // 6 continue
    cout << "6: Continue" << endl;
    
    cout << "Current time is: " << currentTime << endl;
    //cout << "Next time is: " << nextTime << endl;
    
}

int MerkelMain::getUserOption() {
    cout << "------------------------------------------" << endl;
    cout << "Select an option: Type 1-6 for trading" << endl;
    int userOption = 0;
    string line;
    getline(cin, line);
    try {
        userOption = stoi(line);
    }catch(const exception& e)
    {
        //
    }
    
    
    //cin >> userOption;
    cout << "You chose: " << userOption << endl; 
    return userOption;
}

void MerkelMain::printHelp()
{
    cout << "Help- choose options from the menu and follow on the on screen instructions." << endl;
    cout << "------------------------------------------" << endl;
}

void MerkelMain::printMarketStats()
{
    for ( const string& p : OrderBook.getKnownProducts())
    {
        
        cout << "Product: " << p << endl;

        vector<OrderBookEntry> entriesAsk = OrderBook.getOrders(OrderBookType::ask,
                                                             p, currentTime);
        cout << "Asks seen: " << entriesAsk.size() << endl; 
        cout << "Max ask: " << OrderBook::getHighPrice(entriesAsk) << endl;
        cout << "Min ask: " << OrderBook::getLowPrice(entriesAsk) << endl; 

        vector<OrderBookEntry> entriesBid = OrderBook.getOrders(OrderBookType::bid,
                                                             p, currentTime);
        cout << "Bids seen: " << entriesBid.size() << endl; 
        cout << "Max Bid: " << OrderBook::getHighPrice(entriesBid) << endl;
        cout << "Min Bid: " << OrderBook::getLowPrice(entriesBid) << endl;
        
        
        cout << "====================================================" << endl;
    }
}
//    cout << "2: Orderbook contains: " << orders.size() << " entries." << endl;
//    unsigned int bids = 0;
//    unsigned int asks = 0;
//    for (OrderBookEntry& e : orders)
//    {
//        if (e.orderType == OrderBookType::ask)
//        {
//            asks++;
//        }
//        if (e.orderType == OrderBookType::bid)
//        {
//            bids++;
//        }
//    }
//    cout << "OrderBook asks: " << asks << endl;
//    cout << "OrderBook bids: " << bids << endl;
    //cout << "------------------------------------------" << endl;
//}

//void MerkelMain::printMarketStats()
//{
//    for (std::string const& p : OrderBook.getKnownProducts())
//    {
//        std::cout << "Product: " << p << std::endl;
//        std::vector<OrderBookEntry> entries = OrderBook.getOrders(OrderBookType::ask, 
//                                                                p, currentTime);
//        std::cout << "Asks seen: " << entries.size() << std::endl;
//        std::cout << "Max ask: " << OrderBook::getHighPrice(entries) << std::endl;
//        std::cout << "Min ask: " << OrderBook::getLowPrice(entries) << std::endl;
//
//
//
//    }
//}
void MerkelMain::enterAsk()
{
    cout << "3: Make an ask: Enter the amount: (product,price,amount)" << endl;
    cout << "For ex- ETH/BTC,200,0.05" << endl;
    string input;
//    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); // for cleaning the input line before calling
//    // the getline, at it stores some garbage value from the last line. 
    getline(cin,input);
    //cin >> input;
    
    vector<string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() !=3)
    {
        cout << "MerkelMain::enterAsk Bad Input! :  " << input << endl;
        
    }
    else 
    {
        try {
                OrderBookEntry obe = CSVReader::stringsToOBE(
                                                    tokens[1],
                                                    tokens[2],
                                                    currentTime,
                                                    tokens[0],
                                                    OrderBookType::ask);
                obe.username = "simuser";
                if (wallet.canFullfillOrder(obe)){
                    cout << "Wallet looks good." << endl; 
                    OrderBook.insertOrder(obe);
                }
                else {
                    cout << "Wallet has insufficient funds." << endl;
                }
               
        }catch (const exception& e)
        {
            cout << "MerkelMain::enterAsk Bad input!" << endl;
        }
        cout << "You typed: " << input << endl;
    
        cout << "------------------------------------------" << endl;
    }
}
    


void MerkelMain::enterBid()
{
    cout << "3: Make a Bid: Enter the amount: (product,price,amount)" << endl;
    cout << "For ex- ETH/BTC,200,0.05" << endl;
    string input;
//    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); // for cleaning the input line before calling
//    // the getline, at it stores some garbage value from the last line. 
    getline(cin,input);
    //cin >> input;
    
    vector<string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() !=3)
    {
        cout << "MerkelMain::enterBid Bad Input! :  " << input << endl;
        
    }
    else 
    {
        try {
                OrderBookEntry obe = CSVReader::stringsToOBE(
                                                    tokens[1],
                                                    tokens[2],
                                                    currentTime,
                                                    tokens[0],
                                                    OrderBookType::bid);
                obe.username = "simuser";
                
                if (wallet.canFullfillOrder(obe)){
                    cout << "Wallet looks good." << endl; 
                    OrderBook.insertOrder(obe);
                }
                else {
                    cout << "Wallet has insufficient funds." << endl;
                }
        }catch (const exception& e)
        {
            cout << "MerkelMain::enterBid Bad input!" << endl;
        }
        cout << "You typed: " << input << endl;
    
        cout << "------------------------------------------" << endl;
    }

}

void MerkelMain::printWallet()
{
    //cout << "5: Your wallet is empty." << endl;
    cout << wallet.toString() << endl;
    cout << "------------------------------------------" << endl;
}

void MerkelMain::gotoNextInstance()
{
    cout << "6: Going to next instance" << endl;
    for (string p : OrderBook.getKnownProducts())
    {
        cout << "matching " << p << endl;
        vector<OrderBookEntry> sales = OrderBook.matchAsksToBids(p, currentTime);
        cout << "Sales: " << sales.size() << endl;
        for (OrderBookEntry& sale : sales)
        {
            cout << "Sale Price: " << sale.price << " amount: " << sale.amount << endl;
            if (sale.username == "simuser")
            {
                //update the wallet
                wallet.processSale(sale);
            }
        }
    } 
    
    
//    vector<OrderBookEntry> sales = OrderBook.matchAsksToBids("ETH/BTC",currentTime);
//    cout << "Sales: " << sales.size() << endl;
//    for (OrderBookEntry& sale : sales)
//    {
//        cout << "Sale price: " << sale.price << " amount: " << sale.amount << endl; 
//    }
    currentTime = OrderBook.getNextTime(currentTime);
    cout << "------------------------------------------" << endl;
}

void MerkelMain::processUserOption(int userOption) {
    if (userOption == 0)  // bad input
    {
        cout << "Invalid input. Choose 1-6." << endl;
    }
    if (userOption == 1)  // bad input
    {
        printHelp();
    }
    if (userOption == 2)  // bad input
    {
        printMarketStats();
    }
    if (userOption == 3)  // bad input
    {
        enterAsk();
    }
    if (userOption == 4)  // bad input
    {
        enterBid();
    }
    if (userOption == 5)  // bad input
    {
        printWallet();
    }
    if (userOption == 6)  // bad input
    {
        gotoNextInstance();
    }
}
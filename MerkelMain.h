
#pragma once

#include <vector>
#include <iostream>
#include "OrderBookEntry.h"
#include "OrderBook.h"
#include "wallet.h"

using namespace std; 

class MerkelMain
{
public:
    MerkelMain();
    /** Call this to start the sim*/
    void init();
private:
 //   void loadOrderBook();
    void printMenu();
    int getUserOption();
    void printHelp();
    void printMarketStats();
    void enterAsk();
    void enterBid();
    void printWallet();
    void gotoNextInstance();
    void processUserOption(int userOption);
    
    string currentTime;
    //string nextTime;
    OrderBook OrderBook{"20200317.csv"};
    //vector<OrderBookEntry> orders;
    
    Wallet wallet;
};
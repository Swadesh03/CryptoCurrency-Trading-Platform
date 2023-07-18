
#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <map>
#include "OrderBookEntry.h"
#include "CSVReader.h"

using namespace std; 

class Wallet
{
    public:
        Wallet();
        /**  Insert currency into the wallet */
        void insertCurrency(string type, double amount);
        
        /**  Remove currency from the wallet */
        bool removeCurrency(string type, double amount);
        
        /**  check if the wallet contains this much currency or more */
        bool containsCurrency(string type, double amount);
        
         /**  generates the string representation of the wallet */
        string toString();
        /** checks if the wallet can cope with the ask or bid */
        bool canFullfillOrder(OrderBookEntry order);
        /** update the contents of the wallet */
        /* assumes the order was made by the owner of the wallet*/
        void processSale(OrderBookEntry& sale);
        
    private:
        map<string,double> currencies;
        
};
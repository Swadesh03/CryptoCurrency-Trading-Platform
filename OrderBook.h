#pragma once

#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class OrderBook
{
public:
    /** construct reading a csv data file */
    OrderBook(string filename);
    /** return vector of all known products in the dataset */
    vector<string> getKnownProducts();
    /** return vector of orders according to the sent filters */
    vector<OrderBookEntry> getOrders(OrderBookType type, 
                                    string product,
                                    string timestamp);
    /** return the earliest timestamp in the order book */
    string getEarliestTime();
    
    /** return the next timestamp after the sent time in the order book
    if there is no next timestamp, it wraps around back to the start
     * */
    string getNextTime(string timestamp);
    
    void insertOrder(OrderBookEntry& order);
    
    vector<OrderBookEntry> matchAsksToBids(string product, string timestamp);
    
    
    static double getHighPrice(vector<OrderBookEntry>& orders);
    static double getLowPrice(vector<OrderBookEntry>& orders);
    
private:
    vector<OrderBookEntry> orders;
};

#pragma once

#include "OrderBookEntry.h"
#include <vector>
#include <iostream>

using namespace std;

class CSVReader
{
public:
    
    CSVReader();
    
    static vector<OrderBookEntry> readCSV(string csvFile);
    static vector<string> tokenise(string csvLine, char seperator);
    
    static OrderBookEntry stringsToOBE(string price, 
                                        string amount, 
                                        string timestamp,
                                        string product,
                                        OrderBookType OrderBookType);
private:
    
    static OrderBookEntry stringsToOBE(vector<string> strings);
    
};
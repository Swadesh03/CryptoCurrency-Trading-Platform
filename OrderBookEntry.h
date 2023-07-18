
#pragma once

#include <string>
#include <iostream>

using namespace std;

enum class OrderBookType{bid, ask, unknown, asksale, bidsale};

class OrderBookEntry 
{
    public:
        OrderBookEntry(double _price,
                       double _amount,
                       std::string _timestamp,
                       std::string _product,
                       OrderBookType _orderType,
                       string username = "dataset");
        static OrderBookType stringToOrderBookType(string s);
        
        static bool compareByTimestamp(OrderBookEntry& e1, OrderBookEntry& e2)
        {
            return e1.timestamp < e2.timestamp;
        }
        
        static bool compareByPriceAsc(OrderBookEntry& e1, OrderBookEntry& e2)
        {
            return e1.price < e2.price;
        }
        
        static bool compareByPriceDesc(OrderBookEntry& e1, OrderBookEntry& e2)
        {
            return e1.price > e2.price;
        }
        double price;
        double amount;
        std::string timestamp;
        std::string product;
        OrderBookType orderType;
        string username;
};
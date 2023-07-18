
#include <vector>
#include <iostream>
#include <string>
#include "wallet.h"

using namespace std; 

Wallet::Wallet()
{
    
}
        /**  Insert currency into the wallet */
void Wallet::insertCurrency(string type, double amount)
{
    double balance;
    if (amount < 0)
    {
        throw exception{};
    }
    if (currencies.count(type) == 0)
    {
        balance = 0;
    }
    else {
        balance = currencies[type];
    }
    balance += amount;
    currencies[type] = balance;
}

bool Wallet::removeCurrency(string type,double amount)
{
    if (amount < 0)
    {
        return false;
    }
    if (currencies.count(type) == 0)
    {
        return false;
    }
    else { // do we have enough
        if (containsCurrency(type,amount)) // we have enough
        {
            cout << "Removing: " << type << ": " << amount << endl;
            currencies[type] -= amount;
            return true;
        }
        else  // they have it but not enough
        {
            return false;
        }
    }

}
/**  check if the wallet contains this much currency or more */
bool Wallet::containsCurrency(string type, double amount)
{
    if (currencies.count(type) == 0)
         return false;
    else {
        return currencies[type] >= amount;
    }
    return false;
}
 /**  generates the string representation of the wallet */
string Wallet::toString()
{
    string s;
    for (pair<string,double> pair : currencies){
        string currency = pair.first;
        double amount = pair.second;
        s += currency + ":" + to_string(amount) + "\n";
    }
    return s;
}

bool Wallet::canFullfillOrder(OrderBookEntry order)
{
    vector<string> currs = CSVReader::tokenise(order.product, '/');
    // ask
    if (order.orderType == OrderBookType::ask)
    {
        double amount = order.amount;
        string currency = currs[0];
        cout << "Wallet:canFullfillOrder " << currency << ":" << amount << endl;
        return containsCurrency(currency, amount);
    }
    
    // bid logic
    
    if (order.orderType == OrderBookType::bid)
    {
        double amount = order.amount * order.price;
        string currency = currs[1] ;
        cout << "Wallet:canFullfillOrder " << currency << ":" << amount << endl;
        return containsCurrency(currency, amount);
    }
    return false;
}
  

void Wallet::processSale(OrderBookEntry& sale) 
{
    vector<string> currs = CSVReader::tokenise(sale.product, '/');
    // ask
    if (sale.orderType == OrderBookType::asksale)
    {
        double outgoingAmount = sale.amount;
        string outgoingCurrency = currs[0];
        double incomingAmount = sale.amount * sale.price;
        string incomingCurrency = currs[1] ;
        
        currencies[incomingCurrency] += incomingAmount;
        currencies[outgoingCurrency] -= outgoingAmount;
    }
    
    // bid logic
    
    if (sale.orderType == OrderBookType::bidsale)
    {
        double incomingAmount = sale.amount;
        string incomingCurrency = currs[0];
        double outgoingAmount = sale.amount * sale.price;
        string outgoingCurrency = currs[1] ;
        
        currencies[incomingCurrency] += incomingAmount;
        currencies[outgoingCurrency] -= outgoingAmount;
    }
}     
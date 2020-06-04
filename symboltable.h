#ifndef _SYMBOLTABLE_
#define _SYMBOLTABLE_

#include <iostream>
#include <string>
using namespace std;

class SymbolTable
{
    private:
        string symbol;
        int address;
    public:
        SymbolTable(string symbol, int address)
        {
            this->symbol = symbol;
            this->address = address;
        }

        string getSymbol()
        {
            return symbol;
        }

        int getAddress()
        {
            return address;
        }

};


class SymbolTableMap
{
    private:
        SymbolTable **table;
    public:
        SymbolTableMap();
        void addEntry(string, int);
        void display();
        bool contains(string);
        int getAddress(string);
        ~SymbolTableMap();
};

#endif //_SYMBOLTABLE_
#ifndef _SYMBOLTABLE_
#define _SYMBOLTABLE_

#define MAX 24576

#include <iostream>
#include <string>
using namespace std;

class Entry
{
        string symbol;
        int address;
        Entry* nextEntry;
    public:
        Entry();
        Entry(string symbol, int address);
        void print();
        friend class SymbolTable; //This means Symbol Table class can access all private members of Entry class
};


class SymbolTable
{
        Entry* entryHead[MAX];
    public:
        SymbolTable();
        void addEntry(string symbol, int address);
        bool contains(string symbol);
        int getAddress(string symbol);
        void display();
        ~SymbolTable();
};

#endif //_SYMBOLTABLE_
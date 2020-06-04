#include <iostream>
#include "symboltable.h"

using namespace std;

const int TABLE_SIZE = 24576;


int hashFunction(string symbol)
{
    int total = 0;
    for (int i = 0; i < symbol.length(); i++)
    {
        total = total + int(symbol[i]);
    }
    cout << "Symbol:        " << symbol << "    Hash:       " << total % 13 << endl;
    return total % 13; //Or prime numbers like 17, 29, 41, 43, 101, 103
}

//Create a new Symbol Table of size 24576
SymbolTableMap::SymbolTableMap()
{
    table = new SymbolTable* [TABLE_SIZE];
    for (int i = 0; i < TABLE_SIZE; i++) table[i] = NULL;
}

//Adds a new entry to the Symbol Table
void SymbolTableMap::addEntry(string symbol, int address)
{
    SymbolTable *tableEntry = (struct SymbolTable*) malloc(sizeof(SymbolTable));
    tableEntry = new SymbolTable(symbol, address);

    int hash = hashFunction(symbol);
    while (table[hash] != NULL)
    {
        ++hash; //Using linear probing to avoid collision
    }

    table[hash] = tableEntry;
}

//Checks if the Symbol Table already contains the symbol supplied as parameter
bool SymbolTableMap::contains(string symbol)
{
    int hash = hashFunction(symbol);
    while (table[hash] != NULL)
    {
        if (table[hash]->getSymbol() == symbol) return true;
        ++hash;
    }

    return false;
}

//Gets the corresponding address of the symbol supplied as parameter
int SymbolTableMap::getAddress(string symbol)
{
    int hash = hashFunction(symbol);
    while (table[hash] != NULL)
    {
        if (table[hash]->getSymbol() == symbol) return table[hash]->getAddress();
        ++hash;
    }
}

void SymbolTableMap::display()
{
    cout << "--------------------" << "Symbol Table Contents" << "--------------------" << "\n"
            << "        Symbol          " << "------------------" << "     Address    " << endl;

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        if(table[i] != NULL)
        {
            cout <<"        " << table[i]->getSymbol() << "                                  " << table[i]->getAddress() << endl;
        }
    }
}

//SymbolTableMap Deconstructor
SymbolTableMap::~SymbolTableMap()
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        if (table[i] != NULL) delete table[i];
    }
    delete[] table;
}
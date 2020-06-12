#include <iostream>
#include "symboltable.h"

using namespace std;

int hashFunction(string& input); //Prorotype

//Defining methods of the Entry class
Entry::Entry()
{
    nextEntry = NULL;
};

Entry::Entry(string symbol, int address)
{
    this->symbol = symbol;
    this->address = address;
    nextEntry = NULL;
}

Entry::print()
{
    cout << "Symbol:    " << symbol
         << "       Address:    " << address << endl;
}

//Defining functions of the SymbolTable class
SymbolTable::SymbolTable()
{
    for (int i = 0; i < MAX; i++)
        entryHead[i] = NULL;
}

SymbolTable::addEntry(string symbol, int address)
{
    int hashResult = hashFunction(symbol);
    Entry* newSymbolTablePointer = new Entry(symbol, address);

    if (entryHead[hashResult] == NULL)
    {
        entryHead[hashResult] = newSymbolTableEntry;
        cout << "Symbol " << symbol << " and Address " << address << " successfully added (no collision)" << endl;
    }
    else
    {
        Entry* insertPointer = entryHead[hashResult]
        while (insertPointer->nextEntry != NULL)
            insertPointer = insertPointer->nextEntry;

        insertPointer->nextEntry = newSymbolTableEntry;
        cout << "Symbol " << symbol << " and Address " << address << " successfully added (after collision)" << endl;
    }
    
}

SymbolTable::contains(string symbol)
{
    int hashResult = hashFunction(symbol);
    Entry *ptr = entryHead[hashResult];

    if (ptr == NULL)
        return false;

    while (ptr != NULL)
    {
        if (ptr->symbol == symbol)
        {
            return true;
        }

        ptr = ptr->nextEntry;
    }

    return false;
}

SymbolTable::getAddress(string symbol)
{
    int hashResult = hashFunction(symbol);
    Entry *ptr = entryHead[hashResult];

    if (ptr == NULL)
    {
        cout << "This location in the symbol table has no value." << endl;
        exit(1);
    }

    while (ptr != NULL)
    {
        if (ptr->symbol == symbol)
        {
            cout << "Address of symbol " << symbol << " found!" << endl;
            return ptr->address;
        }

        ptr = ptr->nextEntry;
    }

    cout << "Nothing found here!" << endl;
    exit(2);
}




//Hash Function
int hashFunction(string& input)
{
    int total = 0;
    for (int i = 0; i < input.length(); i++)
    {
        total = total + input[i]; //This will be adding the ASCII code to total
    }

    cout << "Input:     " << input 
         << "\nHash:    " << (total % 100) << endl;

    return (total % 100);
}
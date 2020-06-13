#include <iostream>
#include "symboltable.h"

using namespace std;

int hashFunction(string& input); //Prorotype

//Defining methods of the Entry class
//Basic entry 
Entry::Entry()
{
    nextEntry = NULL;
};

//Entry with supplied symbol and address
Entry::Entry(string symbol, int address)
{
    this->symbol = symbol;
    this->address = address;
    nextEntry = NULL;
}

//Print One Symbol Table Entry
void Entry::print()
{
    cout << "Symbol:    " << symbol
         << "       Address:    " << address << endl;
}

//Defining functions of the SymbolTable class

//Initialize a Symbol Table
SymbolTable::SymbolTable()
{
    for (int i = 0; i < MAX; i++)
        entryHead[i] = NULL;
}

//Display all entries of the Symbol Table
void SymbolTable::display()
{
    for (int i = 0; i < MAX; i++)
    {
        if (entryHead[i] != NULL)
        {
            entryHead[i]->print();
        }
    }
}

//Add New Entry to Symbol Table
void SymbolTable::addEntry(string symbol, int address)
{
    int hashResult = hashFunction(symbol);
    Entry* newSymbolTablePointer = new Entry(symbol, address);

    if (entryHead[hashResult] == NULL)
    {
        entryHead[hashResult] = newSymbolTablePointer;
        cout << "Symbol " << symbol << " and Address " << address << " successfully added (no collision)" << endl;
    }
    else
    {
        Entry* insertPointer = entryHead[hashResult];
        while (insertPointer->nextEntry != NULL)
            insertPointer = insertPointer->nextEntry;

        insertPointer->nextEntry = newSymbolTablePointer;
        cout << "Symbol " << symbol << " and Address " << address << " successfully added (after collision)" << endl;
    }
    
}

//Check if symbol exists in Symbol Table
bool SymbolTable::contains(string symbol)
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

//Get address of symbol in Symbol Table
int SymbolTable::getAddress(string symbol)
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

//Free Symbol Table Memory
SymbolTable::~SymbolTable()
{
    for (int i = 0; i < MAX; i++)
    {
        if (entryHead[i] != NULL)
            delete entryHead[i];
    }
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
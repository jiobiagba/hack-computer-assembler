#include <iostream>
#include "symboltable.h"

using namespace std;

int hashFunction(string& input); //Prorotype

//Defining methods of the Entry class
//Basic entry 
// Entry::Entry()
// {
//     nextEntry = NULL;
// };

//Entry with supplied key and address
Entry::Entry(string key, int address)
{
    this->key = key;
    this->address = address;
}

//Print One key Table Entry
void Entry::print()
{
    cout << "key:    " << key
         << "       Address:    " << address << endl;
}

//Defining functions of the keyTable class

//Initialize a key Table
SymbolTable::SymbolTable()
{
    for (int i = 0; i < MAX; i++)
        entryHead[i] = NULL;
}

//Display all entries of the key Table
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

//Add New Entry to key Table
void SymbolTable::addEntry(string& key, int address)
{
    int hashResult = hashFunction(key);
    cout << "Key at top of ADD ENTRY:   " << key << endl;
    Entry* newkeyTablePointer = new Entry(key, address);
    int exitCode = 1;

    while (exitCode > 0)
    {
        if (entryHead[hashResult] == NULL)
        {
            entryHead[hashResult] = newkeyTablePointer;
            cout << "key " << key << " and Address " << address << " successfully added after " << exitCode << " checks" << endl;
            exitCode = 0;
        }
        else
        {
            {
                hashResult++;
            }
        }
        
    }

    // if (entryHead[hashResult] == NULL)
    // {
    //     entryHead[hashResult] = newkeyTablePointer;
    //     cout << "key " << key << " and Address " << address << " successfully added (no collision)" << endl;
    // }
    // else
    // {
    //     while (entryHead[hashResult] != NULL)
    //     {
    //         hashResult++;
    //         if (entryHead[hashResult] == NULL)
    //         {
    //             entryHead[hashResult] = newkeyTablePointer;
    //             cout << "key " << key << " and Address " << address << " successfully added (after collision)" << endl;
    //         }
    //     }
    // }
    
}

//Check if key exists in key Table
bool SymbolTable::contains(string key)
{
    int hashResult = hashFunction(key);

    if (entryHead[hashResult] == NULL)
        return false;

    while (entryHead[hashResult] != NULL)
    {
        if (entryHead[hashResult]->key == key)
        {
            return true;
        }

        hashResult++;
    }

    return false;
}

//Get address of key in key Table
int SymbolTable::getAddress(string key)
{
    int hashResult = hashFunction(key);
    

    if (entryHead[hashResult] == NULL)
    {
        cout << "This location in the key table has no value." << endl;
        exit(1);
    }

    while (entryHead[hashResult] != NULL)
    {
        if (entryHead[hashResult]->key == key)
        {
            cout << "Address of key " << key << " found!" << endl;
            return entryHead[hashResult]->address;
        }

        hashResult++;
    }

    cout << "Nothing found here!" << endl;
    exit(2);
}

//Free key Table Memory
SymbolTable::~SymbolTable()
{
    for (int i = 0; i < MAX; i++)
    {
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
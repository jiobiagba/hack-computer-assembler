//Defining parser module methods
#include <iostream>
#include <bits/stdc++.h>
#include "parser.h"
using namespace std;

string removeAllWhiteSpaces(string variableToClean); //Prototype

//Routine to open file and get ready to parse it.
void Parser::initializer(string filenameToParse)
{
    // ifstream asmFile( filenameToParse);
    asmFile.open(filenameToParse);
    if(  !asmFile || !asmFile.is_open())
     {
         cerr << "Error in opening file " << filenameToParse << endl;
         exit(1);
     }
    

    lineCounter = 0;
}


//Routine to check if there are more commands (more non-empty lines and we aren't at the end of the file)
bool Parser::hasMoreCommands()
{
        getline(asmFile, lineHolder);
        if (  !asmFile) //asmFile.eof() was previously here
        {
            asmFile.close();
            return false;
        }


        //Handling comments and whitespace
        string holderA = lineHolder;
        const int indexOfStartOfComment = lineHolder.find("//");

        if(indexOfStartOfComment != -1)
        {
            holderA = holderA.erase(indexOfStartOfComment);
        }

        if(lineHolder.length() == 0 || holderA.length() == 0)
        {
            lineHolder = "IGNORE";
        } else
        {
            lineHolder = holderA;
            lineCounter = lineCounter + 1;
        }

        return true;
}


//Routine to read next command and make it current command
void Parser::advance()
{
    cout << "Next instruction to process is:        " << lineHolder << endl;
    cout << "Length before whitespace removal:  " << lineHolder.length() << endl;
    nextCommand = removeAllWhiteSpaces(lineHolder);
    cout << "Length after whitespace removal:   " << nextCommand.length() << endl;
}


//Routine to get the comand type of a line of asm file
string Parser::commandType()
{
    if(nextCommand[0] == '@') return "A_COMMAND";
    if(nextCommand.find('=') != -1 || nextCommand.find(';') != -1) return "C_COMMAND";
    if(nextCommand[0] == '(' && nextCommand[nextCommand.length() - 1] == ')') return "L_COMMAND";

    return nextCommand;
}


//Routine to return the symbol or decimal of current command
string Parser::symbol()
{
    if(Parser::commandType() == "A_COMMAND")
    {
        string aCommand = (nextCommand.erase(0,1));
        cout << "acommand:  " << aCommand << "  of length   " << aCommand.length() << endl;
        return aCommand;
    }
    else if(Parser::commandType() == "L_COMMAND")
    {
        string lCommand = (nextCommand.erase(0,1)).erase(nextCommand.length() - 1, 1);
        cout << "lcommand:  " << lCommand << endl;
        return lCommand;
    }

    return "VOID";
}


//Routine to return the dest mnemonic of a C_COMMAND
string Parser::dest()
{
    if(Parser::commandType() == "C_COMMAND")
    {
        string instruction = nextCommand;
        int indexOfEqualTo = nextCommand.find('=');
        if(indexOfEqualTo != -1)
        {
            string destMnemonic = instruction.erase(indexOfEqualTo);
            cout << "nextCommand    Instruction     destMnemonic    :" << nextCommand << "  " << instruction << "   " << destMnemonic << endl;
            return destMnemonic;
        }
    }

    return "null";
}


//Routine to return the comp mnemonic of a C_COMMAND
string Parser::comp()
{
    if(Parser::commandType() == "C_COMMAND")
    {
        string instruction1 = nextCommand;
        string instruction2 = nextCommand;
        int indexOfEqualTo = nextCommand.find('=');
        int indexOfSemiColon = nextCommand.find(';');
        if(indexOfEqualTo != -1 && indexOfSemiColon == -1)
        {
            string compMnemonic = instruction1.erase(0, indexOfEqualTo + 1);
            return compMnemonic;
        }
        if(indexOfEqualTo == -1 && indexOfSemiColon != -1)
        {
            string compMnemonic = instruction2.erase(indexOfSemiColon);
            return compMnemonic;
        }   
        
    }

    return "null";
}


//Routine to return the jump mnemonic of a C_COMMAND
string Parser::jump()
{
    if(Parser::commandType() == "C_COMMAND")
    {
        string instruction = nextCommand;
        int indexOfSemicolon = nextCommand.find(';');
        if(indexOfSemicolon != -1)
        {
            string jumpMnemonic = instruction.erase(0, indexOfSemicolon + 1);
            return jumpMnemonic;
        }

        return "null";
    }
}

//Function to remove all leading, trailing and in-between white spaces from string
string removeAllWhiteSpaces(string variableToClean)
{
    variableToClean.erase(std::remove_if(variableToClean.begin(), variableToClean.end(), ::isspace), variableToClean.end());
    return variableToClean;
}
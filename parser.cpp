//Defining parser module methods
#include "parser.h"
using namespace std;

//Routine to open file and get ready to parse it.
void Parser::initializer(string filenameToParse)
{
    ifstream asmFile( filenameToParse);
    if(  !asmFile || !asmFile.is_open())
        cerr << "Error in opening file " << filenameToParse << endl;
    
    lineCounter = 0;
}


//Routine to check if there are more commands (more non-empty lines and we aren't at the end of the file)
bool Parser::hasMoreCommands()
{
    while( getline( asmFile, lineHolder))
    {
        if (  lineHolder.length() == 0 || asmFile.eof()) return false;
        //Later I'll add logic to check for comment and whitespace
        return true;
    }
    return false;
}


//Routine to read next command and make it current command
void Parser::advance()
{
    while(Parser::hasMoreCommands() == true)
    {
        nextCommand = lineHolder;
    }
}


//Routine to get the comand type of a line of asm file
string Parser::commandType()
{
    if(nextCommand[0] == '@') return "A_COMMAND";
    if(nextCommand.find_first_of('=') != -1 || nextCommand.find_last_of(';') != -1) return "C_COMMAND";
    if(nextCommand[0] == '(' && nextCommand[nextCommand.length() - 1] == ')') return "L_COMMAND";

    return "Error in determining command type of line:   " + nextCommand;
}


//Routine to return the symbol or decimal of current command
string Parser::symbol()
{
    if(Parser::commandType() == "A_COMMAND")
    {
        string aCommand = nextCommand.erase(0,1);
        return aCommand;
    }
    else if(Parser::commandType() == "L_COMMAND")
    {
        string lCommand = (nextCommand.erase(0,1)).erase(nextCommand.length() - 1, 1);
        return lCommand;
    }

    return "Error in extracting symbol from line:   " + nextCommand;
}


//Routine to return the dest mnemonic of a C_COMMAND
string Parser::dest()
{
    if(Parser::commandType() == "C_COMMAND")
    {
        string instruction = nextCommand;
        int indexOfEqualTo = nextCommand.find_first_of('=');
        if(indexOfEqualTo != -1)
        {
            string destMnemonic = instruction.erase(indexOfEqualTo);
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
        int indexOfEqualTo = nextCommand.find_first_of('=');
        int indexOfSemiColon = nextCommand.find_last_of(';');
        if(indexOfEqualTo != -1 && indexOfSemiColon == -1)
        {
            string compMnemonic = instruction1.erase(0, indexOfEqualTo + 1);
            return compMnemonic;
        }
        else if (indexOfEqualTo == -1 && indexOfSemiColon != -1)
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
        int indexOfSemicolon = nextCommand.find_last_of(';');
        if(indexOfSemicolon != -1)
        {
            string jumpMnemonic = instruction.erase(0, indexOfSemicolon + 1);
            return jumpMnemonic;
        }

        return "null";
    }
}
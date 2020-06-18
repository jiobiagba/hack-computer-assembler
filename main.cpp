//Main application doing the comversion
#include "parser.h"
#include "code.h"
#include "symboltable.h"
#include <bitset>
#include <fstream>
using namespace std;

string getFileName(string inputFile); //Prototype
string convertTo16BitBinary(int inputAddress); //Prototype
void initializeSymbolTable(string symbolsFile); //Protoype
bool numberVerifierFunction(string& variableToVerify); //Prototype
void firstPassForA(Parser& ParserTwo); //Prototype
void firstPassForL(Parser& ParserTwo); //Prototype

SymbolTable newSymbolTable;
Parser parserObject;
Parser ParserTwo;
Code codeObject;

int addressOfNextVariable;
string symbol, dest, comp, jump;


int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        cerr << "Use: ./Assembler <filename>.asm" << endl;
        return 1;
    }

    parserObject.initializer( argv[1]); //Open asm file for first pass
    initializeSymbolTable("predefinedsymbols.txt"); //Initialize Symbol Table
    firstPassForL(parserObject); //First pass to build symbol table with only L Commands
    
    //Close input asm file
    if( !parserObject.asmFile.eof())
    {
        cerr << "Error in reading file " << argv[1] << endl;
        return 2;
    }
    parserObject.asmFile.close();

    parserObject.initializer( argv[1]); //Open asm file for first pass
    firstPassForA(parserObject); //First pass to build symbol table with A Commands

    //Close input asm file
    if( !parserObject.asmFile.eof())
    {
        cerr << "Error in reading file " << argv[1] << endl;
        return 2;
    }
    parserObject.asmFile.close();

    ParserTwo.initializer( argv[1]); //Open asm file for second pass
    ofstream hackFile( getFileName(argv[1]) + ".hack"); //Open hack file to write binary code

    //Second Pass
    while(ParserTwo.hasMoreCommands())
    {
        string symbolMine, destMine, compMine, jumpMine;
        int addressMine;
        ParserTwo.advance();
        string commandTypeMine = ParserTwo.commandType();
        if (commandTypeMine != "IGNORE")
        {
            symbolMine = ParserTwo.symbol();
            //If symbol is of A_COMMAND type, proceed ...
            if( symbolMine != "VOID" && commandTypeMine == "A_COMMAND")
            {
                if( numberVerifierFunction(symbolMine)) //If it's a number, don't check symbol table. Just convert to binary and write to file
                {
                    cout << "Number added to file:  " << symbolMine << endl;
                    string binarySymbol = convertTo16BitBinary(stoi(symbolMine));
                    hackFile << binarySymbol << endl;
                }
                else if( !numberVerifierFunction(symbolMine)) //If it's not a number, get address from symbol table, convert to binary and write to file
                {
                    if( symbolMine == "R0")
                    {
                        addressMine = newSymbolTable.getAddress("SP");
                        cout << "Symbol added to file:  " << addressMine << endl;
                        string binarySymbol = convertTo16BitBinary(addressMine);
                        hackFile << binarySymbol << endl;
                    }
                    else if( symbolMine == "R1")
                    {
                        addressMine = newSymbolTable.getAddress("LCL");
                        cout << "Symbol added to file:  " << addressMine << endl;
                        string binarySymbol = convertTo16BitBinary(addressMine);
                        hackFile << binarySymbol << endl;
                    }
                    else if( symbolMine == "R2")
                    {
                        addressMine = newSymbolTable.getAddress("ARG");
                        cout << "Symbol added to file:  " << addressMine << endl;
                        string binarySymbol = convertTo16BitBinary(addressMine);
                        hackFile << binarySymbol << endl;
                    }
                    else if( symbolMine == "R3")
                    {
                        addressMine = newSymbolTable.getAddress("THIS");
                        cout << "Symbol added to file:  " << addressMine << endl;
                        string binarySymbol = convertTo16BitBinary(addressMine);
                        hackFile << binarySymbol << endl;
                    }
                    else if( symbolMine == "R4")
                    {
                        addressMine = newSymbolTable.getAddress("THAT");
                        cout << "Symbol added to file:  " << addressMine << endl;
                        string binarySymbol = convertTo16BitBinary(addressMine);
                        hackFile << binarySymbol << endl;
                    }
                    else 
                    {
                        addressMine = newSymbolTable.getAddress(symbolMine);
                        cout << "Symbol added to file:  " << addressMine << endl;
                        string binarySymbol = convertTo16BitBinary(addressMine);
                        hackFile << binarySymbol << endl;
                    }
                }
            }
            else if( symbolMine == "VOID" && commandTypeMine == "C_COMMAND") //If it's a C_COMMAND, build C_COMMAND code and write to file
            {
                cout << "C_Command to be processed: " << symbolMine << endl;
                destMine =  codeObject.dest(ParserTwo.dest());
                compMine =  codeObject.comp(ParserTwo.comp());
                jumpMine = codeObject.jump(ParserTwo.jump());

                cout << "Processed C_Command:   " << destMine + compMine + jumpMine << endl;

                hackFile << "111" + compMine + destMine + jumpMine << endl;
            }
        }
    }

    cout << "Conversion of assembly language to machine code completed." << endl;
    cout << ParserTwo.getLineCount() << " lines of actual code processed." << endl;
    hackFile.close();
    newSymbolTable.display();
    return 0;
}




//routine for extracting file name without extension
string getFileName(string inputFile)
{
    int fileNameLastIndex = inputFile.find(".asm");
    if( fileNameLastIndex == -1)
    {
        cerr << "File name extraction failed. Please choose a file with the .asm extension." << endl;
        exit(1);
    }

    string newFileName = inputFile.erase(fileNameLastIndex);
    return newFileName;
}

//routine for converting numbers to binary
string convertTo16BitBinary(int inputAddress)
{
    long decimalNumber = stoi(to_string(inputAddress));
    bitset<16> b(decimalNumber);
    cout << "String " << inputAddress << " is " << decimalNumber 
         << " in decimal and " << b << " as a 16-bit binary." << endl;

    return b.to_string();
}

//Routine to initialize symbol table with predefined symbols
void initializeSymbolTable(string symbolsFile)
{
    string newLine, holderA, holderB, leftSide, rightSide;
    int indexOfEqualsTo;
    ifstream inputFile(symbolsFile);
    while(getline(inputFile, newLine))
    {
        holderA = newLine;
        holderB = newLine;
        indexOfEqualsTo = newLine.find("=");

        if(indexOfEqualsTo == -1)
        {
             cerr << "No '=' in " << newLine << endl;
             inputFile.close();
             exit(1);
        }

        leftSide = holderA.erase(indexOfEqualsTo);
        rightSide = holderB.erase(0, indexOfEqualsTo + 1);

        newSymbolTable.addEntry(leftSide, stoi(rightSide));
    }


    if(!inputFile.eof())
    {
        cerr << "Error reading file " << symbolsFile << endl;
        exit(2);
    }

    addressOfNextVariable = newSymbolTable.getAddress("R15") + 1;
    inputFile.close();
}


void firstPassForL(Parser& ParserTwo)
{
    while (ParserTwo.hasMoreCommands())
    {
        ParserTwo.advance();
        string commandTypeMine = ParserTwo.commandType();
        string symbolMine = ParserTwo.symbol();
        if(commandTypeMine == "L_COMMAND" && symbolMine != "VOID")
        {
            string& symbolRef = symbolMine;
            int lineAddress = ParserTwo.getLineCount();
            /*
            If the L_Command hasn't been preadded as an A_COMMAND, then add L_COMMAND to symbol table
            else change the address of the existing L_COMMAND previously added as an A_COMMAND to the right line count
            */
            if(!newSymbolTable.contains(symbolMine))
            {
                cout << "L COMMAND for insertion:   " << symbolRef << " with address     " << lineAddress << endl;
                newSymbolTable.addEntry(symbolRef, lineAddress);
            }
            else if(newSymbolTable.contains(symbolMine))
            {
                cout << symbolMine << " already exists in Symbol table!" << endl;
            }
        }
    }
}

//Routine to populate symbol table with symbols
void firstPassForA(Parser& ParserTwo)
{
    while (ParserTwo.hasMoreCommands())
    {
        ParserTwo.advance();
        string commandTypeMine = ParserTwo.commandType();
        string symbolMine = ParserTwo.symbol();
        if(commandTypeMine == "A_COMMAND" && symbolMine != "VOID" )
        {   
            if( symbolMine != "R0" && symbolMine != "R1" && symbolMine != "R2" && symbolMine != "R3" && symbolMine != "R4")
            {
                //Only Add an A_COMMAND if the A_COMMAND does not exist in Symbol Table   
                if(!newSymbolTable.contains(symbolMine))
                {
                    string& symbolRef = symbolMine;
                    bool isNumber = numberVerifierFunction(symbolMine);
                    if(!isNumber)
                    {
                        cout << "A Command for Insertion:       " << symbolRef << "    with length     "<< symbolMine.length() << " \n" << endl;
                        newSymbolTable.addEntry(symbolRef, addressOfNextVariable);
                        addressOfNextVariable++;
                    }
                }
            }
        }
    }   
}


//Function to verify if a string is made up of only digits
bool numberVerifierFunction(string& variableToVerify)
{
    for (int n = 0; n < variableToVerify.length(); n++)
    {
        cout << "Checking for only numbers ......" << variableToVerify[n] << endl;
        if (!isdigit(variableToVerify[n]))
        {
            cout << "Test for only numbers failed,  returned:        " << false << endl;
            return false;
        }
    }

    cout << "Test for only numbers returned:        " << true << endl;
    return true;
}
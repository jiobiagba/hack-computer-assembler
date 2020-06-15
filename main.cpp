//Main application doing the comversion
#include "parser.h"
#include "code.h"
#include "symboltable.h"
#include <bitset>
using namespace std;

string getFileName(string inputFile); //Prototype
string convertTo16BitBinary(string inputSymbol); //Prototype
void initializeSymbolTable(string symbolsFile); //Protoype
void firstPass(Parser& newParserObject); //Prototype
void secondPass(); //Prototype

SymbolTable newSymbolTable;
Parser parserObject;
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

    parserObject.initializer( argv[1]);
    ofstream hackFile( getFileName(argv[1]) + ".hack");
    initializeSymbolTable("predefinedsymbols.txt");
    firstPass(parserObject);
     
    if( !parserObject.asmFile.eof())
    {
        cerr << "Error in reading file " << argv[1] << endl;
        return 2;
    }

    cout << "Conversion of assembly language to machine code completed." << endl;
    cout << parserObject.getLineCount() << " lines of actual code processed." << endl;
    hackFile.close();
    newSymbolTable.display();
    newSymbolTable.getAddress("MAX");
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

//routine for converting symbol to binary
string convertTo16BitBinary(string inputSymbol)
{
    long decimalNumber = stoi(inputSymbol);
    bitset<16> b(decimalNumber);
    cout << "String " << inputSymbol << " is " << decimalNumber 
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
    // newSymbolTable.display();
    inputFile.close();
}


//Routine to populate symbol table with symbols
void firstPass(Parser& newParserObject)
{
    while (newParserObject.hasMoreCommands())
    {
        newParserObject.advance();
        string commandTypeMine = newParserObject.commandType();
        string symbolMine = newParserObject.symbol();
        if(commandTypeMine == "A_COMMAND" && symbolMine != "VOID" )
        {        
            string& symbolRef = symbolMine;
            cout << "A Command for Insertion:       " << symbolRef << "    with length     "<< symbolMine.length() << " \n" << endl;
            newSymbolTable.addEntry(symbolRef, addressOfNextVariable);
            addressOfNextVariable++;
        }
    }
    
}

//Second pass
void secondPass()
{
    while(parserObject.hasMoreCommands())
    {
        parserObject.advance();
        if(parserObject.commandType() != "IGNORE")
        {
            symbol = parserObject.symbol();
            if( symbol != "VOID")
            {
                cout << "Symbol added to file:  " << symbol << endl;
                string binarySymbol = convertTo16BitBinary(symbol);
                // hackFile << binarySymbol << endl;
            }
            else if( symbol == "VOID")
            {
                cout << "C_Command to be processed: " << symbol << endl;
                dest =  codeObject.dest(parserObject.dest());
                comp =  codeObject.comp(parserObject.comp());
                jump = codeObject.jump(parserObject.jump());

                cout << "Processed C_command:   " << dest + comp + jump << endl;

                // hackFile << "111" + comp + dest + jump << endl;
            }
        }
    }
}
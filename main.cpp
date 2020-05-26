//Main application doing the comversion
#include "parser.h"
#include "code.h"
using namespace std;

string getFileName(string inputFile); //Prototype



int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        cerr << "Use: ./Assembler <filename>.asm" << endl;
        return 1;
    }

    Parser parserObject;
    Code codeObject;
    string symbol, dest, comp, jump;

    parserObject.initializer( argv[1]);
    ofstream hackFile( getFileName(argv[1]) + ".hack");
    while(parserObject.hasMoreCommands())
    {
        parserObject.advance();
        symbol = parserObject.symbol();
        if( symbol != "VOID")
        {
            cout << "Symbol added to file:  " << symbol << endl;
            hackFile << symbol << endl;
        }
        else if( symbol == "VOID")
        {
            cout << "C_Command to be processed: " << symbol << endl;
            dest =  codeObject.dest(parserObject.dest());
            comp =  codeObject.comp(parserObject.comp());
            jump = codeObject.jump(parserObject.jump());

            cout << "Processed C_command:   " << dest + comp + jump << endl;

            hackFile << "111" + dest + comp + jump << endl;
        }
    }
     
    if( !parserObject.asmFile.eof())
    {
        cerr << "Error in reading file " << argv[1] << endl;
        return 2;
    }


    cout << "Conversion of assembly language to machine code completed." << endl;
    hackFile.close();
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
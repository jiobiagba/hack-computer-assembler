//Compile to file Assembler
//Initial Idea for assembler done 20th May 2020.
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string getFileName(string inputFile); //Prototype

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        cerr << "Use: ./Assembler <filename.extension>" << endl;
        return 1;
    }

    ifstream asmFile( argv[1]);
    if(!asmFile)
    {
        cerr << "Error in opening file " << argv[1] << endl;
        return 2;
    }

    ofstream hackFile( getFileName(argv[1]) + ".hack");
    string eachLine;
    int lineCounter = 0;
    while( getline( asmFile, eachLine))
    {
        if(eachLine.length() != 0)
        {
            hackFile << eachLine << endl;
            lineCounter = lineCounter + 1;
        }
    }

    if(!asmFile.eof())
    {
        cerr << "Error in reading file " << argv[1] << endl;
        return 3;
    }

    cout << lineCounter << " lines read." << endl;
    asmFile.close();
    hackFile.close();
    return 0;
}




//Function to extract file name without extension
string getFileName(string inputFile)
{
    int fileNameLastIndex = inputFile.find(".txt");
    if( fileNameLastIndex == -1)
    {
        cerr << "File name extraction failed. Please use the right extension." << endl;
        exit(1);
    }

    string newFileName = inputFile.erase(fileNameLastIndex);
    return newFileName;
}
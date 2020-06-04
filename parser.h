#ifndef _PARSER_
#define _PARSER_

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Parser
{
    private:
        string nextCommand;
        int lineCounter;
    public:
        int getLineCount()
        {
            return lineCounter;
        }
        ifstream asmFile;
        string lineHolder;
        void initializer(string);
        bool hasMoreCommands();
        void advance();
        string commandType();
        string symbol();
        string dest();
        string comp();
        string jump();
};

#endif //_PARSER_

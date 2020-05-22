#ifndef _PARSER_
#define _PARSER_

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Parser
{
    private:
        ifstream asmFile;
        string lineHolder;
        string nextCommand;
        int lineCounter;
    public:
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

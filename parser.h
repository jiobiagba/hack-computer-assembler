#ifndef _PARSER_
#define _PARSER_

#include <iostream>
#include <fstream>
using namespace std;

class Parser
{
    public:
        void initializer(ifstream);
        bool hasMoreCommands();
        void advance();
        string commandType();
        string symbol();
        string dest();
        string comp();
        string jump();
};

#endif //_PARSER_

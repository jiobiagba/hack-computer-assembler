#ifndef _CODE_
#define _CODE_

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Code
{
    private:
        ifstream destFile;
        ifstream compFile;
        ifstream jumpFile;
        string codeLine;
    public:
        string dest(string);
        string comp(string);
        string jump(string);
};

#endif //_CODE_
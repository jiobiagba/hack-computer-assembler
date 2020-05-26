//Defining code module methods
#include <iostream>
#include "code.h"
using namespace std;

//Routine for getting 3-bit dest code
string Code::dest(string mnemonic)
{
   destFile.open("dest.txt") ;
   if(!destFile.is_open())
   {
       cerr << "Ensure dest.txt exists in this directory.";
       exit(1);
   }

    cout << "Mnemonic in code dest:  " << mnemonic << endl;

   while(getline( destFile, codeLine))
   {
       string leftSide, rightSide, holder1, holder2 = codeLine;
       int indexOfEqualTo = codeLine.find('=');
       holder1 = codeLine;
       leftSide = holder2.erase(indexOfEqualTo);
       cout << "destleftside:       " << leftSide << endl;
       rightSide = holder1.erase(0, indexOfEqualTo + 1);
       cout << "destRightside:      " << rightSide << endl;

       if(mnemonic == leftSide)
       {
           destFile.close();
           return rightSide;
       }
   }

}

//Routine for getting 7-bit comp code
string Code::comp(string mnemonic)
{
   compFile.open("comp.txt") ;
   if(!compFile.is_open()) cerr << "Ensure comp.txt exists in this directory.";

    cout << "Mnemonic in code comp:  " << mnemonic << endl;

   while(getline( compFile, codeLine))
   {
       string leftSide, rightSide, holder1, holder2 = codeLine;
       int indexOfEqualTo = codeLine.find('=');
       holder1 = codeLine;
       leftSide = holder2.erase(indexOfEqualTo);
       cout << "compLeftSide:       " << leftSide << endl;
       rightSide = holder1.erase(0, indexOfEqualTo + 1);
       cout << "compRightSide:      " << rightSide << endl;

       if(mnemonic == leftSide)
       {
           compFile.close();
           return rightSide;
       }
   }
}

//Routine for getting 3-bit jump code
string Code::jump(string mnemonic)
{
   jumpFile.open("jump.txt") ;
   if(!jumpFile.is_open()) cerr << "Ensure jump.txt exists in this directory.";

    cout << "Mnemonic in code jump:  " << mnemonic << endl;
   while(getline( jumpFile, codeLine))
   {
       string leftSide, rightSide, holder1, holder2 = codeLine;
       int indexOfEqualTo = codeLine.find('=');
       holder1 = codeLine;
       leftSide = holder2.erase(indexOfEqualTo);
       rightSide = holder1.erase(0, indexOfEqualTo + 1);

       if(mnemonic == leftSide)
       {
           jumpFile.close();
           return rightSide;
       }
   }

}
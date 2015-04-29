/*****************************
@author ltf1320
@modifier

*****************************/
#include <iostream>
#include <mainServer/MainServerConsole.h>
using namespace std;

int main()
{
    cout<<"ChaosFight Main Server"<<endl;
    MainServerConsole console;
    string cmd;
    while(true)
    {
        cin>>cmd;
        console.excute(cmd);
    }
    return 0;
}

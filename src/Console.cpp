/*****************************
@author ltf1320
@modifier

*****************************/
#include "Console.h"
#include <stdlib.h>
#include <iostream>

Console::Console()
{
    //ctor
}

Console::~Console()
{
    //dtor
}
void
Console::excute(string cmd)
{
    if(!cmd.compare("quit"))
    {
        cout<<"quit by command"<<endl;
        exit(0);
    }
    else if(!this->priExcute(cmd))
        cout<<"unkown command"<<endl;
}

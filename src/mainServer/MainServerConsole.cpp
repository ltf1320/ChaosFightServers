/*****************************
@author ltf1320
@modifier

*****************************/
#include "mainServer/MainServerConsole.h"
#include <iostream>
MainServerConsole::MainServerConsole()
{
    //ctor
}

MainServerConsole::~MainServerConsole()
{
    //dtor
}
bool
MainServerConsole::priExcute(string cmd)
{
    if(!cmd.compare("start"))
    {
        cout<<"main server started"<<endl;
    }
    else return false;
    return true;
}

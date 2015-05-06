#ifndef MAINSERVERCONSOLE_H
#define MAINSERVERCONSOLE_H

#include "Console.h"
#include "MainServer.h"
using namespace std;
class MainServerConsole : public Console
{
    public:
        MainServerConsole();
        virtual ~MainServerConsole();
        virtual bool priExcute(string cmd);
    protected:
    private:
};

#endif // MAINSERVERCONSOLE_H

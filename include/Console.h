#ifndef CONSOLE_H
#define CONSOLE_H
#include <string>
using namespace std;
class Console
{
    public:
        Console();
        virtual ~Console();
        void excute(string cmd);
        virtual bool priExcute(string cmd)=0;
    protected:
    private:
};

#endif // CONSOLE_H

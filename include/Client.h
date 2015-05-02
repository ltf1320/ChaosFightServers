#ifndef CLIENT_H
#define CLIENT_H
#include "sockBuffer.h"
#include <string>
class Client
{
    public:
        Client(int sock);
        bool login(const char* userName,const char* password);
        void recvMsg();
        int getSock();
        bool isLogined();
        std::string getUserName();
        virtual ~Client();
    protected:
        int sock;
        bool logined;
        std::string userName;
        SockBuffer* buffer;
    private:
};

#endif // CLIENT_H

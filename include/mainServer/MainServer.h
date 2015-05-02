#ifndef MAINSERVER_H
#define MAINSERVER_H

#include <map>
#include <mutex>
#include "ThreadPool.h"
#include "Client.h"
#include <string>
class MainServer
{
    public:
        static MainServer* getInstance();
        void startServer();
        Client* getClient(std::string userName);
        Client* getClient(int sock);
        void addClient(Client *client);
        void removeClient(int sock);
        static void onMessageRecv(Msg_t *msg,int sock);
        static void listenThread();
    protected:
        static MainServer* instance;
        static ThreadPool* threadPool;
       static void setnonblocking(int sock);
        int port;
        MainServer();
         ~MainServer();
        std::map<std::string,Client*> clientsByUserName;
        std::map<int,Client*> clientsBySock;
        std::mutex mtx;
    private:
};
#endif // MAINSERVER_H

#ifndef THREADPOOL_H
#define THREADPOOL_H
#include <thread>
#include <condition_variable>
#include <mutex>
#include <functional>
#include <vector>
#include "ThreadSafeQueue.h"
class ThreadPool
{
    public:
        ThreadPool(int threadNum);
        void addTast(std::function<void()> task);
        virtual ~ThreadPool();
        int getThreadNum();
        void terminate();
    protected:
        bool terminated;
        int threadNum;
        std::mutex mtx;
        std::condition_variable  cv;
        bool notified;
        std::vector<std::thread> threads;
        static void run(ThreadPool* thPool);
        ThreadSafeQueue<std::function<void()> > taskQue;
    private:
};

#endif // THREADPOOL_H

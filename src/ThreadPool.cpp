/*****************************
@author ltf1320
@modifier

*****************************/
#include "ThreadPool.h"
ThreadPool::ThreadPool(int threadNum)
{
    terminated=false;
    this->threadNum=threadNum;
    for(int i=0;i<threadNum;i++)
    {
        std::thread th(run,this);
        threads.push_back(std::move(th));
    }
}

void ThreadPool::addTast(std::function<void()> task)
{
    std::lock_guard<std::mutex> lck(mtx);
    taskQue.push(task);
    notified=true;
    cv.notify_one();
}

ThreadPool::~ThreadPool()
{
terminate();
    //dtor
}
int ThreadPool::getThreadNum()
{
    return threadNum;
}
void ThreadPool::run(ThreadPool* thPool)
{
    while(!thPool->terminated)
    {
        auto res=thPool->taskQue.popFront();
        if(res.first)
        {
            res.second();
        }
        else{
            std::unique_lock <std::mutex> lck(thPool->mtx);
            while(!thPool->notified)
                thPool->cv.wait(lck);
            if(thPool->terminated)return;
                thPool->notified=false;
        }
    }
}
void ThreadPool::terminate()
{
    terminated=true;
    notified=true;
    cv.notify_all();
    for(int i=0;i<threadNum;i++)
        threads[i].join();
}

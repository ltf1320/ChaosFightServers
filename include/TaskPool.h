#ifndef TASKPOOL_H
#define TASKPOOL_H

#include <queue>
#include <thread>
class BaseTask
{
    public :
        virtual void run()=0;
}

class TaskPool
{
    public:
        TaskPool();
        void addTask(BaseTask *task);
        virtual ~TaskPool();
    protected:
        queue<BaseTask*> taskQue;

    private:
};

#endif // TASKPOOL_H

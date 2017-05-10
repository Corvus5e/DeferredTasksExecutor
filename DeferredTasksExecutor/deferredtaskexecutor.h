
#ifndef DEFERREDTASKEXECUTOR_H
#define DEFERREDTASKEXECUTOR_H

#include <abstracttask.h>
#include <worker.h>

#include <thread>
#include <mutex>
#include <vector>
#include <queue>
#include <functional>
#include <atomic>
#include <vector>
#include <condition_variable>


struct TaskComp{
    bool operator()(const AbstractTask* op1, const AbstractTask *op2) const
    {
        return op1->getPriority() < op2->getPriority();
    }
};

class DeferredTaskExecutor {
private:
    std::mutex queue_mutex;
    std::condition_variable condition;
    std::vector<std::thread> worker_threads;
    std::priority_queue<AbstractTask*, std::vector<AbstractTask*>, TaskComp> tasks;
    std::atomic<bool> stopped;
    std::function<void (AbstractTask*)> tasks_handler;

    friend class Worker;

public:
    DeferredTaskExecutor(std::function<void (AbstractTask*)> handler);
    void addTask(AbstractTask *task);
    bool isStopped();
    void start(size_t threads_numbers);
    void stop();
    size_t queueSize() { return tasks.size(); }
    ~DeferredTaskExecutor();
};

#endif // DEFERREDTASKEXECUTOR_H


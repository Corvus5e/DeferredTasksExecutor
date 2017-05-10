
#ifndef WORKER_H
#define WORKER_H

class DeferredTaskExecutor;

class Worker {
private:
    DeferredTaskExecutor &dtask_executor;
public:
    Worker(DeferredTaskExecutor &task_executor);
    void operator()();

};

#endif // WORKER_H


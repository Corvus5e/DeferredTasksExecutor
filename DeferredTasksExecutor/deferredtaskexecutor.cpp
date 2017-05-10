
#include <deferredtaskexecutor.h>

DeferredTaskExecutor::DeferredTaskExecutor(std::function<void (AbstractTask*)> handler) :
                                           stopped(true), tasks_handler(handler)
{

}

bool DeferredTaskExecutor::isStopped()
{
    return this->stopped;
}

void DeferredTaskExecutor::stop(){
    this->stopped = true;
}

void DeferredTaskExecutor::start(size_t threads_numbers)
{
    this->stopped = false;
    for(size_t i = 0; i < threads_numbers; i++){
        worker_threads.push_back(std::thread(Worker(*this)));
    }
}

DeferredTaskExecutor::~DeferredTaskExecutor()
{
    this->stop();
    condition.notify_all();
    for(auto &t : this->worker_threads){
        if(t.joinable()){
            t.join();
        }
    }
}

void DeferredTaskExecutor::addTask(AbstractTask *task)
{
    {
        std::unique_lock<std::mutex> lock(this->queue_mutex);
        this->tasks.push(task);
    }

    condition.notify_one();
}

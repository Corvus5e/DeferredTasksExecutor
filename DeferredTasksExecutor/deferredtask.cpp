
#include <deferredtask.h>

#include <thread>
#include <chrono>

DeferredTask::DeferredTask(int priority) : AbstractTask(priority)
{

}

void DeferredTask::run()
{
    this->status = TaskStatus::PROCESSING;
    std::this_thread::sleep_for(std::chrono::seconds(std::rand() % MAX_SLEEP));
    this->status = TaskStatus::DONE;
}

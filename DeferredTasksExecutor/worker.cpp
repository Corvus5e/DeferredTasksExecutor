
#include <worker.h>
#include <deferredtaskexecutor.h>
#include <thread>

Worker::Worker(DeferredTaskExecutor &task_executor) : dtask_executor(task_executor)
{

}

void Worker::operator ()()
{
    while(!dtask_executor.isStopped()){       
       AbstractTask* task = nullptr;

       {           
           std::unique_lock<std::mutex> lock(dtask_executor.queue_mutex);

           while(!dtask_executor.isStopped() && dtask_executor.tasks.empty()){
               dtask_executor.condition.wait(lock);
           }

           if(!dtask_executor.tasks.empty()){
               task = dtask_executor.tasks.top();
               dtask_executor.tasks.pop();
           }
       }

       if(task){
           task->run();
           dtask_executor.tasks_handler(task);
       }
    }
}

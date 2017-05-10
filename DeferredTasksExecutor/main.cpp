
#include <deferredtaskexecutor.h>
#include <deferredtask.h>

#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

struct DeferredCalculationParams{
    const size_t tasks_number;
    const size_t workers_number;

    DeferredCalculationParams(size_t tasks, size_t workers) :
        tasks_number(tasks), workers_number(workers)
    {

    }
};

int main()
{
    DeferredCalculationParams params {14, std::max(std::thread::hardware_concurrency(), 4u)};

    size_t completed_tasks(0);
    auto resultHandler = [&completed_tasks](AbstractTask* at){
        static mutex m;
        m.lock();
        cout << "Task( prioroty: " << at->getPriority() << ") completed in thread " << this_thread::get_id() << endl;
        completed_tasks++;
        m.unlock();
    };

    DeferredTaskExecutor dte(resultHandler);
    dte.start(params.workers_number);

    vector<AbstractTask*>tasks;
    for(size_t i = 0; i < params.tasks_number; i++) {
        tasks.push_back(new DeferredTask(i));
        dte.addTask(tasks.back());
    }

    cout << "Threads number :" << params.workers_number << endl;

    auto printStatus = [&dte, &tasks](){
        cout << "Queue size: " << dte.queueSize() << endl;
        for(size_t i = 0; i < tasks.size(); i++){
            cout << "Task " << i << " (priority " << tasks[i]->getPriority()<< ") " <<
                    "status " << TaskStatus::toString(tasks[i]->getStatus()) << endl;
        }
        cout << endl;
    };

    while(completed_tasks != params.tasks_number){
        printStatus();
        this_thread::sleep_for (std::chrono::milliseconds(300));
    }
    printStatus();

    dte.stop();

    cout << endl;
    cout << "Tasks completed." << endl;

    return 0;
}


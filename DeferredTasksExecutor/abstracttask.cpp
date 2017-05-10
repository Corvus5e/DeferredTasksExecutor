
#include <abstracttask.h>

#include <utility>

std::map<TaskStatus::Status, std::string> TaskStatus::enumStringMap
           {std::make_pair(TaskStatus::Status::QUEUE, "QUEUE"),
            std::make_pair(TaskStatus::Status::PROCESSING, "PROCESSING"),
            std::make_pair(TaskStatus::Status::DONE, "DONE"),
            std::make_pair(TaskStatus::Status::CANCELED, "CANCELED")
           };

const std::string& TaskStatus::toString(TaskStatus::Status s){
    auto it = enumStringMap.find(s);
    if(it == enumStringMap.end()){
        return std::string();
    }
    return it->second;
}

AbstractTask::AbstractTask(int priority) : status(TaskStatus::QUEUE), priority(priority)
{

}

TaskStatus::Status AbstractTask::getStatus()
{
    return this->status;
}

void AbstractTask::setStatus(TaskStatus::Status status)
{
    this->status = status;
}

int AbstractTask::getPriority() const
{
    return this->priority;
}

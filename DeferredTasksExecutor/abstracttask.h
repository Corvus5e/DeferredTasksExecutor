
#ifndef AbstractTask_H
#define AbstractTask_H

#include <map>

class TaskStatus {

public:
    enum Status {
        QUEUE = 1,
        PROCESSING,
        DONE,
        CANCELED
    };
    static const std::string& toString(Status s);
private:
    static std::map<TaskStatus::Status, std::string> enumStringMap;
};

class AbstractTask {
protected:
    TaskStatus::Status status;
    int priority;

public:
    AbstractTask(int priority = 1);
    TaskStatus::Status getStatus();
    int getPriority() const;
    virtual void run() = 0;

private:
    void setStatus(TaskStatus::Status status);

};

#endif // AbstractTask_H


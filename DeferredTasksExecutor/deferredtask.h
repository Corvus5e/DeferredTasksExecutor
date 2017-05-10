
#ifndef DEFERREDTASK_H
#define DEFERREDTASK_H

#include <abstracttask.h>

class DeferredTask : public AbstractTask {

private:
    static const int MAX_SLEEP = 15;

public:
    DeferredTask(int priority = 1);
    void run() override;
};

#endif // DEFERREDTASK_H


#include <queue>
#include <mutex>
#include <condition_variable>
#include "event.h"


// to be removed
#include <iostream>

std::mutex queueMutex;
std::condition_variable queueNonEmptyCondition;

class ExecutionLoop 
{
private:
    /* data */
    ExecutionLoop() {}

    ~ExecutionLoop() {}

    std::queue<Event*> eventQueue;

    Event *popEvent() {

        // acquire
        std::unique_lock<std::mutex> lck(queueMutex);

        while(eventQueue.empty()) {
            // release and sleep (automatically released by wait)
            queueNonEmptyCondition.wait(lck);
            // acquire the lock (already called by wait before it returns ^)
        }

        // pop the event
        Event *e = eventQueue.front();
        eventQueue.pop();

        // release the lock (automatic, released on lck's destruction)
        return e;
    }

public:
    ExecutionLoop(ExecutionLoop const&) = delete;

    void operator=(ExecutionLoop const&) = delete;

    static ExecutionLoop& getInstance() {
        static ExecutionLoop instance;
        return instance;
    }

    void handleEvent(Event *e) {
        std::cout << "handling some event " << e->id << std::endl;
    }

    void pushEvent(Event *e) {
        std::unique_lock<std::mutex> lck(queueMutex);
        eventQueue.push(e);
        queueNonEmptyCondition.notify_one();
    }

    void start() {
        while(true) {
            Event *curEvent = popEvent();
            handleEvent(curEvent);
        }
    }
};

#ifndef LIFE_CYCLE_EXECUTION_LOOP_H_
#define LIFE_CYCLE_EXECUTION_LOOP_H_    

#include <queue>
#include <mutex>
#include <condition_variable>
#include <memory>

#include "life-cycle-moment.h"

using std::shared_ptr;
using std::make_shared;

// to be removed
#include <iostream>

class Event;

class ExecutionLoop 
{
private:
    /* data */
    ExecutionLoop() {}

    ~ExecutionLoop() {}

    std::queue<shared_ptr<Event>> eventQueue;

    shared_ptr<Event> popEvent();

    // returns true if app exit is the event
    void handleEvent(shared_ptr<Event> e);

    void startLoop();

    void addTestKeyEvents();

    void addTestKeyEventsInThreads();

public:
    ExecutionLoop(ExecutionLoop const&) = delete;

    void operator=(ExecutionLoop const&) = delete;

    static ExecutionLoop& getInstance();

    void pushEvent(shared_ptr<Event> e);

    void pushLifeCycleEvent(LifeCycleMoment l);

    void start();
};


#endif /* LIFE_CYCLE_EXECUTION_LOOP_H_ */
#ifndef LIFE_CYCLE_EXECUTION_LOOP_H_
#define LIFE_CYCLE_EXECUTION_LOOP_H_    

#include <queue>
#include <mutex>
#include <condition_variable>
#include <memory>
#include <vector>

#include "life-cycle-moment.h"

using std::shared_ptr;
using std::weak_ptr;
using std::make_shared;
using std::vector;

// to be removed
#include <iostream>

class Event;
class EventEmitter;
class Logger;
class EventRouter;

class ExecutionLoop 
{
public:
    ExecutionLoop(ExecutionLoop const&) = delete;

    void operator=(ExecutionLoop const&) = delete;

    static ExecutionLoop& getInstance();

    void pushEvent(shared_ptr<Event> e);

    void pushLifeCycleEvent(LifeCycleMoment l);

    void addEmitter(weak_ptr<EventEmitter> ee);

    void start();

private:
    /* data */
    ExecutionLoop();

    ~ExecutionLoop() {}

    std::queue<shared_ptr<Event>> eventQueue;

    vector<std::weak_ptr<EventEmitter>> eventEmitters;

    shared_ptr<EventRouter> router;

    shared_ptr<Event> popEvent();

    // returns true if app exit is the event
    void handleEvent(shared_ptr<Event> e);

    void startLoop();

    void addTestKeyEvents();

    void addTestKeyEventsInThreads();
};


#endif /* LIFE_CYCLE_EXECUTION_LOOP_H_ */
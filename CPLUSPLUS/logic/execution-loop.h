#include <queue>
#include <mutex>
#include <condition_variable>
#include "event.h"
#include "app-exit-manager.h"


// to be removed
#include <iostream>





// ExecutionLoop
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

    // returns true if app exit is the event
    void handleEvent(Event *e) {
        EventRouter router;
        router.route(e);
    }

    void startLoop() {
        while(!AppExitManager::shouldAppExit()) {
            Event *curEvent = popEvent();
            handleEvent(curEvent);
        }
        Event *exitEvent = new LifeCycleEvent(AppWillExit);
        handleEvent(exitEvent);
    }

    void addTestKeyEvents() {
        ExecutionLoop& exe = ExecutionLoop::getInstance();
        for(char c = 'a'; c <= 'z'; c++) {
            Event* e = new KeyEvent(c);
            exe.pushEvent(e);
        }
    }

    void addTestKeyEventsInThreads() {
        std::thread t1(&ExecutionLoop::addTestKeyEvents, this);
        std::thread t2(&ExecutionLoop::addTestKeyEvents, this);

        t1.join();
        t2.join();
    }

public:
    ExecutionLoop(ExecutionLoop const&) = delete;

    void operator=(ExecutionLoop const&) = delete;

    static ExecutionLoop& getInstance() {
        static ExecutionLoop instance;
        return instance;
    }

    void pushEvent(Event *e) {
        std::unique_lock<std::mutex> lck(queueMutex);
        eventQueue.push(e);
        queueNonEmptyCondition.notify_one();
    }

    void pushLifeCycleEvent(LifeCycleMoment l) {
        LifeCycleEvent* e = new LifeCycleEvent(l);
        pushEvent(e);
    }

    void start() {
        std::thread eventExeThread(&ExecutionLoop::startLoop, this);

        pushLifeCycleEvent(AppDidStart);

        addTestKeyEventsInThreads();

        pushLifeCycleEvent(AppExit);
        
        eventExeThread.join();
    }
};

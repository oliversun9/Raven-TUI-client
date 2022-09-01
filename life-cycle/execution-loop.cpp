#include "execution-loop.h"
#include "event-router.h"   
#include "app-exit-manager.h"
#include "life-cycle-moment.h"
#include "life-cycle-event.h"
#include "key-event.h"
#include "event-emitter.h"

#include <thread>

using std::shared_ptr;
using std::make_shared;

std::mutex queueMutex;
std::condition_variable queueNonEmptyCondition;

ExecutionLoop::ExecutionLoop() {
    router = make_shared<EventRouter>();
}

shared_ptr<Event> ExecutionLoop::popEvent() {

    // acquire
    std::unique_lock<std::mutex> lck(queueMutex);

    while(eventQueue.empty()) {
        // release and sleep (automatically released by wait)
        queueNonEmptyCondition.wait(lck);
        // acquire the lock (already called by wait before it returns ^)
    }

    // pop the event
    shared_ptr<Event> e = eventQueue.front();
    eventQueue.pop();

    // release the lock (automatic, released on lck's destruction)
    return e;
}

// returns true if app exit is the event
void ExecutionLoop::handleEvent(shared_ptr<Event> e) {
    router->route(e);
}

void ExecutionLoop::startLoop() {
    while(!AppExitManager::shouldAppExit()) {
        shared_ptr<Event> curEvent = popEvent();
        handleEvent(curEvent);
    }
    shared_ptr<Event> exitEvent = make_shared<LifeCycleEvent>(AppWillExit);
    handleEvent(exitEvent);
}

void ExecutionLoop::addTestKeyEvents() {
    ExecutionLoop& exe = ExecutionLoop::getInstance();
    for(char c = 'a'; c <= 'z'; c++) {
        shared_ptr<Event>  e =  make_shared<KeyEvent>(c);
        exe.pushEvent(e);
    }
}

void ExecutionLoop::addTestKeyEventsInThreads() {
    std::thread t1(&ExecutionLoop::addTestKeyEvents, this);
    std::thread t2(&ExecutionLoop::addTestKeyEvents, this);

    t1.join();
    t2.join();
}

ExecutionLoop& ExecutionLoop::getInstance() {
    static ExecutionLoop instance;
    return instance;
}

void ExecutionLoop::pushEvent(shared_ptr<Event> e) {
    std::unique_lock<std::mutex> lck(queueMutex);
    eventQueue.push(e);
    queueNonEmptyCondition.notify_one();
}

void ExecutionLoop::pushLifeCycleEvent(LifeCycleMoment l) {
    shared_ptr<LifeCycleEvent> e = make_shared<LifeCycleEvent>(l);
    pushEvent(e);
}

void ExecutionLoop::addEmitter(weak_ptr<EventEmitter> ee) {
    eventEmitters.push_back(ee);
}

void ExecutionLoop::start() {
    std::thread eventExeThread(&ExecutionLoop::startLoop, this);

    pushLifeCycleEvent(AppDidStart);

    // addTestKeyEventsInThreads();

    vector<std::jthread> threads;

    for(auto ee : eventEmitters) {
        threads.push_back(
            std::jthread([this, ee] (std::stop_token stoken) {
                while(!stoken.stop_requested()) {
                    if(shared_ptr<EventEmitter> esp = ee.lock()) {
                        auto e = esp->emit();
                        if (e != nullptr) {
                            this->pushEvent(e);
                        }
                    }
                }
            })
        );
    }
    
    eventExeThread.join();


    for(auto &t : threads) {
        t.request_stop();
    }
}
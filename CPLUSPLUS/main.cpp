#include <iostream>
#include <thread>
#include "logic/execution-loop.h"


// to be removed
void addEvent(int base) {
    ExecutionLoop& exe = ExecutionLoop::getInstance();
    for(int i = base; i < base + 50; i++) {
        Event* e = new Event(i);
        exe.pushEvent(e);
    }
}

void startExecution() {
    ExecutionLoop& exe = ExecutionLoop::getInstance();
    exe.start();
}

int main() {
    std::thread eventExecutionThread(startExecution);

    // TODO: remove
    std::thread t1(addEvent, 100);
    std::thread t2(addEvent, 300);
    t1.join();
    t2.join();
    // remove ^

    // other stuff

    // main exe thread
    eventExecutionThread.join();
}
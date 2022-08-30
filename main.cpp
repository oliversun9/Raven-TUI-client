#include <iostream>
#include <thread>
#include "life-cycle/execution-loop.h"
#include "text-ui/key-poller.h"


int main() {

    ExecutionLoop& exe = ExecutionLoop::getInstance();

    // add event emitters
    auto kp = make_shared<KeyPoller>();
    kp->setup();
    exe.addEmitter(weak_ptr<KeyPoller>(kp));
    
    // start() doesn't return until the event loop stops
    exe.start();
}
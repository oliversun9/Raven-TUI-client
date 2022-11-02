#include <iostream>
#include <thread>
#include "life-cycle/execution-loop.h"
#include "text-ui/key-poller.h"
#include "text-ui/NcursesWrapper.h"


int main() {

    ExecutionLoop& exe = ExecutionLoop::getInstance();
    TextInterface& textInterface = NcursesWrapper::getInstance();
    textInterface.setup();

    // add event emitters
    auto kp = make_shared<KeyPoller>(textInterface);
    exe.addEmitter(weak_ptr<KeyPoller>(kp));
    
    // start() doesn't return until the event loop stops
    exe.start();
}

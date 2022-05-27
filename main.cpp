#include <iostream>
#include <thread>
#include "life-cycle/execution-loop.h"


int main() {

    ExecutionLoop& exe = ExecutionLoop::getInstance();
    // start() doesn't return until the event loop stops
    exe.start();
}
#include "../life-cycle/execution-loop.h"
#include "../life-cycle/key-event.h"
#include "key-poller.h"
#include "../life-cycle/life-cycle-moment.h"
#include "../life-cycle/life-cycle-event.h"
#include "NcursesWrapper.h"

#include <iostream>

const char QUIT_KEY = 'q';

shared_ptr<Event> KeyPoller::emit() {
    const char c = textInterface.getKeyBoardInput();
    if(c == TextInterface::NO_KEY_INPUT) {
        return nullptr;
    }
    if (c == QUIT_KEY) {
        return make_shared<LifeCycleEvent>(AppExit);
    }
    return make_shared<KeyEvent>(c);
}
#include <ncurses.h>
#include "../life-cycle/execution-loop.h"
#include "../life-cycle/key-event.h"
#include "key-poller.h"
#include "../life-cycle/life-cycle-moment.h"
#include "../life-cycle/life-cycle-event.h"

#include <iostream>

KeyPoller::KeyPoller(){
    this->isScrSetup = false;
}
KeyPoller::~KeyPoller(){
    endwin();
    std::cout << "DESTRUCTING KeyPoller" << std::endl;
}

const char QUIT_KEY = 'q';

void KeyPoller::setup() {
    initscr();
    nodelay(stdscr, true);
    isScrSetup = true;
}

shared_ptr<Event> KeyPoller::emit() {
    if (!isScrSetup) {
        setup();
    }
    const char c =  getch();
    if(c == ERR) {
        return nullptr;
    }
    if (c == QUIT_KEY) {
        return make_shared<LifeCycleEvent>(AppExit);
    }
    return make_shared<KeyEvent>(c);
}
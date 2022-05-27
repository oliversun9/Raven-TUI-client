#ifndef LIFE_CYCLE_KEY_EVENT_H
#define LIFE_CYCLE_KEY_EVENT_H

#include "event.h"

using std::enable_shared_from_this;

class KeyEvent: public Event, public enable_shared_from_this<KeyEvent> {
public:
    KeyEvent(char c): c(c) {}
    ~KeyEvent(){}

    const char c;

    void getRouted(shared_ptr<EventRouter> router);
};

#endif /* LIFE_CYCLE_KEY_EVENT_H */
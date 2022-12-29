#ifndef LIFE_CYCLE__EVENT_HANDLER
#define LIFE_CYCLE__EVENT_HANDLER

#include <memory>

using std::shared_ptr;

class Event;

class EventHandler
{
public:
    virtual void handle(shared_ptr<Event> e) = 0;
};

#endif /* LIFE_CYCLE__EVENT_HANDLER */
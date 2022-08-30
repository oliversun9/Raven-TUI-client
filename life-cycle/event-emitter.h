#ifndef LIFE_CYCLE__EVENT_EMITTER
#define LIFE_CYCLE__EVENT_EMITTER

#include <memory>

using std::shared_ptr;

class Event;

class EventEmitter
{
public:
    virtual ~EventEmitter(){}

    // must be non-blocking
    virtual shared_ptr<Event> emit() = 0;
};

#endif // LIFE_CYCLE__EVENT_EMITTER
#ifndef LIFE_CYCLE_EVENT_H_
#define LIFE_CYCLE_EVENT_H_

#include <memory>

using std::shared_ptr;

class EventRouter;

class Event
{
private:
public:
    virtual ~Event(){}

    virtual void getRouted(shared_ptr<EventRouter> router) = 0;
};

#endif /* LIFE_CYCLE_EVENT_H_ */
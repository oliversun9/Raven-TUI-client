#ifndef LIFE_CYCLE_EVENT_ROUTER_H_
#define LIFE_CYCLE_EVENT_ROUTER_H_

#include <memory>

using std::enable_shared_from_this;
using std::shared_ptr;

class Event;
class KeyEvent;
class LifeCycleEvent;
class Logger;

class EventRouter: public enable_shared_from_this<EventRouter> {
private:
    shared_ptr<Logger> logger;
public:
    EventRouter();
    ~EventRouter(){}

    void route(shared_ptr<Event> e);

    void route(shared_ptr<KeyEvent> ke);

    void route(shared_ptr<LifeCycleEvent> le);
};

#endif /* LIFE_CYCLE_EVENT_ROUTER_H_ */
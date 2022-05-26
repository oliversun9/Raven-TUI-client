#ifndef LIFE_CYCLE_EVENT_H_
#define LIFE_CYCLE_EVENT_H_

#include "app-exit-manager.h"

using std::shared_ptr;
using std::make_shared;
using std::enable_shared_from_this;

class EventRouter;
class KeyEvent;
class LifeCycleEvent;
class AppExitManager;

enum LifeCycleMoment {
    AppDidStart,
    AppWillExit,
    AppExit,
};

class Event
{
private:
    /* data */
public:
    virtual ~Event(){}

    virtual void getRouted(shared_ptr<EventRouter> router) = 0;
};

class KeyEvent: public Event, public enable_shared_from_this<KeyEvent> {
public:
    KeyEvent(char c): c(c) {}
    ~KeyEvent(){}

    const char c;

    void getRouted(shared_ptr<EventRouter> router);
};



class LifeCycleEvent: public Event, public enable_shared_from_this<LifeCycleEvent> {
public:
    LifeCycleEvent(LifeCycleMoment p): lifeCycleMoment(p) {}
    ~LifeCycleEvent(){}

    const LifeCycleMoment lifeCycleMoment;

    void getRouted(shared_ptr<EventRouter> router);
};


class EventRouter: public enable_shared_from_this<EventRouter> {
    public:
    EventRouter(){}
    ~EventRouter(){}

    void route(shared_ptr<Event> e);

    void route(shared_ptr<KeyEvent> ke);

    void route(shared_ptr<LifeCycleEvent> le);
};


void KeyEvent::getRouted(shared_ptr<EventRouter> router) {
    router->route(shared_from_this());
}

void LifeCycleEvent::getRouted(shared_ptr<EventRouter> router) {
    router->route(shared_from_this());
}

void EventRouter::route(shared_ptr<Event> e) {
    e->getRouted(shared_from_this());
}

void EventRouter::route(shared_ptr<KeyEvent> ke) {
    std::cout << "routing key event " << ke->c << std::endl;
}

void EventRouter::route(shared_ptr<LifeCycleEvent> le) {
    switch (le->lifeCycleMoment)
    {
    case AppDidStart:
        std::cout << "app did start" << std::endl;
        break;

    case AppWillExit:
        std::cout << "app will exit" << std::endl;
        break;

    case AppExit:
        // std::cout << "App Exit Request" << std::endl;
        AppExitManager::requestExit();
    
    default:
        break;
    }
}

#endif /* LIFE_CYCLE_EVENT_H_ */
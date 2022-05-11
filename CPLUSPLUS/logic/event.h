#include "app-exit-manager.h"

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

    virtual void getRouted(EventRouter *router) = 0;
};

class KeyEvent: public Event {
public:
    KeyEvent(char c): c(c) {}
    ~KeyEvent(){}

    const char c;

    void getRouted(EventRouter *router);
};



class LifeCycleEvent: public Event {
public:
    LifeCycleEvent(LifeCycleMoment p): lifeCycleMoment(p) {}
    ~LifeCycleEvent(){}

    const LifeCycleMoment lifeCycleMoment;

    void getRouted(EventRouter *router);
};


class EventRouter {
    public:
    EventRouter(){}
    ~EventRouter(){}

    void route(Event *e);

    void route(KeyEvent *ke);

    void route(LifeCycleEvent *le);
};


void KeyEvent::getRouted(EventRouter *router) {
    router->route(this);
}

void LifeCycleEvent::getRouted(EventRouter *router) {
    router->route(this);
}

void EventRouter::route(Event *e) {
    e->getRouted(this);
}

void EventRouter::route(KeyEvent *ke) {
    std::cout << "routing key event " << ke->c << std::endl;
}

void EventRouter::route(LifeCycleEvent *le) {
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

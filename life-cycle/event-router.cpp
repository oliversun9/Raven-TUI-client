#include <iostream>

#include "event-router.h"
#include "app-exit-manager.h"
#include "event.h"
#include "key-event.h"
#include "life-cycle-event.h"
#include "life-cycle-moment.h"

using std::shared_ptr;

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
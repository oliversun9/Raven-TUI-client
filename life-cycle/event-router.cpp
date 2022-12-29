#include <iostream>
#include <string>

#include "event-router.h"
#include "app-exit-manager.h"
#include "event.h"
#include "key-event.h"
#include "life-cycle-event.h"
#include "life-cycle-moment.h"
#include "../util/logger.h"
#include "../util/time-service.h"

using std::shared_ptr;
using std::make_shared;

EventRouter::EventRouter() {
    logger = make_shared<Logger>("event_log.txt");
    logger->log(TimeService::localTimeText());
    logger->log("Logger activated");
}

void EventRouter::handle(shared_ptr<Event> e) {
    e->getHandled(shared_from_this());
}

void EventRouter::route(shared_ptr<KeyEvent> ke) {
    std::string message("routing key event ");
    message.push_back(ke->c);
    logger->log(message);
}

void EventRouter::route(shared_ptr<LifeCycleEvent> le) {
    switch (le->lifeCycleMoment)
    {
    case AppDidStart:
        logger->log("app did start");
        break;

    case AppWillExit:
        logger->log("app will exit");
        break;

    case AppExit:
        logger->log("App Exit Request");
        AppExitManager::requestExit();
    
    default:
        break;
    }
}
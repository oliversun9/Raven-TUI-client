#include "key-event.h"
#include "event-router.h"

using std::shared_ptr;

void KeyEvent::getRouted(shared_ptr<EventRouter> router) {
    router->route(shared_from_this());
}
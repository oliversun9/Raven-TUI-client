#ifndef LIFE_CYCLE_LIFE_CYCLE_EVENT_H_
#define LIFE_CYCLE_LIFE_CYCLE_EVENT_H_

#include <memory>

#include "event.h"
#include "life-cycle-moment.h"

using std::enable_shared_from_this;

class LifeCycleEvent: public Event, public enable_shared_from_this<LifeCycleEvent> {
public:
    LifeCycleEvent(LifeCycleMoment p): lifeCycleMoment(p) {}
    ~LifeCycleEvent(){}

    const LifeCycleMoment lifeCycleMoment;

    void getHandled(shared_ptr<EventRouter> router);
};

#endif /* LIFE_CYCLE_LIFE_CYCLE_EVENT_H_ */
#ifndef TEXT_UI__KEY_POLLER
#define TEXT_UI__KEY_POLLER


#include "../life-cycle/event-emitter.h"
#include "../life-cycle/event-emitter.h"

class TextInterface;

using std::enable_shared_from_this;
class KeyPoller: public EventEmitter, public enable_shared_from_this<KeyPoller> {
private:
    TextInterface& textInterface;
public:
    KeyPoller(TextInterface& t): textInterface(t) {}
    ~KeyPoller(){}

    // non-blocking
    shared_ptr<Event> emit();
};

#endif // TEXT_UI__KEY_POLLER
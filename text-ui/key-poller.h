#ifndef TEXT_UI__KEY_POLLER
#define TEXT_UI__KEY_POLLER


#include "../life-cycle/event-emitter.h"
#include "../life-cycle/event-emitter.h"

using std::enable_shared_from_this;
class KeyPoller: public EventEmitter, public enable_shared_from_this<KeyPoller> {
private:
    /* data */
    bool isScrSetup;

    
public:
    KeyPoller(/* args */);
    ~KeyPoller();

    // call this plz (this will be removed, and init will be done in the main TUI thing)
    void setup();

    // non-blocking
    shared_ptr<Event> emit();
};

#endif // TEXT_UI__KEY_POLLER
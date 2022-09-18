#ifndef LIFE_CYCLE_APP_EXIT_MANAGER_H_
#define LIFE_CYCLE_APP_EXIT_MANAGER_H_

#include <mutex>

class AppExitManager {
public:
    static void requestExit();
    static bool shouldAppExit();
private:
    static bool _shouldExit;
};

#endif /* LIFE_CYCLE_APP_EXIT_MANAGER_H_ */
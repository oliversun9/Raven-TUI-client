#ifndef LIFE_CYCLE_APP_EXIT_MANAGER_H_
#define LIFE_CYCLE_APP_EXIT_MANAGER_H_

#include <mutex>


std::mutex appExitMutex;


class AppExitManager {
public:
    static void requestExit() {
        std::unique_lock<std::mutex> lck(appExitMutex);
        _shouldExit = true;
    }

    static bool shouldAppExit() {
        std::unique_lock<std::mutex> lck(appExitMutex);
        return _shouldExit;        
    }
private:
    static bool _shouldExit;
};

bool AppExitManager::_shouldExit = false;

#endif /* LIFE_CYCLE_APP_EXIT_MANAGER_H_ */
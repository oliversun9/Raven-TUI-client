#ifndef APP_EXIT_MANAGER
#define APP_EXIT_MANAGER

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

#endif
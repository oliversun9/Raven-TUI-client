#include "app-exit-manager.h"

using std::mutex;
using std::unique_lock;

mutex appExitMutex;

void AppExitManager::requestExit() {
    unique_lock<mutex> lck(appExitMutex);
    _shouldExit = true;
}

bool AppExitManager::shouldAppExit() {
    unique_lock<mutex> lck(appExitMutex);
    return _shouldExit;        
}

bool AppExitManager::_shouldExit = false;
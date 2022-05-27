#include "app-exit-manager.h"



std::mutex appExitMutex;

void AppExitManager::requestExit() {
    std::unique_lock<std::mutex> lck(appExitMutex);
    _shouldExit = true;
}

bool AppExitManager::shouldAppExit() {
    std::unique_lock<std::mutex> lck(appExitMutex);
    return _shouldExit;        
}

bool AppExitManager::_shouldExit = false;
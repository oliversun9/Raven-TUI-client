#include "time-service.h"
#include <chrono>
#include <ctime>

string TimeService::localTimeText() {
    // from https://stackoverflow.com/a/27856440/19866760

    auto sysClockTimePoint = std::chrono::system_clock::now();
    std::time_t sysClockTime = std::chrono::system_clock::to_time_t(sysClockTimePoint);

    string dateTime = "";
    dateTime += std::ctime(&sysClockTime);

    return dateTime;
}
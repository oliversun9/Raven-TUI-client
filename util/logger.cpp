#include "logger.h"
#include <iostream>
#include <fstream>

Logger::Logger(string logFileName): outputFileStream(logFileName, std::ios::app) {
    if(!outputFileStream.is_open()) {
        throw std::bad_alloc();
    }
}

Logger::~Logger() {
    outputFileStream.close();
}

void Logger::log(string message) {
    outputFileStream << message << std::endl;
}
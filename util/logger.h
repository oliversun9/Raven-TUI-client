#ifndef UTIL__LOGGER
#define UTIL__LOGGER

#include <string>
#include <fstream>
#include <memory>

using std::string;
using std::enable_shared_from_this;
using std::ofstream;

class Logger: public enable_shared_from_this<Logger>
{
private:
    ofstream outputFileStream;    
public:
    Logger(string logFileName);
    ~Logger();
    void log(string message);
};

#endif // UTIL__LOGGER
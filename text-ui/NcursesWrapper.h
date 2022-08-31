#ifndef TEXT_UI__NCURSES_WRAPPER
#define TEXT_UI__NCURSES_WRAPPER

#include "TextInterface.h"

class NcursesWrapper: public TextInterface
{
private:
    /* data */
    NcursesWrapper(/* args */);
    ~NcursesWrapper();
public:
    NcursesWrapper(NcursesWrapper const&) = delete;
    void operator=(NcursesWrapper const&) = delete;
    static NcursesWrapper& getInstance();
    
    void setup();
    int getKeyBoardInput();
    void displayBox(int y, int x, unsigned int h, unsigned int w);
    void displayText(int y, int x, std::string s);
};

#endif // TEXT_UI__NCURSES_WRAPPER
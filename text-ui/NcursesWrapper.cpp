#include "NcursesWrapper.h"
#include "curses.h"


NcursesWrapper::NcursesWrapper(/* args */) {}

NcursesWrapper::~NcursesWrapper()
{
    endwin();
}

NcursesWrapper& NcursesWrapper::getInstance() {
    static NcursesWrapper instance;
    return instance;
}

void NcursesWrapper::setup() {
    initscr();
    nodelay(stdscr, true);
}

int NcursesWrapper::getKeyBoardInput() {
    const int keyCode = getch();
    if (keyCode == ERR) {
        return TextInterface::NO_KEY_INPUT;
    }
    return keyCode;
}

void NcursesWrapper::displayBox(int y, int x, unsigned int h, unsigned int w) {}

void NcursesWrapper::displayText(int y, int x, std::string s) {}

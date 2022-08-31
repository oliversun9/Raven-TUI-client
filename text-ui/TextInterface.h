#ifndef TEXT_UI__TEXT_INTERFACE
#define TEXT_UI__TEXT_INTERFACE

#include <string>

class TextInterface
{
public:
static const int NO_KEY_INPUT = -1;
virtual void setup() = 0;
virtual int getKeyBoardInput() = 0;
virtual void displayBox(int y, int x, unsigned int h, unsigned int w) = 0;
virtual void displayText(int y, int x, std::string s) = 0;
};

#endif // TEXT_UI__TEXT_INTERFACE
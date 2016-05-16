#include "Fragment.hpp"
#include <sstream>

using namespace std;

string Fragment::toString() const
{
    stringstream ss;
    for(auto widget : mWidgets)
    {
        ss << widget->toString() << endl;
    }
    return ss.str();
}

bool Fragment::handleInput(string str, Control* control) const
{
    for (auto widget : mWidgets)
    {
        if (widget->handleInput(str, control))
        {
            return true;
        }
    }
    return false;
}

Fragment::~Fragment()
{
    for (auto widget : mWidgets)
    {
        delete widget;
    }
}

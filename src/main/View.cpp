#include "View.hpp"
#include <sstream>

using namespace std;

View::View(const Display* display, Control* control)
    : mDisplay(display), mControl(control)
{
}

string View::toString() const
{
    stringstream ss;
    for (auto fragment : mFragments)
    {
        ss << fragment->toString() << endl;
    }
    return ss.str();
}

void View::show() const
{
    mDisplay->show(*this);
    getInput();
}

View::~View()
{
    for (auto fragment : mFragments)
    {
        delete fragment;
    }
}

void View::getInput() const
{
    string input = mDisplay->getInput();
    while (!handleInput(input))
    {
        input = mDisplay->reInput();
    }
}

bool View::handleInput(string str) const
{
    for (auto fragment : mFragments)
    {
        if (fragment->handleInput(str, mControl))
        {
            return true;
        }
    }
    return false;
}

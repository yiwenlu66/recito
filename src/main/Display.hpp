#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include "View.hpp"
#include <string>

using namespace std;

class View;

class Display
{
    virtual void show(const View&) const;
    virtual string getInput() const;
};

class TextDisplay: public Display
{
    virtual void show(const View&) const;
    virtual string getInput() const;
};

#endif

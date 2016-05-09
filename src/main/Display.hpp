#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include "View.hpp"

class View;

class Display
{
    virtual void show(const View&) const;
};

class TextDisplay: public Display
{
    virtual void show(const View&) const;
};

#endif

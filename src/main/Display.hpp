#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include "View.hpp"
#include <string>

using namespace std;

class View;

class Display
{
public:
    virtual void show(const View&) const = 0;
    virtual string getInput() const = 0;
    virtual string reInput() const = 0;
    virtual ~Display() = default;
};

class TextDisplay: public Display
{
public:
    virtual void show(const View&) const;
    virtual string getInput() const;
    virtual string reInput() const;
};

#endif

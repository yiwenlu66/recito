#ifndef WIDGET_HPP
#define WIDGET_HPP

#include <string>
#include "Control.hpp"

using namespace std;

class Control;

class Widget
{
public:
    virtual bool handleInput(string input, Control* control) const; // return true if the input is handled; do nothing by default
    virtual string toString() const;
};

class Label: public Widget
{
public:
    Label(string);
    virtual string toString() const;

private:
    string mText;
};

class Input: public Widget
{
public:
    Input(string key, string hintText);
    virtual string toString() const;
    virtual bool handleInput(string input, Control* control) const;

protected:
    string mKey;
    string mHintText;
};

// subclasses of Input will be declared here

#endif

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
    virtual ~Widget() = default;
};

class Label: public Widget
{
public:
    Label(string);
    virtual string toString() const;
    virtual ~Label() = default;

private:
    string mText;
};

class TextInput: public Widget
{
public:
    TextInput(string hintText);
    virtual string toString() const;
    virtual bool handleInput(string input, Control* control) const;
    virtual ~TextInput() = default;

private:
    string mHintText;
};

class Option: public Widget
{
public:
    Option(string key, string hintText);
    virtual string toString() const;
    virtual bool handleInput(string input, Control* control) const;
    virtual ~Option() = default;

protected:
    string mKey;
    string mHintText;
};

// subclasses of Option will be declared here

#endif

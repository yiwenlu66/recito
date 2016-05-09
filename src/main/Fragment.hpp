#ifndef FRAGMENT_HPP
#define FRAGMENT_HPP

#include "Widget.hpp"
#include "Control.hpp"
#include <string>
#include <vector>

using namespace std;

class Control;
class Widget;

class Fragment
{
public:
    string toString() const;        // call Widget::toString() in sequence
    bool handleInput(string, Control) const;    // call Widget::handleInput() in sequence
    ~Fragment();                    // delete all widgets in mWidgets

protected:
    vector<Widget*> mWidgets;
};

// subclasses of Fragment will be declared here

#endif

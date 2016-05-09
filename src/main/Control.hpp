#ifndef CONTROL_HPP
#define CONTROL_HPP

#include "ViewClass.hpp"
#include "View.hpp"
#include "MainLoop.hpp"

class View;
class MainLoop;

class Control
{
public:
    Control(MainLoop*);
    const View& getView() const;
    void showView() const;      // call View::show()
    void waitForInput() const;  // read input and call View::handleInput(), finally deal with invalid input
    ~Control();

private:
    const View* mView;
    MainLoop* mMainControl;
    void setView(ViewClass);    // delete old view and construct new view using ViewFactory
};

// subclasses of Control will be declared here

#endif

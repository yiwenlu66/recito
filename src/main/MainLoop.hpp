#ifndef MAINLOOP_HPP
#define MAINLOOP_HPP

#include "Display.hpp"
#include "Control.hpp"
#include "ControlClass.hpp"

class Display;
class Control;

class MainLoop
{
public:
    MainLoop();                 // initialize mDisplay and mControl (MainMenuControl)
    void stop();                // set mRun to false
    bool isRunning() const;
    const Display* getDisplay() const;
    const Control* getControl() const;
    void setControl(ControlClass);  // delete old control and construct new control using ControlFactory
    ~MainLoop();

private:
    bool mRun = true;
    const Display* mDisplay;
    const Control* mControl;
};

#endif

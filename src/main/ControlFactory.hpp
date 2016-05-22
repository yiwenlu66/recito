#ifndef CONTROLFACTORY_HPP
#define CONTROLFACTORY_HPP

#include "MainLoop.hpp"
#include "Control.hpp"
#include "../common.hpp"

class MainLoop;
class Control;

class ControlFactory
{
public:
    ControlFactory(MainLoop*);
    Control* make(ControlClass);

private:
    MainLoop* mMainLoop;
};

#endif

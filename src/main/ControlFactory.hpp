#ifndef CONTROLFACTORY_HPP
#define CONTROLFACTORY_HPP

#include "MainLoop.hpp"
#include "ControlClass.hpp"

class ControlFactory
{
public:
    ControlFactory(MainLoop*);
    Control* make(ControlClass);

private:
    MainLoop* mMainLoop;
};

#endif

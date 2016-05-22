#ifndef VIEWFACTORY_HPP
#define VIEWFACTORY_HPP

#include "Control.hpp"
#include "../common.hpp"

class ViewFactory
{
public:
    ViewFactory(Control*, const Display*);
    const View* make(ViewClass);

private:
    Control* mControl;
    const Display* mDisplay;
};

#endif

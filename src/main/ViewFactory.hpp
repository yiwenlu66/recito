#ifndef VIEWFACTORY_HPP
#define VIEWFACTORY_HPP

#include "Control.hpp"
#include "ViewClass.hpp"

class ViewFactory
{
public:
    ViewFactory(const Control*, const Display*);
    const View* make(ViewClass);

private:
    const Control* mControl;
    const Display* mDisplay;
};

#endif

#include "Control.hpp"
#include "ViewFactory.hpp"
#include "View.hpp"

Control::Control(MainLoop* mainloop)
    : mMainLoop(mainloop)
{
}

Control::~Control()
{
    delete mView;
}

const View& Control::getView() const
{
    return *mView;
}

void Control::setView(ViewClass viewClass)
{
    delete mView;
    ViewFactory viewFactory(this, mMainLoop->getDisplay());
    mView = viewFactory.make(viewClass);
}

void Control::showView() const
{
    mView->show();
}

MemoryControl::~MemoryControl()
{
    delete mWordIterator;
}

ExamControl::~ExamControl()
{
    delete mWordIterator;
}

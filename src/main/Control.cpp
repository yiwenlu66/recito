#include "Control.hpp"
#include "ViewFactory.hpp"
#include "View.hpp"

Control::Control(MainLoop*mainloop)
{
    mainloop = this->mMainControl;
}
Control::~Control()
{
    // uncomment after View::~View() is implemented
    // delete mView;
}
const View&Control::getView()const
{
    return *mView;
}
void Control::setView(ViewClass viewclass)
{
    // uncomment after View::~View() is implemented
    // delete mView;

    // uncomment after MainControl::getDisplay() is implemented
    //ViewFactory fa(this, mMainControl->getDisplay());

    // uncomment after ViewFactory::make() is implemented
    //mView=fa.make(viewclass);

}
void Control::showView()const
{
    // uncomment after View::show() is implemented
    //mView->show();
}

MemoryControl::~MemoryControl()
{
    delete mWordIterator;
}
ExamControl::~ExamControl()
{
    delete mWordIterator;
}


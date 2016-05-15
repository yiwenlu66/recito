#include "Control.hpp"
#include"ViewFactory.hpp"
Control::Control(MainLoop*mainloop)
{
    mainloop = this->mMainControl;
}
Control::~Control()
{
    delete mView;
}
const View&Control::getView()const
{
    return *mView;
}
void Control::setView(ViewClass viewclass)
{
    delete mView;
    ViewFactory fa(this, mMainControl->getDisplay);
    mView=fa.make(viewclass);

}
void Control::showView()const
{
    mView->show();
}


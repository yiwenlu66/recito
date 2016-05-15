#include "ControlFactory.hpp"
ControlFactory::ControlFactory(MainLoop*mainloop)
{
    mMainLoop = mainloop;
}

Control* ControlFactory::make(ControlClass controlclass)
{
    Control * temp;
    switch (controlclass)
    {
    case ControlClass::MAIN_MENU:
        temp = new Main_MenuControl(mMainLoop);
        break;
    case ControlClass::MEMORY:
        temp = new MemoryControl(mMainLoop);
        break;
    case ControlClass::DICT:
        temp = new DictControl(mMainLoop);
        break;
    case ControlClass::EXAM:
        temp = new ExamControl(mMainLoop);
        break;
    case ControlClass::TEXT:
        temp = new TextControl(mMainLoop);
        break;
    case ControlClass::QUIT:
        temp = new QuitControl(mMainLoop);
        break;
    default:
        break;
    }
}



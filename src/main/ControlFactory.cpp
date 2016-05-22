#include "ControlFactory.hpp"

ControlFactory::ControlFactory(MainLoop* mainloop)
    : mMainLoop(mainloop)
{
}

Control* ControlFactory::make(ControlClass controlClass)
{
    switch (controlClass)
    {
    case ControlClass::MAIN_MENU:
        return new MainMenuControl(mMainLoop);
    case ControlClass::MEMORY:
        return new MemoryControl(mMainLoop);
    case ControlClass::DICT:
        return new DictControl(mMainLoop);
    case ControlClass::EXAM:
        return new ExamControl(mMainLoop);
    case ControlClass::TEXT:
        return new TextControl(mMainLoop);
    case ControlClass::QUIT:
        return new QuitControl(mMainLoop);
    }
}

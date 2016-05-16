#ifndef CONTROL_HPP
#define CONTROL_HPP

#include "ViewClass.hpp"
#include "View.hpp"
#include "MainLoop.hpp"
#include <string>

using namespace std;

class View;
class MainLoop;

class Control
{
public:
    Control(MainLoop*);
    const View& getView() const;
    void showView() const;      // call View::show()
    ~Control();

private:
    const View* mView;
    MainLoop* mMainControl;
    void setView(ViewClass);    // delete old view and construct new view using ViewFactory
};
//All the Handle function return true when the input can be handled;
class Main_MenuControl :public Control
{
public:
    Main_MenuControl(MainLoop *mainloop):Control(mainloop){ }
    bool HandleMode(string);

};
class MemoryControl :public Control
{
public:
    MemoryControl(MainLoop *mainloop) :Control(mainloop) { }
    bool HandleCategory(string);
    bool HandleAnswer(string);//when you answer if you know a word
    bool HandleChoose(string);
    bool HandleReturn(string);
};
class DictControl :public Control
{
public:
    DictControl(MainLoop *mainloop) :Control(mainloop) { }
    bool  HandleMode(string);
    bool  HandleWord(string);
    bool  HandleHistory(string);
    bool  HandleNext(string);
};
class ExamControl :public Control
{
public:
    ExamControl(MainLoop *mainloop) :Control(mainloop) { }
    bool HandleCategory(string);
    bool HandleSum(string);
    bool HandleWord(string);
    bool HandleReturn(string);
};
class TextControl :public Control
{
public:
    TextControl(MainLoop *mainloop) :Control(mainloop) { }
    bool HandleFilename(string);
    bool HandleSuccess(string);
    bool HandleFail(string);
};

// subclasses of Control will be declared here

#endif

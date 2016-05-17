#ifndef CONTROL_HPP
#define CONTROL_HPP

#include <string>
#include<fstream>
#include "ViewClass.hpp"
#include "View.hpp"
#include "MainLoop.hpp"
#include"../common.hpp"
#include"../algorithm/recito_algorithm.hpp"

using namespace std;

class View;
class MainLoop;

class Control
{
public:
    Control(MainLoop*);
    const View& getView() const;
    void showView() const;      // call View::show()
    virtual void backToMainMenu();
    virtual ~Control();

protected:
    const View* mView;
    void setView(ViewClass);    // delete old view and construct new view using ViewFactory
    MainLoop* mMainLoop;
};

class ChooseGroupInterface
{
public:
    virtual void chooseGroup(Group) = 0;
};

class EditExampleInterface
{
public:
    virtual void editExample() = 0;
};

class PagerInterface
{
public:
    virtual void previousPage() = 0;
    virtual void nextPage() = 0;
};

class StringHandlerInterface
{
public:
    virtual void handleString(string) = 0;
};

class MainMenuControl: public Control
{
public:
    MainMenuControl(MainLoop *mainloop): Control(mainloop) { }
    void setControlClass(ControlClass);
};

class MemoryControl: public Control, public ChooseGroupInterface, public EditExampleInterface,
    public StringHandlerInterface
{
public:
    MemoryControl(MainLoop *mainloop) : Control(mainloop) { }
    virtual void chooseGroup(Group);
    virtual void editExample();
    virtual void handleString(string);
    void addAnswer(int);    //0,1,2,3
    void showAnswer();
    virtual ~MemoryControl();

private:
    WordIterator* mWordIterator;
    string mCurrentWord;
};

class DictControl: public Control, public EditExampleInterface, public PagerInterface,
    public StringHandlerInterface
{
public:
    DictControl(MainLoop *mainloop) : Control(mainloop) { }
    virtual void editExample();
    virtual void previousPage();
    virtual void nextPage();
    virtual void handleString(string);
    void inputWord();               // redirect to DICT_INPUT view
    void showHistory();             // redirect to DICT_HISTORY view
    void goToHistoryWord(int i);    // go to the i-th word on the current page
    void goToDictMenu();

private:
    string mCurrentWord;
    vector<string> mHistoryWords;   //all history words
};

class ExamControl: public Control, public ChooseGroupInterface
{
public:
    ExamControl(MainLoop *mainloop) : Control(mainloop) { }
    virtual void chooseGroup(Group);
    void setTestNumber(int);
    void continueExam();
    virtual ~ExamControl();

private:
    WordIterator* mWordIterator;
    string mCurrentWord;
};

class TextControl: public Control, public EditExampleInterface, public PagerInterface,
    public StringHandlerInterface
{
public:
    TextControl(MainLoop *mainloop) : Control(mainloop) { }
    virtual void editExample();
    virtual void previousPage();
    virtual void nextPage();
    virtual void handleString(string);
    void reEnterFileName();

private:
    string mFileName;
    string mNowWord;
    void openFile(string);
};

#endif

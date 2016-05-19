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
enum class ControlClass;

class Control
{
    friend class ViewFactory;
public:
    Control(MainLoop*);
    Control() = default;
    const View& getView() const;
    void showView() const;      // call View::show()
    virtual void backToMainMenu()=0;
    virtual ~Control();

protected:
    const View* mView;
    ViewClass mViewtype;
    void setView(ViewClass);    // delete old view and construct new view using ViewFactory
    MainLoop* mMainLoop;
};

class ChooseGroupInterface
{
public:
    virtual void chooseGroup(Group) = 0;
};

class EditExampleInterface:protected Control
{
public:
    EditExampleInterface() = default;
    virtual void editExample() = 0;
protected:
    void overwriteExample(string);
    string mCurrentWord;
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
    MainMenuControl(MainLoop *mainloop) : Control(mainloop) { setView(ViewClass::MAIN_MENU); }
    void setControlClass(ControlClass);
    void backToMainMenu() {  }
};

class MemoryControl: public Control, public ChooseGroupInterface, public EditExampleInterface,
    public StringHandlerInterface
{
    friend class ViewFactory;
public:
    MemoryControl(MainLoop *mainloop) : Control(mainloop) { Control::setView(ViewClass::CHOOSE_CATEGORY); }
    virtual void chooseGroup(Group);
    virtual void editExample();
    virtual void handleString(string);
    virtual void backToMainMenu();
    void addAnswer(int);    //0,1,2,3
    void showAnswer();
    virtual ~MemoryControl();

private:
    WordIterator* mWordIterator;
    string mCurrentWord;
    void continueMemory();
    Group mMemoryGroup;
};

class DictControl: public Control, public EditExampleInterface, public PagerInterface,
    public StringHandlerInterface
{
    friend class ViewFactory;
public:
    DictControl(MainLoop *mainloop) : Control(mainloop) { Control::setView(ViewClass::DICT_MENU); }
    virtual void editExample();
    virtual void previousPage();
    virtual void backToMainMenu();
    virtual void nextPage();
    virtual void handleString(string);
    void inputWord();               // redirect to DICT_INPUT view
    void showHistory();             // redirect to DICT_HISTORY view
    void goToHistoryWord(int i);    // go to the i-th word on the current page
    void goToDictMenu();            //remember to commit;

private:
    string mCurrentWord;
    vector<string> mHistoryWords;   //all history words
    vector<string> mPageWords;
    int mBeginIndex;
    int mEndIndex;
    void findWord(string);
};

class ExamControl: public Control, public ChooseGroupInterface
{
    friend class ViewFactory;
public:
    ExamControl(MainLoop *mainloop) : Control(mainloop) { Control::setView(ViewClass::CHOOSE_CATEGORY); }
    virtual void chooseGroup(Group);
    virtual void backToMainMenu();
    void setTestNumber(int);
    void continueExam();
    virtual ~ExamControl();

private:
    WordIterator* mWordIterator;
    string mCurrentWord;
    vector<string> mCurrentOptions;
    Group mTestGroup;
    int Correctindex;
    int mGroupwordnumber;
    int mTestnumber;
};

class TextControl: public Control,  public PagerInterface,
    public StringHandlerInterface
{
    friend class ViewFactory;
public:
    TextControl(MainLoop *mainloop) : Control(mainloop) { Control::setView(ViewClass::TEXT_CHOOSE_FILE); }
    virtual void previousPage();
    virtual void nextPage();
    virtual void handleString(string);
    virtual void backToMainMenu();
    void reEnterFileName();

private:
    string mFileName;
    string mCurrentWord;
    int mIndex;
    string mText;
    vector<string> mUnseenWords;
    void openFile(string);
    void calText();
};


#endif

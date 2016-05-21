#ifndef CONTROL_HPP
#define CONTROL_HPP

#include <string>
#include <fstream>
#include "ViewClass.hpp"
#include "View.hpp"
#include "MainLoop.hpp"
#include "../common.hpp"
#include "../algorithm/recito_algorithm.hpp"

using namespace std;

class View;
class MainLoop;
enum class ControlClass;

class Control
{
public:
    Control(MainLoop*);
    Control() = default;
    const View& getView() const;
    void showView() const;      // call View::show()
    virtual void backToMainMenu() = 0;
    virtual ~Control();

protected:
    friend class ViewFactory;
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

class EditExampleInterface: protected Control
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
    MainMenuControl(MainLoop *mainloop) : Control(mainloop)
    {
        setView(ViewClass::MAIN_MENU);
    }
    void setControlClass(ControlClass);
    void backToMainMenu() {  }
};

class MemoryControl: public Control, public ChooseGroupInterface, public EditExampleInterface,
    public StringHandlerInterface
{
public:
    MemoryControl(MainLoop *mainloop) : Control(mainloop)
    {
        Control::setView(ViewClass::CHOOSE_CATEGORY);
    }
    virtual void chooseGroup(Group);
    virtual void editExample();
    virtual void handleString(string);
    virtual void backToMainMenu();
    void addAnswer(int);    // 0,1,2,3
    void showAnswer();
    virtual ~MemoryControl();

private:
    friend class ViewFactory;
    WordIterator* mWordIterator;
    string mCurrentWord;
    void continueMemory();
    Group mMemoryGroup;
};

class DictControl: public Control, public EditExampleInterface, public PagerInterface,
    public StringHandlerInterface
{
public:
    DictControl(MainLoop *mainloop) : Control(mainloop)
    {
        Control::setView(ViewClass::DICT_MENU);
    }
    virtual void editExample();
    virtual void previousPage();
    virtual void backToMainMenu();
    virtual void nextPage();
    virtual void handleString(string);
    void inputWord();               // redirect to DICT_INPUT view
    void showHistory();             // redirect to DICT_HISTORY view
    void goToHistoryWord(int i);    // go to the i-th word on the current page
    void goToDictMenu();            // remember to commit;

private:
    friend class ViewFactory;
    string mCurrentWord;
    vector<string> mHistoryWords;   // all history words
    vector<string> mPageWords;
    unsigned long mBeginIndex;
    unsigned long mEndIndex;
    void findWord(string);
};

class ExamControl: public Control, public ChooseGroupInterface
{
public:
    ExamControl(MainLoop *mainloop) : Control(mainloop)
    {
        Control::setView(ViewClass::CHOOSE_CATEGORY);
    }
    virtual void chooseGroup(Group);
    virtual void backToMainMenu();
    void setTestNumber(int);
    void continueExam();
    virtual ~ExamControl();

private:
    friend class ViewFactory;
    WordIterator* mWordIterator;
    string mCurrentWord;
    vector<string> mCurrentOptions;
    Group mTestGroup;
    unsigned long correctIndex;
    int mGroupWordNumber;
    int mTestNumber;
};

class TextControl: public Control,  public PagerInterface,
    public StringHandlerInterface
{
public:
    TextControl(MainLoop *mainloop) : Control(mainloop)
    {
        Control::setView(ViewClass::TEXT_CHOOSE_FILE);
    }
    virtual void previousPage();
    virtual void nextPage();
    virtual void handleString(string);
    virtual void backToMainMenu();
    void reEnterFileName();

private:
    friend class ViewFactory;
    string mFileName;
    string mCurrentWord;
    unsigned long mIndex;
    string mText;
    vector<string> mUnseenWords;
    void openFile(string);
    void calText();
};

#endif

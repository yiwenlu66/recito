#ifndef CONTROL_HPP
#define CONTROL_HPP

#include <string>
#include <fstream>
#include "View.hpp"
#include "MainLoop.hpp"
#include "../common.hpp"
#include "../algorithm/recito_algorithm.hpp"

using namespace std;

class View;
enum class ControlClass;
class WordRecord;
class MainLoop;


class Control
{
public:
    Control(MainLoop*);
    Control() = default;
    const View& getView() const;
    void showView() const;      // call View::show()
    void backToMainMenu();
    virtual ~Control();

protected:
    friend class ViewFactory;
    const View* mView = nullptr;
    ViewClass mViewClass;
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
    EditExampleInterface(MainLoop* mainLoop)
        : mMainLoop(mainLoop) {  }
    virtual void editExample() = 0;

protected:
    MainLoop* mMainLoop;
    void overwriteExample(string word, string example);
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
    MainMenuControl(MainLoop* mainLoop) : Control(mainLoop)
    {
        setView(ViewClass::MAIN_MENU);
    }
    void setControlClass(ControlClass);
};


class MemoryControl: public Control, public ChooseGroupInterface, public EditExampleInterface,
    public StringHandlerInterface
{
public:
    MemoryControl(MainLoop* mainLoop) : Control(mainLoop), EditExampleInterface(mainLoop)
    {
        Control::setView(ViewClass::CHOOSE_CATEGORY);
    }
    virtual void chooseGroup(Group);
    virtual void editExample();
    virtual void handleString(string);
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
    DictControl(MainLoop* mainLoop) : Control(mainLoop), EditExampleInterface(mainLoop)
    {
        Control::setView(ViewClass::DICT_MENU);
    }
    virtual void editExample();
    virtual void previousPage();
    virtual void nextPage();
    virtual void handleString(string);
    void inputWord();               // redirect to DICT_INPUT view
    void showHistory();             // redirect to DICT_HISTORY view
    void goToHistoryWord(int i);    // go to the i-th word on the current page
    void goToDictMenu();            // remember to commit;

private:
    friend class ViewFactory;
    string mCurrentWord;
    vector<pair<string, long long>> mHistoryWords;   // all history words
    vector<string> mPageWords;
    size_t mBeginIndex = 0;
    size_t mEndIndex = HISTORY_PER_PAGE;
    void findWord(string);
    void showHistoryPage();
};


class ExamControl: public Control, public ChooseGroupInterface
{
public:
    ExamControl(MainLoop* mainLoop) : Control(mainLoop)
    {
        Control::setView(ViewClass::CHOOSE_CATEGORY);
    }
    virtual void chooseGroup(Group);
    void setTestNumber(int);
    void continueExam();
    void checkAnswer(string);

private:
    friend class ViewFactory;
    void shuffleAllWords();
    Group mTestGroup;
    vector<WordRecord*> mAllWordsInGroup;
    vector<WordRecord*> mWordsToBeTested;
    int mTestNumber;
    size_t mCurrentIndex;
    vector<string> mOptions;
    int mCorrectAnswer;  // 0 for a, 1 for b, etc.
    int mCorrectNumber = 0;
    bool mIsCorrect;
};


class TextControl: public Control, public PagerInterface, public EditExampleInterface,
    public StringHandlerInterface
{
public:
    TextControl(MainLoop* mainLoop) : Control(mainLoop), EditExampleInterface(mainLoop)
    {
        Control::setView(ViewClass::TEXT_CHOOSE_FILE);
    }
    virtual void previousPage();
    virtual void nextPage();
    virtual void handleString(string);
    virtual void editExample();
    void reEnterFileName();

private:
    friend class ViewFactory;
    string mFileName;
    string mCurrentWord;
    size_t mIndex;
    string mText;
    vector<string> mUnseenWords;
    void openFile(string);
    void calText();
};


class QuitControl: public Control
{
public:
    QuitControl(MainLoop*);
};


#endif

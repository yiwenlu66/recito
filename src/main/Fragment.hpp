#ifndef FRAGMENT_HPP
#define FRAGMENT_HPP

#include "Widget.hpp"
#include "Control.hpp"
#include <string>
#include <vector>

using namespace std;

class Control;
class Widget;

class Fragment
{
public:
    string toString() const;                     // call Widget::toString() in sequence
    bool handleInput(string, Control*) const;    // call Widget::handleInput() in sequence
    virtual ~Fragment();                         // delete all widgets in mWidgets

protected:
    vector<Widget*> mWidgets;
};

class ChooseModeFragment: public Fragment
{
public:
    ChooseModeFragment();
};

class ChooseCategoryFragment: public Fragment
{
public:
    ChooseCategoryFragment();
};

class WordFragment: public Fragment
{
public:
    WordFragment(string);
};

class ShowAnswerFragment: public Fragment
{
public:
    ShowAnswerFragment();
};

class BackToMainMenuFragment: public Fragment
{
public:
    BackToMainMenuFragment();
};

class ExplanationFragment: public Fragment
{
public:
    ExplanationFragment(string);
};

class ExampleFragment: public Fragment
{
public:
    ExampleFragment(string);
};

class ChooseReviewAnswerFragment: public Fragment
{
public:
    ChooseReviewAnswerFragment();
};

class ReviewCompleteFragment: public Fragment
{
public:
    ReviewCompleteFragment();
};

class DictMenuFragment: public Fragment
{
public:
    DictMenuFragment();
};

class DictInputFragment: public Fragment
{
public:
    DictInputFragment();
};

class HistoryWordListFragment: public Fragment
{
public:
    HistoryWordListFragment(const vector<string>&);
};

class PagerFragment: public Fragment
{
public:
    PagerFragment(bool hasPrevious, bool hasNext);
};

class GoToDictMenuFragment: public Fragment
{
public:
    GoToDictMenuFragment();
};

class ExamChooseNumberFragment: public Fragment
{
public:
    ExamChooseNumberFragment(int maxNum);
};

class ChoicesFragment: public Fragment
{
public:
    ChoicesFragment(const vector<string>& choices);
};

class ExamAnswerFragment: public Fragment
{
public:
    ExamAnswerFragment(bool correct, string correctAnswer = "");
};

class ExamContinueFragment: public Fragment
{
public:
    ExamContinueFragment();
};

class ExamCompleteFragment: public Fragment
{
public:
    ExamCompleteFragment(double accuracy);
};

class TextFileNotFoundFragment: public Fragment
{
public:
    TextFileNotFoundFragment();
};

class TextChooseFileFragment: public Fragment
{
public:
    TextChooseFileFragment();
};

class EditFragment: public Fragment
{
public:
    EditFragment();
};

#endif

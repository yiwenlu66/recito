#ifndef VIEW_HPP
#define VIEW_HPP

#include <vector>
#include <string>
#include "Fragment.hpp"
#include "Display.hpp"
#include "Control.hpp"

using namespace std;

class Display;
class Fragment;
class Control;

class View
{
public:
    View(const Display*, Control*);
    virtual string toString() const;  // call Fragment::toString() in sequence
    void show() const;                // call Display::show() and getInput()
    virtual ~View();

protected:
    vector<Fragment*> mFragments;

private:
    const Display* mDisplay;
    Control* mControl;
    void getInput() const;            // call Display::getInput() and handleInput(), and deal with invalid input
    bool handleInput(string) const;   // call Fragment::handleInput() in sequence
};

class MainMenuView: public View
{
public:
    MainMenuView(const Display*, Control*);
};

class ChooseCategoryView: public View
{
public:
    ChooseCategoryView(const Display*, Control*);
};

class ReviewQuestionView: public View
{
public:
    ReviewQuestionView(const Display*, Control*, string word);
};

class ReviewAnswerView: public View
{
public:
    ReviewAnswerView(const Display*, Control*, string word, string explanation, string example);
};

class ReviewCompleteView: public View
{
public:
    ReviewCompleteView(const Display*, Control*);
};

class DictMenuView: public View
{
public:
    DictMenuView(const Display*, Control*);
};

class DictInputView: public View
{
public:
    DictInputView(const Display*, Control*);
};

class DictHistoryView: public View
{
public:
    DictHistoryView(const Display*, Control*, const vector<string>& words, bool hasPrevious, bool hasNext);
};

class DictHistoryEmptyView: public View
{
public:
    DictHistoryEmptyView(const Display*, Control*);
};

class DictWordView: public View
{
public:
    DictWordView(const Display*, Control*, string word, string explanation, string example);
};

class DictWordNotExistView: public View
{
public:
    DictWordNotExistView(const Display*, Control*);
};

class ExamChooseNumberView: public View
{
public:
    ExamChooseNumberView(const Display*, Control*, int maxNum);
};

class ExamQuestionView: public View
{
public:
    ExamQuestionView(const Display*, Control*, string word, const vector<string>& choices);
};

class ExamAnswerView: public View
{
public:
    ExamAnswerView(const Display*, Control*, bool correct, string correctAnswer = "");
};

class ExamCompleteView: public View
{
public:
    ExamCompleteView(const Display*, Control*, double accuracy);
};

class TextChooseFileView: public View
{
public:
    TextChooseFileView(const Display*, Control*);
};

class TextFileNotFoundView: public View
{
public:
    TextFileNotFoundView(const Display*, Control*);
};

class TextWordView: public View
{
public:
    TextWordView(const Display*, Control*, string word, string explanation, string example,
            bool hasPrevious, bool hasNext);
};

class EditView: public View
{
public:
    EditView(const Display*, Control*);
};

#endif

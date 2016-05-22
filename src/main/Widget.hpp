#ifndef WIDGET_HPP
#define WIDGET_HPP

#include <string>
#include "Control.hpp"
#include "../common.hpp"

using namespace std;

class Control;
enum class ControlClass;

class Widget
{
public:
    virtual bool handleInput(string input, Control* control) const; // return true if the input is handled; do nothing by default
    virtual string toString() const = 0;
    virtual ~Widget() = default;
};

class Label: public Widget
{
public:
    Label(string);
    virtual string toString() const;

private:
    string mText;
};

class TextInput: public Widget
{
public:
    TextInput(string hintText);
    virtual string toString() const;
    virtual bool handleInput(string input, Control* control) const;

private:
    string mHintText;
};

class MaxNumberInput: public TextInput
{
public:
    MaxNumberInput(string hintText, int maxNum);
    virtual bool handleInput(string input, Control* control) const;

private:
    int mMaxNum;
};

class Option: public Widget
{
public:
    Option(string key, string hintText);
    virtual string toString() const;
    virtual bool handleInput(string input, Control* control) const;

protected:
    string mKey;
    string mHintText;
    virtual void callControl(Control*) const = 0;
};

class ChooseModeOption: public Option
{
public:
    ChooseModeOption(string key, string hintText, ControlClass controlClass);

protected:
    virtual void callControl(Control*) const;

private:
    ControlClass mControlClass;
};

class ChooseCategoryOption: public Option
{
public:
    ChooseCategoryOption(string key, string hintText, Group group);

protected:
    virtual void callControl(Control*) const;

private:
    Group mGroup;
};

class ShowAnswerOption: public Option
{
public:
    ShowAnswerOption(string key = "a", string hintText = "show answer");

protected:
    virtual void callControl(Control*) const;
};

class BackToMainMenuOption: public Option
{
public:
    BackToMainMenuOption(string key = "m", string hintText = "back to main menu");

protected:
    virtual void callControl(Control*) const;
};

class EditExampleOption: public Option
{
public:
    EditExampleOption(string key = "e", string hintText = "edit example");

protected:
    virtual void callControl(Control*) const;
};

class ReviewAnswerOption: public Option
{
public:
    ReviewAnswerOption(int ans);
    ReviewAnswerOption(int ans, string hintText);

protected:
    virtual void callControl(Control*) const;

private:
    static string getDefaultHintText(int ans);
    int mAnswer;
};

class DictInputWordOption: public Option
{
public:
    DictInputWordOption(string key = "i", string hintText = "input a word");

protected:
    virtual void callControl(Control*) const;
};

class DictShowHistoryOption: public Option
{
public:
    DictShowHistoryOption(string key = "h", string hintText = "show history");

protected:
    virtual void callControl(Control*) const;
};

class HistoryWordOption: public Option
{
public:
    HistoryWordOption(int seq, string word);

protected:
    virtual void callControl(Control*) const;

private:
    int mSeq;
};

class PagerOption: public Option
{
public:
    PagerOption(int direction);                                 // -1 for previous page, 1 for next page
    PagerOption(int direction, string key, string hintText);

protected:
    virtual void callControl(Control*) const;

private:
    int mDirection;
    static string getDefaultKey(int direction);
    static string getDefaultHintText(int direction);
};

class GoToDictMenuOption: public Option
{
public:
    GoToDictMenuOption(string key = "n", string hintText = "look up another word");

protected:
    virtual void callControl(Control*) const;
};

class ExamChoiceOption: public Option
{
public:
    using Option::Option;

protected:
    virtual void callControl(Control*) const;
};

class ExamContinueOption: public Option
{
public:
    ExamContinueOption(string key = "c", string hintText = "continue");

protected:
    virtual void callControl(Control*) const;
};

class ReEnterFileNameOption: public Option
{
public:
    ReEnterFileNameOption(string key = "r", string hintText = "re-enter the file name");

protected:
    virtual void callControl(Control*) const;
};

#endif

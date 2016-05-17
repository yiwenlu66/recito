#include "Widget.hpp"

bool Widget::handleInput(string, Control*) const
{
    return false;
}

Label::Label(string text)
    : mText(text)
{
}

string Label::toString() const
{
    return mText;
}

TextInput::TextInput(string hintText)
    : mHintText(hintText)
{
}

string TextInput::toString() const
{
    return mHintText;
}

MaxNumberInput::MaxNumberInput(string hintText, int maxNum)
    : TextInput(hintText + " (0~" + to_string(maxNum) + ")")
{
}

Option::Option(string key, string hintText)
    : mKey(key), mHintText(hintText)
{
}

string Option::toString() const
{
    return mKey + ") " + mHintText;
}

ChooseModeOption::ChooseModeOption(string key, string hintText, ControlClass controlClass)
    : Option(key, hintText), mControlClass(controlClass)
{
}

ChooseCategoryOption::ChooseCategoryOption(string key, string hintText, Group group)
    : Option(key, hintText), mGroup(group)
{
}

ShowAnswerOption::ShowAnswerOption(string key, string hintText)
    : Option(key, hintText)
{
}

BackToMainMenuOption::BackToMainMenuOption(string key, string hintText)
    : Option(key, hintText)
{
}

EditExampleOption::EditExampleOption(string key, string hintText)
    : Option(key, hintText)
{
}

ReviewAnswerOption::ReviewAnswerOption(int ans)
    : Option(to_string(ans), getDefaultHintText(ans))
{
}

ReviewAnswerOption::ReviewAnswerOption(int ans, string hintText)
    : Option(to_string(ans), hintText)
{
}

string ReviewAnswerOption::getDefaultHintText(int ans)
{
    switch (ans)
    {
    case 0:
        return "I do not know this word.";
    case 1:
        return "I managed to recall it with some hesitation.";
    case 2:
        return "I'm quite familiar with it.";
    case 3:
        return "I'm perfectly familiar with it!";
    default:
        return "";
    }
}

DictInputWordOption::DictInputWordOption(string key, string hintText)
    : Option(key, hintText)
{
}

DictShowHistoryOption::DictShowHistoryOption(string key, string hintText)
    : Option(key, hintText)
{
}

HistoryWordOption::HistoryWordOption(int seq, string word)
    : Option(to_string(seq), word)
{
}

PagerOption::PagerOption(int direction, string key, string hintText)
    : Option(key, hintText), mDirection(direction)
{
}

PagerOption::PagerOption(int direction)
    : PagerOption(direction, getDefaultKey(direction), getDefaultHintText(direction))
{
}

string PagerOption::getDefaultKey(int direction)
{
    if (direction == -1)
    {
        return "p";
    }
    return "n";
}

string PagerOption::getDefaultHintText(int direction)
{
    if (direction == -1)
    {
        return "previous page";
    }
    return "next page";
}

GoToDictMenuOption::GoToDictMenuOption(string key, string hintText)
    : Option(key, hintText)
{
}

ExamContinueOption::ExamContinueOption(string key, string hintText)
    : Option(key, hintText)
{
}

ReEnterFileNameOption::ReEnterFileNameOption(string key, string hintText)
    : Option(key, hintText)
{
}

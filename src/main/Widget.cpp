#include "Widget.hpp"
#include <cstdlib>
#include <cerrno>
#include <stdexcept>

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

bool TextInput::handleInput(string input, Control* control) const
{
    StringHandlerInterface* ptr = dynamic_cast<StringHandlerInterface*>(control);
    if (ptr != nullptr)
    {
        ptr->handleString(input);
    }
    else
    {
        throw *(new logic_error("ERROR: Illegal call on handleString()"));
    }
    return true;
}

MaxNumberInput::MaxNumberInput(string hintText, int maxNum)
    : TextInput(hintText + " (0~" + to_string(maxNum) + ")"), mMaxNum(maxNum)
{
}

bool MaxNumberInput::handleInput(string input, Control* control) const
{
    ExamControl* examControl = dynamic_cast<ExamControl*>(control);
    if (examControl != nullptr)
    {
        int parsedInt;
        char* e;
        errno = 0;
        parsedInt = strtol(input.c_str(), &e, 10);
        if (*e != '\0' || errno != 0 || parsedInt < 0 || parsedInt > mMaxNum)
        {
            // illegal input
            return false;
        }
        examControl->setTestNumber(parsedInt);
    }
    else
    {
        throw *(new logic_error("ERROR: Illegal call on setTestNumber()"));
    }
    return true;
}

Option::Option(string key, string hintText)
    : mKey(key), mHintText(hintText)
{
}

string Option::toString() const
{
    return mKey + ") " + mHintText;
}

bool Option::handleInput(string input, Control* control) const
{
    if (input == mKey)
    {
        callControl(control);
        return true;
    }
    return false;
}

ChooseModeOption::ChooseModeOption(string key, string hintText, ControlClass controlClass)
    : Option(key, hintText), mControlClass(controlClass)
{
}

void ChooseModeOption::callControl(Control* control) const
{
    MainMenuControl* mainMenuControl = dynamic_cast<MainMenuControl*>(control);
    if (mainMenuControl != nullptr)
    {
        mainMenuControl->setControlClass(mControlClass);
    }
    else
    {
        throw *(new logic_error("ERROR: Illegal call on setControlClass()"));
    }
}

ChooseCategoryOption::ChooseCategoryOption(string key, string hintText, Group group)
    : Option(key, hintText), mGroup(group)
{
}

void ChooseCategoryOption::callControl(Control* control) const
{
    ChooseGroupInterface* ptr = dynamic_cast<ChooseGroupInterface*>(control);
    if (ptr != nullptr)
    {
        ptr->chooseGroup(mGroup);
    }
    else
    {
        throw *(new logic_error("ERROR: Illegal call on chooseGroup()"));
    }
}

ShowAnswerOption::ShowAnswerOption(string key, string hintText)
    : Option(key, hintText)
{
}

void ShowAnswerOption::callControl(Control* control) const
{
    MemoryControl* memoryControl = dynamic_cast<MemoryControl*>(control);
    if (memoryControl != nullptr)
    {
        memoryControl->showAnswer();
    }
    else
    {
        throw *(new logic_error("ERROR: Illegal call on showAnswer()"));
    }
}

BackToMainMenuOption::BackToMainMenuOption(string key, string hintText)
    : Option(key, hintText)
{
}

void BackToMainMenuOption::callControl(Control* control) const
{
    control->backToMainMenu();
}

EditExampleOption::EditExampleOption(string key, string hintText)
    : Option(key, hintText)
{
}

void EditExampleOption::callControl(Control* control) const
{
    EditExampleInterface* ptr = dynamic_cast<EditExampleInterface*>(control);
    if (ptr != nullptr)
    {
        ptr->editExample();
    }
    else
    {
        throw *(new logic_error("ERROR: Illegal call on editExample()"));
    }
}

ReviewAnswerOption::ReviewAnswerOption(int ans)
    : Option(to_string(ans), getDefaultHintText(ans)), mAnswer(ans)
{
}

ReviewAnswerOption::ReviewAnswerOption(int ans, string hintText)
    : Option(to_string(ans), hintText)
{
}

void ReviewAnswerOption::callControl(Control* control) const
{
    MemoryControl* memoryControl = dynamic_cast<MemoryControl*>(control);
    if (memoryControl != nullptr)
    {
        memoryControl->addAnswer(mAnswer);
    }
    else
    {
        throw *(new logic_error("ERROR: Illegal call on addAnswer()"));
    }
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

void DictInputWordOption::callControl(Control* control) const
{
    DictControl* dictControl = dynamic_cast<DictControl*>(control);
    if (dictControl != nullptr)
    {
        dictControl->inputWord();
    }
    else
    {
        throw *(new logic_error("ERROR: Illegal call on inputWord()"));
    }
}

DictShowHistoryOption::DictShowHistoryOption(string key, string hintText)
    : Option(key, hintText)
{
}

void DictShowHistoryOption::callControl(Control* control) const
{
    DictControl* dictControl = dynamic_cast<DictControl*>(control);
    if (dictControl != nullptr)
    {
        dictControl->showHistory();
    }
    else
    {
        throw *(new logic_error("ERROR: Illegal call on showHistory()"));
    }
}

HistoryWordOption::HistoryWordOption(int seq, string word)
    : Option(to_string(seq), word), mSeq(seq)
{
}

void HistoryWordOption::callControl(Control* control) const
{
    DictControl* dictControl = dynamic_cast<DictControl*>(control);
    if (dictControl != nullptr)
    {
        dictControl->goToHistoryWord(mSeq);
    }
    else
    {
        throw *(new logic_error("ERROR: Illegal call on goToHistoryWord()"));
    }
}

PagerOption::PagerOption(int direction, string key, string hintText)
    : Option(key, hintText), mDirection(direction)
{
}

PagerOption::PagerOption(int direction)
    : PagerOption(direction, getDefaultKey(direction), getDefaultHintText(direction))
{
}

void PagerOption::callControl(Control* control) const
{
    PagerInterface* ptr = dynamic_cast<PagerInterface*>(control);
    if (ptr != nullptr)
    {
        if (mDirection == -1)
        {
            ptr->previousPage();
        }
        else
        {
            ptr->nextPage();
        }
    }
    else
    {
        throw *(new logic_error("ERROR: Illegal call on previousPage() or nextPage()"));
    }
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

void GoToDictMenuOption::callControl(Control* control) const
{
    DictControl* dictControl = dynamic_cast<DictControl*>(control);
    if (dictControl != nullptr)
    {
        dictControl->goToDictMenu();
    }
    else
    {
        throw *(new logic_error("ERROR: Illegal call on goToDictMenu()"));
    }
}

void ExamChoiceOption::callControl(Control* control) const
{
    ExamControl* examControl = dynamic_cast<ExamControl*>(control);
    if (examControl != nullptr)
    {
        examControl->checkAnswer(mKey);
    }
    else
    {
        throw *(new logic_error("ERROR: Illegal call on checkAnswer()"));
    }
}

ExamContinueOption::ExamContinueOption(string key, string hintText)
    : Option(key, hintText)
{
}

void ExamContinueOption::callControl(Control* control) const
{
    ExamControl* examControl = dynamic_cast<ExamControl*>(control);
    if (examControl != nullptr)
    {
        examControl->continueExam();
    }
    else
    {
        throw *(new logic_error("ERROR: Illegal call on continueExam()"));
    }
}

ReEnterFileNameOption::ReEnterFileNameOption(string key, string hintText)
    : Option(key, hintText)
{
}

void ReEnterFileNameOption::callControl(Control* control) const
{
    TextControl* textControl = dynamic_cast<TextControl*>(control);
    if (textControl != nullptr)
    {
        textControl->reEnterFileName();
    }
    else
    {
        throw *(new logic_error("ERROR: Illegal call on reEnterFileName()"));
    }
}

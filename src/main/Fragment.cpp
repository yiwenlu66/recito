#include "Fragment.hpp"
#include <sstream>
#include <iomanip>

using namespace std;

string Fragment::toString() const
{
    stringstream ss;
    for(auto widget : mWidgets)
    {
        ss << widget->toString() << endl;
    }
    return ss.str();
}

bool Fragment::handleInput(string str, Control* control) const
{
    for (auto widget : mWidgets)
    {
        if (widget->handleInput(str, control))
        {
            return true;
        }
    }
    return false;
}

Fragment::~Fragment()
{
    for (auto widget : mWidgets)
    {
        delete widget;
    }
}

ChooseModeFragment::ChooseModeFragment()
{
    mWidgets.push_back(new Label("Please choose a mode:"));
    mWidgets.push_back(new ChooseModeOption("m", "memory mode", ControlClass::MEMORY));
    mWidgets.push_back(new ChooseModeOption("d", "dictionary mode", ControlClass::DICT));
    mWidgets.push_back(new ChooseModeOption("e", "exam mode", ControlClass::EXAM));
    mWidgets.push_back(new ChooseModeOption("t", "text mode", ControlClass::TEXT));
    mWidgets.push_back(new ChooseModeOption("q", "quit", ControlClass::QUIT));
}

ChooseCategoryFragment::ChooseCategoryFragment()
{
    mWidgets.push_back(new Label("Please choose a category:"));
    mWidgets.push_back(new ChooseCategoryOption("u", "unseen", Group::UNSEEN));
    mWidgets.push_back(new ChooseCategoryOption("l", "learn", Group::LEARN));
    mWidgets.push_back(new ChooseCategoryOption("y", "young", Group::YOUNG));
    mWidgets.push_back(new ChooseCategoryOption("m", "mature", Group::MATURE));
    mWidgets.push_back(new ChooseCategoryOption("r", "relearn", Group::RELEARN));
    mWidgets.push_back(new ChooseCategoryOption("s", "suspended", Group::SUSPENDED));
    mWidgets.push_back(new ChooseCategoryOption("a", "all", Group::ALL));
}

WordFragment::WordFragment(string word)
{
    mWidgets.push_back(new Label(word));
}

ShowAnswerFragment::ShowAnswerFragment()
{
    mWidgets.push_back(new ShowAnswerOption());
}

BackToMainMenuFragment::BackToMainMenuFragment()
{
    mWidgets.push_back(new BackToMainMenuOption());
}

ExplanationFragment::ExplanationFragment(string explanation)
{
    mWidgets.push_back(new Label("Explanation: " + explanation));
}

ExampleFragment::ExampleFragment(string example)
{
    mWidgets.push_back(new Label("Example: " + example));
    mWidgets.push_back(new EditExampleOption());
}

ChooseReviewAnswerFragment::ChooseReviewAnswerFragment()
{
    for (int i = 0; i < 4; ++i)
    {
        mWidgets.push_back(new ReviewAnswerOption(i));
    }
}

ReviewCompleteFragment::ReviewCompleteFragment()
{
    mWidgets.push_back(new Label("Congratulations! you have completed this mission."));
}

DictMenuFragment::DictMenuFragment()
{
    mWidgets.push_back(new DictInputWordOption());
    mWidgets.push_back(new DictShowHistoryOption());
}

DictInputFragment::DictInputFragment()
{
    mWidgets.push_back(new TextInput("Please input a word:"));
}

WordDoesNotExistFragment::WordDoesNotExistFragment()
{
    mWidgets.push_back(new Label("Word does not exist!"));
}

DictHistoryEmptyFragment::DictHistoryEmptyFragment()
{
    mWidgets.push_back(new Label("History is empty!"));
}

HistoryWordListFragment::HistoryWordListFragment(const vector<string>& entries)
{
    for (unsigned long i = 0; i < entries.size(); ++i)
    {
        mWidgets.push_back(new HistoryWordOption(i, entries[i]));
    }
}

PagerFragment::PagerFragment(bool hasPrevious, bool hasNext)
{
    if (hasPrevious)
    {
        mWidgets.push_back(new PagerOption(-1));
    }
    if (hasNext)
    {
        mWidgets.push_back(new PagerOption(1));
    }
}

GoToDictMenuFragment::GoToDictMenuFragment()
{
    mWidgets.push_back(new GoToDictMenuOption());
}

ExamChooseNumberFragment::ExamChooseNumberFragment(int maxNum)
{
    mWidgets.push_back(new MaxNumberInput("Please input the number of words you want to test yourself on: ", maxNum));
}

ChoicesFragment::ChoicesFragment(const vector<string>& choices)
{
    // up to 10 choices allowed
    for (int i = 0; i < min(static_cast<int>(choices.size()), 10); ++i)
    {
        mWidgets.push_back(new ExamChoiceOption(to_string('a' + i), choices[i]));
    }
}

ExamAnswerFragment::ExamAnswerFragment(bool correct, string correctAnswer)
{
    if (correct)
    {
        mWidgets.push_back(new Label("Correct!"));
    }
    else
    {
        mWidgets.push_back(new Label("Wrong! The answer is: " + correctAnswer + "."));
    }
}

ExamContinueFragment::ExamContinueFragment()
{
    mWidgets.push_back(new ExamContinueOption());
}

ExamCompleteFragment::ExamCompleteFragment(double accuracy)
{
    stringstream ss;
    ss << "Congratulations! You've completed the test with ";
    ss << fixed << setprecision(2) << accuracy * 100;
    ss << "\% accuracy";
    mWidgets.push_back(new Label(ss.str()));
}

TextFileNotFoundFragment::TextFileNotFoundFragment()
{
    mWidgets.push_back(new Label("Cannot open file!"));
    mWidgets.push_back(new ReEnterFileNameOption());
}

TextChooseFileFragment::TextChooseFileFragment()
{
    mWidgets.push_back(new TextInput("Please enter the file name:"));
}

EditFragment::EditFragment()
{
    mWidgets.push_back(new TextInput("Please enter the new example:"));
}

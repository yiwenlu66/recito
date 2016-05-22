#include "View.hpp"
#include <sstream>

using namespace std;

View::View(const Display* display, Control* control)
    : mDisplay(display), mControl(control)
{
}

string View::toString() const
{
    stringstream ss;
    ss << endl;
    for (auto fragment : mFragments)
    {
        ss << fragment->toString();
    }
    return ss.str();
}

void View::show() const
{
    mDisplay->show(*this);
    getInput();
}

View::~View()
{
    for (auto fragment : mFragments)
    {
        delete fragment;
    }
}

void View::getInput() const
{
    string input = mDisplay->getInput();
    while (!handleInput(input))
    {
        input = mDisplay->reInput();
    }
}

bool View::handleInput(string str) const
{
    for (auto fragment : mFragments)
    {
        if (fragment->handleInput(str, mControl))
        {
            return true;
        }
    }
    return false;
}

MainMenuView::MainMenuView(const Display* display, Control* control)
    : View(display, control)
{
    mFragments.push_back(new ChooseModeFragment());
}

ChooseCategoryView::ChooseCategoryView(const Display* display, Control* control)
    : View(display, control)
{
    mFragments.push_back(new ChooseCategoryFragment());
}

ReviewQuestionView::ReviewQuestionView(const Display* display, Control* control, string word)
    : View(display, control)
{
    mFragments.push_back(new WordFragment(word));
    mFragments.push_back(new ShowAnswerFragment());
    mFragments.push_back(new BackToMainMenuFragment());
}

ReviewAnswerView::ReviewAnswerView(const Display* display, Control* control, string word,
                                   string explanation, string example)
    : View(display, control)
{
    mFragments.push_back(new WordFragment(word));
    mFragments.push_back(new ExplanationFragment(explanation));
    mFragments.push_back(new ExampleFragment(example));
    mFragments.push_back(new ChooseReviewAnswerFragment());
    mFragments.push_back(new BackToMainMenuFragment());
}

ReviewCompleteView::ReviewCompleteView(const Display* display, Control* control)
    : View(display, control)
{
    mFragments.push_back(new ReviewCompleteFragment());
    mFragments.push_back(new BackToMainMenuFragment());
}

DictMenuView::DictMenuView(const Display* display, Control* control)
    : View(display, control)
{
    mFragments.push_back(new DictMenuFragment());
    mFragments.push_back(new BackToMainMenuFragment());
}

DictInputView::DictInputView(const Display* display, Control* control)
    : View(display, control)
{
    mFragments.push_back(new DictInputFragment());
}

DictHistoryView::DictHistoryView(const Display* display, Control* control, const vector<string>& words,
                                 bool hasPrevious, bool hasNext)
    : View(display, control)
{
    mFragments.push_back(new HistoryWordListFragment(words));
    mFragments.push_back(new PagerFragment(hasPrevious, hasNext));
    mFragments.push_back(new BackToMainMenuFragment());
}

DictWordView::DictWordView(const Display* display, Control* control, string word,
                           string explanation, string example)
    : View(display, control)
{
    mFragments.push_back(new WordFragment(word));
    mFragments.push_back(new ExplanationFragment(explanation));
    mFragments.push_back(new ExampleFragment(example));
    mFragments.push_back(new GoToDictMenuFragment());
    mFragments.push_back(new BackToMainMenuFragment());
}

DictWordNotExistView::DictWordNotExistView(const Display* display, Control* control)
    : View(display, control)
{
    mFragments.push_back(new WordDoesNotExistFragment());
    mFragments.push_back(new GoToDictMenuFragment());
    mFragments.push_back(new BackToMainMenuFragment());
}

ExamChooseNumberView::ExamChooseNumberView(const Display* display, Control* control, int maxNum)
    : View(display, control)
{
    mFragments.push_back(new ExamChooseNumberFragment(maxNum));
}

ExamQuestionView::ExamQuestionView(const Display* display, Control* control, string word, const vector<string>& choices)
    : View(display, control)
{
    mFragments.push_back(new WordFragment(word));
    mFragments.push_back(new ChoicesFragment(choices));
    mFragments.push_back(new BackToMainMenuFragment());
}

ExamAnswerView::ExamAnswerView(const Display* display, Control* control, bool correct, string correctAnswer)
    : View(display, control)
{
    mFragments.push_back(new ExamAnswerFragment(correct, correctAnswer));
    mFragments.push_back(new ExamContinueFragment());
}

ExamCompleteView::ExamCompleteView(const Display* display, Control* control, double accuracy)
    : View(display, control)
{
    mFragments.push_back(new ExamCompleteFragment(accuracy));
    mFragments.push_back(new BackToMainMenuFragment());
}

TextChooseFileView::TextChooseFileView(const Display* display, Control* control)
    : View(display, control)
{
    mFragments.push_back(new TextChooseFileFragment());
}

TextFileNotFoundView::TextFileNotFoundView(const Display* display, Control* control)
    : View(display, control)
{
    mFragments.push_back(new TextFileNotFoundFragment());
    mFragments.push_back(new BackToMainMenuFragment());
}

TextWordView::TextWordView(const Display* display, Control* control, string word,
                           string explanation, string example,
                           bool hasPrevious, bool hasNext)
    : View(display, control)
{
    mFragments.push_back(new WordFragment(word));
    mFragments.push_back(new ExplanationFragment(explanation));
    mFragments.push_back(new ExampleFragment(example));
    mFragments.push_back(new PagerFragment(hasPrevious, hasNext));
    mFragments.push_back(new BackToMainMenuFragment());
}

EditView::EditView(const Display* display, Control* control)
    : View(display, control)
{
    mFragments.push_back(new EditFragment());
}

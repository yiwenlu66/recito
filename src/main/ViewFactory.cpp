#include "ViewFactory.hpp"
#include <stdexcept>

using namespace std;

ViewFactory::ViewFactory(Control* control, const Display* display)
{
    mControl = control;
    mDisplay = display;
}

const View* ViewFactory::make(ViewClass viewClass)
{
    switch (viewClass)
    {
    case ViewClass::MAIN_MENU:
        return new MainMenuView(mDisplay, mControl);

    case ViewClass::CHOOSE_CATEGORY:
        return new ChooseCategoryView(mDisplay, mControl);

    case ViewClass::REVIEW_QUESTION:
    {
        MemoryControl* memoryControl = dynamic_cast<MemoryControl*>(mControl);
        if (memoryControl != nullptr)
        {
            return new ReviewQuestionView(mDisplay, mControl, memoryControl->mCurrentWord);
        }
        else
        {
            throw * (new logic_error("Error: Illegal casting."));
        }
    }

    case ViewClass::REVIEW_ANSWER:
    {
        MemoryControl* memoryControl = dynamic_cast<MemoryControl*>(mControl);
        if (memoryControl != nullptr)
        {
            WordRecord* wordRecord = memoryControl->Control::mMainLoop->getMainDatabase()->get(memoryControl->mCurrentWord);
            return new ReviewAnswerView(mDisplay, mControl, wordRecord->getKey(),
                                        wordRecord->getExplanation(), wordRecord->getExample());
        }
        else
        {
            throw * (new logic_error("Error: Illegal casting."));
        }
    }

    case ViewClass::REVIEW_COMPLETE:
        return new ReviewCompleteView(mDisplay, mControl);

    case ViewClass::DICT_MENU:
        return new DictMenuView(mDisplay, mControl);

    case ViewClass::DICT_INPUT:
        return new DictInputView(mDisplay, mControl);

    case ViewClass::DICT_HISTORY:
    {
        DictControl* dictControl = dynamic_cast<DictControl*>(mControl);
        if (dictControl != nullptr)
        {
            return new DictHistoryView(mDisplay, mControl, dictControl->mPageWords,
                                       dictControl->mBeginIndex > 0,
                                       dictControl->mEndIndex < dictControl->mHistoryWords.size());
        }
        else
        {
            throw * (new logic_error("Error: Illegal casting."));
        }
    }

    case ViewClass::DICT_HISTORY_EMPTY:
        return new DictHistoryEmptyView(mDisplay, mControl);

    case ViewClass::DICT_WORD:
    {
        DictControl* dictControl = dynamic_cast<DictControl*>(mControl);
        if (dictControl != nullptr)
        {
            WordRecord* wordRecord = dictControl->Control::mMainLoop->getMainDatabase()->get(dictControl->mCurrentWord);
            return new DictWordView(mDisplay, mControl, wordRecord->getKey(),
                                    wordRecord->getExplanation(), wordRecord->getExample());
        }
        else
        {
            throw * (new logic_error("Error: Illegal casting."));
        }
    }

    case ViewClass::DICT_WORD_NOT_EXIST:
        return new DictWordNotExistView(mDisplay, mControl);

    case ViewClass::EXAM_CHOOSE_NUMBER:
    {
        ExamControl* examControl = dynamic_cast<ExamControl*>(mControl);
        if (examControl != nullptr)
        {
            return new ExamChooseNumberView(mDisplay, mControl, static_cast<int>(examControl->mAllWordsInGroup.size()));
        }
        else
        {
            throw * (new logic_error("Error: Illegal casting."));
        }
    }

    case ViewClass::EXAM_QUESTION:
    {
        ExamControl* examControl = dynamic_cast<ExamControl*>(mControl);
        if (examControl != nullptr)
        {
            return new ExamQuestionView(mDisplay, mControl, examControl->mWordsToBeTested[examControl->mCurrentIndex]->getKey(),
                                        examControl->mOptions);
        }
        else
        {
            throw * (new logic_error("Error: Illegal casting."));
        }
    }

    case ViewClass::EXAM_ANSWER:
    {
        ExamControl* examControl = dynamic_cast<ExamControl*>(mControl);
        if (examControl != nullptr)
        {
            return new ExamAnswerView(mDisplay, mControl, examControl->mIsCorrect,
                                      string(1, static_cast<char>(examControl->mCorrectAnswer + 'a')));
        }
        else
        {
            throw * (new logic_error("Error: Illegal casting."));
        }
    }

    case ViewClass::EXAM_COMPLETE:
    {
        ExamControl* examControl = dynamic_cast<ExamControl*>(mControl);
        if (examControl != nullptr)
        {
            return new ExamCompleteView(mDisplay, mControl, 1.0 * examControl->mCorrectNumber / examControl->mTestNumber);
        }
        else
        {
            throw * (new logic_error("Error: Illegal casting."));
        }
    }

    case ViewClass::TEXT_CHOOSE_FILE:
        return new TextChooseFileView(mDisplay, mControl);

    case ViewClass::TEXT_FILE_NOT_FOUND:
        return new TextFileNotFoundView(mDisplay, mControl);

    case ViewClass::TEXT_NO_WORD:
        return new TextNoWordView(mDisplay, mControl);

    case ViewClass::TEXT_WORD:
    {
        TextControl* textControl = dynamic_cast<TextControl*>(mControl);
        if (textControl != nullptr)
        {
            WordRecord* wordRecord = textControl->Control::mMainLoop->getMainDatabase()->get(textControl->mCurrentWord);
            return new TextWordView(mDisplay, mControl, wordRecord->getKey(), wordRecord->getExplanation(), wordRecord->getExample(),
                                    textControl->mIndex != 0, textControl->mIndex != textControl->mUnseenWords.size() - 1);
        }
        else
        {
            throw * (new logic_error("Error: Illegal casting."));
        }
    }

    case ViewClass::EDIT:
        return new EditView(mDisplay, mControl);

    default:
        throw * (new runtime_error("Viewtype doesn't exist"));
    }
}

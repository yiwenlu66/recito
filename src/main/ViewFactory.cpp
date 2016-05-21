#include "ViewFactory.hpp"

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
        return new ReviewQuestionView(mDisplay, mControl, dynamic_cast<MemoryControl*>(mControl)->mCurrentWord);

    case ViewClass::REVIEW_ANSWER:
    {
        MemoryControl* tempControl = dynamic_cast<MemoryControl*>(mControl);
        WordRecord* tempRecord = tempControl->Control::mMainLoop->getMainDatabase()->get(tempControl->mCurrentWord);
        return new ReviewAnswerView(mDisplay, mControl, tempRecord->getKey(),
                                    tempRecord->getExplanation(), tempRecord->getExample());
    }

    case ViewClass::REVIEW_COMPLETE:
        return new ReviewCompleteView(mDisplay, mControl);

    case ViewClass::DICT_MENU:
        return new DictMenuView(mDisplay, mControl);

    case ViewClass::DICT_INPUT:
        return new DictInputView(mDisplay, mControl);

    case ViewClass::DICT_HISTORY:
    {
        DictControl* tempControl = dynamic_cast<DictControl*>(mControl);
        return new DictHistoryView(mDisplay, mControl, tempControl->mPageWords,
                                   tempControl->mBeginIndex != 0,
                                   tempControl->mEndIndex != tempControl->mHistoryWords.size() - 1);
    }

    case ViewClass::DICT_WORD:
    {
        DictControl* tempControl = dynamic_cast<DictControl*>(mControl);
        WordRecord* tempRecord = tempControl->Control::mMainLoop->getMainDatabase()->get(tempControl->mCurrentWord);
        return new DictWordView(mDisplay, mControl, tempRecord->getKey(),
                                tempRecord->getExplanation(), tempRecord->getExample());
    }

    case ViewClass::DICT_WORD_NOT_EXIST:
        return new DictWordNotExistView(mDisplay, mControl);

    case ViewClass::EXAM_CHOOSE_NUMBER:
    {
        ExamControl* tempControl = dynamic_cast<ExamControl*>(mControl);
        return new ExamChooseNumberView(mDisplay, mControl, tempControl->mGroupWordNumber);
    }

    case ViewClass::EXAM_QUESTION:
    // TODO

    case ViewClass::EXAM_ANSWER:
    // TODO

    case ViewClass::EXAM_COMPLETE:
    // TODO

    case ViewClass::TEXT_CHOOSE_FILE:
        return new TextChooseFileView(mDisplay, mControl);

    case ViewClass::TEXT_NOT_FIND_FILE:
        return new TextFileNotFoundView(mDisplay, mControl);

    case ViewClass::TEXT_WORD:
    {
        TextControl* tempControl = dynamic_cast<TextControl*>(mControl);
        WordRecord* tempRecord = tempControl->Control::mMainLoop->getMainDatabase()->get(tempControl->mCurrentWord);
        return new TextWordView(mDisplay, mControl, tempRecord->getKey(), tempRecord->getExplanation(), tempRecord->getExample(),
                                tempControl->mIndex != 0, tempControl->mIndex != tempControl->mUnseenWords.size() - 1);
    }

    case ViewClass::EDIT:
        return new EditView(mDisplay, mControl);

    default:
        throw * (new runtime_error("Viewtype doesn't exist"));
    }
}

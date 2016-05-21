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
        MemoryControl* memoryControl = dynamic_cast<MemoryControl*>(mControl);
        WordRecord* answerRecord = memoryControl->Control::mMainLoop->getMainDatabase()->get(memoryControl->mCurrentWord);
        return new ReviewAnswerView(mDisplay, mControl, answerRecord->getKey(),
                answerRecord->getExplanation(), answerRecord->getExample());

    case ViewClass::REVIEW_COMPLETE:
        return new ReviewCompleteView(mDisplay, mControl);

    case ViewClass::DICT_MENU:
        return new DictMenuView(mDisplay, mControl);

    case ViewClass::DICT_INPUT:
        return new DictInputView(mDisplay, mControl);

    case ViewClass::DICT_HISTORY:
        DictControl* dictHistoryControl = dynamic_cast<DictControl*>(mControl);
        return new DictHistoryView(mDisplay, mControl, dictHistoryControl->mPageWords,
                                   dictHistoryControl->mBeginIndex != 0,
                                   dictHistoryControl->mEndIndex != dictHistoryControl->mHistoryWords.size() - 1);

    case ViewClass::DICT_WORD:
        DictControl* dictWordControl = dynamic_cast<DictControl*>(mControl);
        WordRecord* dictWordRecord = dictWordControl->Control::mMainLoop->getMainDatabase()->get(dictWordRecord->mCurrentWord);
        return new DictWordView(mDisplay, mControl, dictWordRecord->getKey(),
                dictWordRecord->getExplanation(), dictWordRecord->getExample());

    case ViewClass::DICT_WORD_NOT_EXIST:
        return new DictWordNotExistView(mDisplay, mControl);

    case ViewClass::EXAM_CHOOSE_NUMBER:
        ExamControl* examControl = dynamic_cast<ExamControl*>(mControl);
        return new ExamChooseNumberView(mDisplay, mControl, examControl->mGroupWordNumber);

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
        TextControl* textControl = dynamic_cast<TextControl*>(mControl);
        WordRecord* textRecord = textControl->Control::mMainLoop->getMainDatabase()->get(textControl->mCurrentWord);
        return new TextWordView(mDisplay, mControl, textRecord->getKey(), textRecord->getExplanation(), textRecord->getExample(),
                                textControl->mIndex != 0, textControl->mIndex != textControl->mUnseenWords.size() - 1);

    case ViewClass::EDIT:
        return new EditView(mDisplay, mControl);

    default:
        throw * (new runtime_error("Viewtype doesn't exist"));
    }
}

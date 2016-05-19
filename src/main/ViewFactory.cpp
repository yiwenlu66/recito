#include "ViewFactory.hpp"

ViewFactory::ViewFactory(Control*control, const Display*display)
{
    mControl = control;
    mDisplay = display;
}
const View* ViewFactory::make(ViewClass viewclass)
{
    switch (viewclass)
    {
    case ViewClass::MAIN_MENU:
        return new MainMenuView(mDisplay, mControl);
        break;
    case ViewClass::CHOOSE_CATEGORY:
        return new ChooseCategoryView(mDisplay, mControl);
        break;
    case ViewClass::REVIEW_QUESTION:
        return new ReviewQuestionView(mDisplay, mControl, dynamic_cast<MemoryControl*>(mControl)->mCurrentWord);
        break;
    case ViewClass::REVIEW_ANSWER:
        MemoryControl* MtempControl = dynamic_cast<MemoryControl*>(mControl);
        WordRecord* MtempRecord = MtempControl->Control::mMainLoop->getMainDatabase()->get(MtempControl->mCurrentWord);
        return new ReviewAnswerView(mDisplay, mControl,MtempRecord->getKey(),MtempRecord->getExplanation(),MtempRecord->getExample());
        break;
    case ViewClass::REVIEW_COMPLETE:
        return new ReviewCompleteView(mDisplay, mControl);
        break;
    case ViewClass::DICT_MENU:
        return new DictMenuView(mDisplay, mControl);
        break;
    case ViewClass::DICT_INPUT:
        return new DictInputView(mDisplay, mControl);
        break;
    case ViewClass::DICT_HISTORY:
        DictControl* DtempControl = dynamic_cast<DictControl*>(mControl);
        return new DictHistoryView(mDisplay, mControl, DtempControl->mPageWords,
            DtempControl->mBeginIndex!=0,
            DtempControl->mEndIndex!=DtempControl->mHistoryWords.size()-1);
        break;
    case ViewClass::DICT_WORD:
        DictControl* DtempControl = dynamic_cast<DictControl*>(mControl);
        WordRecord* DtempRecord = DtempControl->Control::mMainLoop->getMainDatabase()->get(DtempControl->mCurrentWord);
        return new DictWordView(mDisplay, mControl, DtempRecord->getKey(), DtempRecord->getExplanation(), DtempRecord->getExample());
        break;
    case ViewClass::DICT_WORD_NOT_EXIST:
        return new DictWordNotExistView(mDisplay, mControl);
        break;
    case ViewClass::EXAM_CHOOSE_NUMBER:
        ExamControl *EtempControl = dynamic_cast<ExamControl*>(mControl);
        return new ExamChooseNumberView(mDisplay, mControl,EtempControl->mGroupwordnumber);
        break;
    case ViewClass::EXAM_QUESTION:
        break;
    case ViewClass::EXAM_ANSWER:
        break;
    case ViewClass::EXAM_COMPLETE:
        break;
    case ViewClass::TEXT_CHOOSE_FILE:
        return new TextChooseFileView(mDisplay, mControl);
        break;
    case ViewClass::TEXT_NOT_FIND_FILE:
        return new TextFileNotFoundView(mDisplay, mControl);
        break;
    case ViewClass::TEXT_WORD:
        TextControl* TtempControl = dynamic_cast<TextControl*>(mControl);
        WordRecord* TtempRecord = TtempControl->Control::mMainLoop->getMainDatabase()->get(TtempControl->mCurrentWord);
        return new TextWordView(mDisplay, mControl, TtempRecord->getKey(), TtempRecord->getExplanation(), TtempRecord->getExample(),
            TtempControl->mIndex!=0,TtempControl->mIndex!=TtempControl->mUnseenWords.size()-1);
        break;
    case ViewClass::EDIT:
        return new EditView(mDisplay, mControl);
        break;
    default:
        throw(runtime_error((" Viewtype doesn't exist")));
        break;
    }
}

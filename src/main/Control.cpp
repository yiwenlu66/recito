#include "Control.hpp"
#include "ViewFactory.hpp"
#include "View.hpp"
#include "Database.hpp"
#include "../algorithm/recito_algorithm.hpp"
#include <algorithm>
#include <random>
#include <chrono>
#include <cstdlib>
#include <ctime>

typedef Database<string, WordRecord>* DB;

// start of EditExampleInterface

void EditExampleInterface::overwriteExample(string word, string example)
{
    auto mainDatabase = mMainLoop->getMainDatabase();
    auto record = mainDatabase->get(word);
    record->setExample(example);
    mainDatabase->update(record->getKey());
}

// end of EditExampleInterface

// start of Control

Control::Control(MainLoop* mainloop)
    : mMainLoop(mainloop)
{
}

const View& Control::getView() const
{
    return *mView;
}

void Control::setView(ViewClass viewClass)
{
    delete mView;
    ViewFactory viewFactory(this, mMainLoop->getDisplay());
    mView = viewFactory.make(viewClass);
    mViewClass = viewClass;
}

void Control::showView() const
{
    mView->show();
}

void Control::backToMainMenu()
{
    Control::mMainLoop->setControl(ControlClass::MAIN_MENU);
}

Control::~Control()
{
    if (mView != nullptr)
    {
        delete mView;
    }
}

// end of Control

// start of MainMenuControl

void MainMenuControl::setControlClass(ControlClass controlclass)
{
    mMainLoop->setControl(controlclass);
}

// end of MainMenuControl

// start of MemoryControl

void MemoryControl::chooseGroup(Group group)
{
    DB mainDatabase;
    mainDatabase = Control::mMainLoop->getMainDatabase();
    vector<WordWithEFI*> elements;
    mMemoryGroup = group;
    int numWord = 0;
    for (auto i : mainDatabase->getKeyRecordMap())
    {

        if (i.second->getGroup() != group && i.second->getGroup() != Group::ALL)
        {
            continue;
        }
        else
        {
            ++numWord;
            if (numWord > MAX_MEMORY_WORD)
            {
                break;
            }
            else
            {
                WordWithEFI *temp = new WordWithEFI(i.second->getKey(),
                                                    (i.second->getAlgorithmOutput())[0], (i.second->getAlgorithmOutput())[1]);
                elements.push_back(temp);
            }
        }
    }
    mWordIterator = new WordIterator(elements);
    continueMemory();
}

void MemoryControl::editExample()
{
    Control::setView(ViewClass::EDIT);
}

void MemoryControl::handleString(string string)
{
    overwriteExample(mCurrentWord, string);
    setView(ViewClass::REVIEW_ANSWER);
}

void MemoryControl::addAnswer(int answer)
{
    DB mainDatabase;
    mainDatabase = Control::mMainLoop->getMainDatabase();
    WordRecord* record = mainDatabase->get(mCurrentWord);
    record->addAnswer(answer);

    // update algorithm output
    double EF = record->getAlgorithmOutput()[0];
    double I = record->getAlgorithmOutput()[1];
    int q = (answer == 0) ? answer : answer + 2;
    record->setAlgorithmOutput(interval(EF, q, I));

    // regroup
    EF = record->getAlgorithmOutput()[0];
    I = record->getAlgorithmOutput()[1];
    record->setGroup(group(record->getGroup(), record->getAnswers(), EF, I));

    // if answer is 0, review again
    if (answer == 0)
    {
        mWordIterator->add(new WordWithEFI(record->getKey(), EF, I));
    }

    mainDatabase->update(mCurrentWord);
    continueMemory();
}

void MemoryControl::backToMainMenu()
{
    Control::mMainLoop->getMainDatabase()->commit();
    Control::mMainLoop->setControl(ControlClass::MAIN_MENU);
}

void MemoryControl::showAnswer()
{
    Control::setView(ViewClass::REVIEW_ANSWER);
}

void MemoryControl::continueMemory()
{
    mCurrentWord = mWordIterator->next();
    if (mCurrentWord != "")
    {
        Control::setView(ViewClass::REVIEW_QUESTION);
    }
    else
    {
        Control::setView(ViewClass::REVIEW_COMPLETE);
    }
}

MemoryControl::~MemoryControl()
{
    delete mWordIterator;
}

// end of MemoryControl

// start of DictControl

void DictControl::editExample()
{
    Control::setView(ViewClass::EDIT);
}

void DictControl::findWord(string word)
{
    if (Control::mMainLoop->getMainDatabase()->get(word))
    {
        mCurrentWord = word;
        Control::setView(ViewClass::DICT_WORD);
        Control::mMainLoop->getHistoryDatabase()->add(word, new HistoryRecord(word, true));
    }
    else
    {
        Control::setView(ViewClass::DICT_WORD_NOT_EXIST);
    }
}

void DictControl::goToDictMenu()
{
    Control::mMainLoop->getMainDatabase()->commit();
    Control::mMainLoop->getHistoryDatabase()->commit();
    Control::setView(ViewClass::DICT_MENU);
}

void DictControl::goToHistoryWord(int i)
{
    auto historyDatabase = Control::mMainLoop->getHistoryDatabase();
    mCurrentWord = mPageWords[i];
    auto historyRecord = historyDatabase->get(mCurrentWord);
    historyRecord->setTimeStamp(getCurrentTimeStamp());
    historyDatabase->update(historyRecord->getKey());
    Control::setView(ViewClass::DICT_WORD);
}

void DictControl::handleString(string input)
{
    if (Control::mViewClass == ViewClass::EDIT)
    {
        overwriteExample(mCurrentWord, input);
        setView(ViewClass::DICT_WORD);
    }
    else if (Control::mViewClass == ViewClass::DICT_INPUT)
    {
        findWord(input);
    }
}

void DictControl::inputWord()
{
    Control::setView(ViewClass::DICT_INPUT);
}

void DictControl::showHistory()
{
    mHistoryWords.clear();
    auto historyDatabase = Control::mMainLoop->getHistoryDatabase();
    typedef pair<string, long long> PairType;
    for (auto keyRecord : historyDatabase->getKeyRecordMap())
    {
        mHistoryWords.push_back(PairType(keyRecord.first, keyRecord.second->getTimeStamp()));
    }
    sort(mHistoryWords.begin(), mHistoryWords.end(), [](PairType p1, PairType p2)
    {
        return p1.second > p2.second;
    });
    if (mHistoryWords.empty())
    {
        setView(ViewClass::DICT_HISTORY_EMPTY);
    }
    else
    {
        showHistoryPage();
    }
}

void DictControl::showHistoryPage()
{
    mPageWords.clear();
    for (unsigned long i = mBeginIndex; i < min(mEndIndex, mHistoryWords.size()); i++)
    {
        mPageWords.push_back(mHistoryWords[i].first);
    }
    Control::setView(ViewClass::DICT_HISTORY);
}

void DictControl::previousPage()
{
    mBeginIndex -= HISTORY_PER_PAGE;
    mEndIndex -= HISTORY_PER_PAGE;
    showHistory();
}

void DictControl::nextPage()
{
    mBeginIndex += HISTORY_PER_PAGE;
    mEndIndex += HISTORY_PER_PAGE;
    showHistory();
}

void DictControl::backToMainMenu()
{
    Control::mMainLoop->getHistoryDatabase()->commit();
    Control::mMainLoop->getMainDatabase()->commit();
    Control::mMainLoop->setControl(ControlClass::MAIN_MENU);
}

// end of DictControl

// start of ExamControl

void ExamControl::chooseGroup(Group group)
{
    mTestGroup = group;
    const DB mainDatabase = Control::mMainLoop->getMainDatabase();
    for (auto item : mainDatabase->getKeyRecordMap())
    {
        if (group == Group::ALL || item.second->getGroup() == group)
        {
            mAllWordsInGroup.push_back(item.second);
        }
    }
    mOptions.resize(min(mAllWordsInGroup.size(), static_cast<unsigned long>(EXAM_NUM_OPTIONS)));
    setView(ViewClass::EXAM_CHOOSE_NUMBER);
}

void ExamControl::backToMainMenu()
{
    Control::mMainLoop->setControl(ControlClass::MAIN_MENU);
}

void ExamControl::checkAnswer(string ans)
{
    mIsCorrect = (string(1, static_cast<char>('a' + mCorrectAnswer)) == ans);
    if (mIsCorrect)
    {
        ++mCorrectNumber;
    }
    ++mCurrentIndex;
    setView(ViewClass::EXAM_ANSWER);
}

void ExamControl::continueExam()
{
    if (mCurrentIndex < static_cast<unsigned long>(mTestNumber))
    {
        shuffleAllWords();
        mCorrectAnswer = -1;
        for (int i = 0; i < static_cast<int>(mOptions.size()); ++i)
        {
            mOptions[i] = mAllWordsInGroup[i]->getExplanation();
            if (mAllWordsInGroup[i]->getKey() == mWordsToBeTested[mCurrentIndex]->getKey())
            {
                mCorrectAnswer = i;
            }
        }
        if (mCorrectAnswer == -1)
        {
            srand(time(NULL));
            mCorrectAnswer = rand() % mOptions.size();
            mOptions[mCorrectAnswer] = mWordsToBeTested[mCurrentIndex]->getExplanation();
        }
        setView(ViewClass::EXAM_QUESTION);
    }
    else
    {
        setView(ViewClass::EXAM_COMPLETE);
    }
}

void ExamControl::setTestNumber(int testNumber)
{
    shuffleAllWords();
    mWordsToBeTested.resize(testNumber);
    copy(mAllWordsInGroup.begin(), mAllWordsInGroup.begin() + testNumber, mWordsToBeTested.begin());
    mTestNumber = testNumber;
    mCurrentIndex = 0;
    continueExam();
}

void ExamControl::shuffleAllWords()
{
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(mAllWordsInGroup.begin(), mAllWordsInGroup.end(), default_random_engine(seed));
}

// end of ExamControl

// start of TextControl

void TextControl::handleString(string input)
{
    openFile(input);
}

void TextControl::openFile(string filename)
{
    ifstream fin(filename);
    if (fin.is_open())
    {
        mFileName = filename;
        mText.assign(istreambuf_iterator<char>(fin), istreambuf_iterator<char>());
        fin.close();
        calText();
        mCurrentWord = mUnseenWords[0];
        mIndex = 0;
        setView(ViewClass::TEXT_WORD);
    }
    else
    {
        setView(ViewClass::TEXT_NOT_FIND_FILE);
    }
}

void TextControl::reEnterFileName()
{
    Control::setView(ViewClass::TEXT_CHOOSE_FILE);
}

void TextControl::calText()
{
    vector<string> words(splitWord(mText));
    for (unsigned long i = 0; i < words.size(); i++)
    {
        WordRecord* temp(mMainLoop->getMainDatabase()->get(words[i]));
        if (temp)
        {
            if (temp->getGroup() == Group::UNSEEN)
            {
                bool exist = false;
                for (unsigned long j = 0; j < mUnseenWords.size(); j++)
                {
                    if (mUnseenWords[j] == temp->getKey())
                    {
                        exist = true;
                        break;
                    }
                }
                if (!exist)
                {
                    mUnseenWords.push_back(temp->getKey());
                }
            }
        }
    }
}

void TextControl::nextPage()
{
    mCurrentWord = mUnseenWords[++mIndex];
    setView(ViewClass::TEXT_WORD);
}

void TextControl::previousPage()
{
    mCurrentWord = mUnseenWords[--mIndex];
    setView(ViewClass::TEXT_WORD);
}

// end of TextControl

// start of QuitControl

QuitControl::QuitControl(MainLoop* mainLoop)
{
    mainLoop->stop();
}

// end of QuitControl

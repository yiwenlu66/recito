#include "Control.hpp"
#include "ViewFactory.hpp"
#include "View.hpp"
#include"Database.hpp"
#include"../algorithm/recito_algorithm.hpp"

Control::Control(MainLoop* mainloop)
    : mMainLoop(mainloop)
{
}

Control::~Control()
{
    delete mView;
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
    mViewtype = viewClass;  
}

void Control::showView() const
{
    mView->show();
}

MemoryControl::~MemoryControl()
{
    delete mWordIterator;
}

ExamControl::~ExamControl()
{
    delete mWordIterator;
}




void EditExampleInterface::overwriteExample(string example)
{
    Database<string, WordRecord>*maindatabase;
    maindatabase = mMainLoop->getMainDatabase();
    (maindatabase->get(mCurrentWord))->setExample(example);
}



void MainMenuControl::setControlClass(ControlClass controlclass)
{
    mMainLoop->setControl(controlclass);
}
//mainMenu done




void MemoryControl::chooseGroup(Group group)
{
    Database<string, WordRecord>*maindatabase;
    maindatabase = Control::mMainLoop->getMainDatabase();
    vector<WordWithEFI*>elements;
    mMemoryGroup = group;
    int wordnumber = 0;
    for (auto i: maindatabase->getKeyRecordMap())
    {
        
        if (i.second->getGroup() != group)
        {
            continue;
        }
        else
        {
            wordnumber++;
            if (wordnumber > MaxMemoryWordNumber)
            {
                break;
            }
            else
            {
                WordWithEFI *temp = new  WordWithEFI(i.second->getKey(), (i.second->getAlgorithmOutput())[0], (i.second->getAlgorithmOutput())[1]);
                elements.push_back(temp);
            }
        }
        
    }
    mWordIterator = new WordIterator(elements);
}

void MemoryControl::editExample()
{
    Control::setView(ViewClass::EDIT);
}

void MemoryControl::handleString(string string)
{
    overwriteExample(string);
}

void MemoryControl::addAnswer(int answer)
{
    Database<string, WordRecord>*maindatabase;
    maindatabase = Control::mMainLoop->getMainDatabase();
    maindatabase->get(mCurrentWord)->addAnswer(answer);
    maindatabase->update(mCurrentWord);
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
    if (mCurrentWord!="")
    {
        Control::setView(ViewClass::REVIEW_QUESTION);
    }
    else
    {
        Control::setView(ViewClass::REVIEW_COMPLETE);
    }
}
//Meomory done;


void DictControl::editExample()
{
    Control::setView(ViewClass::EDIT);
}

void DictControl::findWord(string word)
{
    if (Control::mMainLoop->getMainDatabase()->get(word))
    {
        Control::setView(ViewClass::DICT_WORD);
        mCurrentWord = word;
        Control::mMainLoop->getHistoryDatabase()->add(word, &HistoryRecord(word));

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
    mCurrentWord = mPageWords[i];
    Control::setView(ViewClass::DICT_WORD);
}

void DictControl::handleString(string input)
{
    if (Control::mViewtype == ViewClass::EDIT)
    {
        overwriteExample(input);
    }
    else if (Control::mViewtype==ViewClass::DICT_INPUT)
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
    Control::setView(ViewClass::DICT_HISTORY);
}

void DictControl::previousPage()
{
    mBeginIndex -= MaxPageWordNumber;
    mEndIndex -= MaxPageWordNumber;
    mPageWords.clear();
    for (int i = mBeginIndex; i <= mEndIndex; i++)
    {
        mPageWords.push_back(mHistoryWords[i]);
    }
    Control::setView(ViewClass::DICT_HISTORY);
}

void DictControl::nextPage()
{
    mBeginIndex += MaxPageWordNumber;
    mEndIndex = ((mEndIndex + MaxPageWordNumber) < mHistoryWords.size()) ? (mEndIndex + MaxPageWordNumber) : (mHistoryWords.size() - 1);
    mPageWords.clear();
    for (int i = mBeginIndex; i <= mEndIndex; i++)
    {
        mPageWords.push_back(mHistoryWords[i]);
    }
    Control::setView(ViewClass::DICT_HISTORY);

}

void DictControl::backToMainMenu()
{
    Control::mMainLoop->getHistoryDatabase()->commit();
    Control::mMainLoop->getMainDatabase()->commit();
    Control::mMainLoop->setControl(ControlClass::MAIN_MENU);
}
//Dict done






void ExamControl::chooseGroup(Group group)
{
    mTestGroup = group;
    Database<string, WordRecord>*maindatabase;
    maindatabase = Control::mMainLoop->getMainDatabase();
    vector<WordWithEFI*>elements;
    mTestGroup = group;
    mGroupwordnumber = 0;
    for (auto i : maindatabase->getKeyRecordMap())
    {

        if (i.second->getGroup() != group)
        {
            continue;
        }
        else
        {
            mGroupwordnumber++;
        }

    }
    
}

void ExamControl::backToMainMenu()
{
    Control::mMainLoop->setControl(ControlClass::MAIN_MENU);
}

void ExamControl::continueExam()
{
    //
}

void ExamControl::setTestNumber(int testnumber)
{
    mTestnumber = testnumber;
}


//TODO






void TextControl::backToMainMenu()
{
    Control::mMainLoop->setControl(ControlClass::MAIN_MENU);
}

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
    vector<string> words(splitword(mText));
    for (int i = 0; i < words.size; i++)
    {
        WordRecord* temp(mMainLoop->getMainDatabase()->get(words[i]));
        if (temp)
        {
            if (temp->getGroup() == Group::UNSEEN)
            {
                bool exist = false;
                for (int j = 0; j< mUnseenWords.size; j++)
                {
                    if (mUnseenWords[j]== temp->getKey())
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
//Text done;





#ifndef CONTROL_HPP
#define CONTROL_HPP

#include "ViewClass.hpp"
#include "View.hpp"
#include "MainLoop.hpp"
#include <string>


#include"../common.hpp"
#include"../algorithm/recito_algorithm.hpp"
#include<fstream>
using namespace std;

class View;
class MainLoop;

class Control
{
public:
    Control(MainLoop*);
    const View& getView() const;
    void showView() const;      // call View::show()
    void changeControl(ControlClass);
    void setView(ViewClass);    // delete old view and construct new view using ViewFactory
    virtual void handleString(string) = 0;
    ~Control();

protected:
    const View* mView;
    MainLoop* mMainControl;
    
};
//All the Handle function return true when the input can be handled;
class Main_MenuControl :public Control
{
public:
    Main_MenuControl(MainLoop *mainloop):Control(mainloop){ }



};
class MemoryControl :public Control
{
public:
    MemoryControl(MainLoop *mainloop) :Control(mainloop) { }
    void chooseGroup(Group);
    void iterateWord();
    void dealwithReply(int);//0,1,2,3
    void handleString(string);
private:
    WordIterator* mWordIterator;
    string mNowword;
    void editWord(string);

};
class DictControl :public Control
{
public:
    DictControl(MainLoop *mainloop) :Control(mainloop) { }
    void handleString(string);
    void loadHistory();
    void showNextHistory();
    void showPreviousHistory();
private:
    string mNowword;
    vector<string> mHistorywords;//all history words;
    void editWord(string);
    void findWord(string);

};
class ExamControl :public Control
{
public:
    ExamControl(MainLoop *mainloop) :Control(mainloop) { }
    void chooseGroup(Group);
    void setTestNumber(int);
    void iteratorTestWord();
private:
    WordIterator* mWordIterator;
    string mNowword;
   
};
class TextControl :public Control
{
public:
    TextControl(MainLoop *mainloop) :Control(mainloop) { }
    void handleString(string);
    void giveWord();
private:
    string mFilestring;
    string mNowword;
    void openFile(string);
};

// subclasses of Control will be declared here

#endif

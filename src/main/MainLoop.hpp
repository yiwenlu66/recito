#ifndef MAINLOOP_HPP
#define MAINLOOP_HPP

#include "Display.hpp"
#include "Control.hpp"
#include "../common.hpp"
#include "Database.hpp"
#include "Record.hpp"
#include "ControlFactory.hpp"

class Display;
class Control;
class ControlFactory;

typedef Database<string, WordRecord>* WordDB;
typedef Database<string, HistoryRecord>* HistoryDB;

class MainLoop
{
public:
    MainLoop(string mainDatabaseFileName, string historyDatabaseFileName);   // initialize mDisplay and mControl (MainMenuControl); load databases
    void run();
    void stop();                                                             // set mRun to false
    bool isRunning() const;
    const Display* getDisplay() const;
    const Control* getControl() const;
    void setControl(ControlClass);                                           // delete old control and construct new control using ControlFactory
    WordDB getMainDatabase();
    HistoryDB getHistoryDatabase();
    ~MainLoop();

private:
    bool mRun = true;
    const Display* mDisplay;
    const Control* mControl;
    WordDB mMainDatabase;
    HistoryDB mHistoryDatabase;
    ControlFactory* mControlFactory;
};

#endif

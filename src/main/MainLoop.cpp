#include "MainLoop.hpp"
#include "Display.hpp"
#include <iostream>

using namespace std;


MainLoop::MainLoop(string mainDatabaseFileName, string historyDatabaseFileName)
    : mDisplay(new TextDisplay()), mControl(new MainMenuControl(this)), mControlFactory(new ControlFactory(this))
{
    mMainDatabase = new TextDatabase<string, WordRecord>();
    try
    {
        mMainDatabase->load(mainDatabaseFileName);
    }
    catch (runtime_error e)
    {
        cout << e.what() << endl;
        mRun = false;
    }

    mHistoryDatabase = new TextDatabase<string, HistoryRecord>();
    try
    {
        mHistoryDatabase->load(historyDatabaseFileName);
    }
    catch (runtime_error e)
    {
        cout << e.what() << endl;
        mRun = false;
    }
}

void MainLoop::run()
{
    while (mRun)
    {
        mControl->showView();
    }
}

void MainLoop::stop()
{
    mRun = false;
}

bool MainLoop::isRunning() const
{
    return mRun;
}

const Display* MainLoop::getDisplay() const
{
    return mDisplay;
}

const Control* MainLoop::getControl() const
{
    return mControl;
}

void MainLoop::setControl(ControlClass controlClass)
{
    delete mControl;
    mControl = mControlFactory->make(controlClass);
}

WordDB MainLoop::getMainDatabase()
{
    return mMainDatabase;
}

HistoryDB MainLoop::getHistoryDatabase()
{
    return mHistoryDatabase;
}

MainLoop::~MainLoop()
{
    delete mDisplay;
    delete mControl;
    delete mMainDatabase;
    delete mHistoryDatabase;
    delete mControlFactory;
}

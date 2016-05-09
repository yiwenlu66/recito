#ifndef VIEW_HPP
#define VIEW_HPP

#include <vector>
#include <string>
#include "Fragment.hpp"
#include "Display.hpp"
#include "Control.hpp"

using namespace std;

class Display;
class Fragment;
class Control;

class View
{
public:
    View(const Display*, Control*);
    virtual string toString() const;  // call Fragment::toString() in sequence
    bool handleInput(string) const;   // call Fragment::handleInput() in sequence
    void show() const;                // call Display::show()
    ~View();

protected:
    vector<Fragment*> mFragments;

private:
    const Display* mDisplay;
    Control* mControl;
};

// subclasses of View will be declared here

#endif

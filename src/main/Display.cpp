#include "Display.hpp"
#include <string>
#include <iostream>

using namespace std;

string TextDisplay::getInput() const
{
    string str;
    getline(cin, str);
    return str;
}

string TextDisplay::reInput() const
{
    cout << "Invalid input. Please re-enter:" << endl;
    return getInput();
}

void TextDisplay::show(const View& view) const
{
    cout << view.toString() << endl;
}

#include "Widget.hpp"

bool Widget::handleInput(string, Control*) const
{
    return false;
}

Label::Label(string text)
    : mText(text)
{
}

string Label::toString() const
{
    return mText;
}

TextInput::TextInput(string hintText)
    : mHintText(hintText)
{
}

string TextInput::toString() const
{
    return mHintText;
}

Option::Option(string key, string hintText)
    : mKey(key), mHintText(hintText)
{
}

string Option::toString() const
{
    return mKey + ") " + mHintText;
}

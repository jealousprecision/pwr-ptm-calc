#pragma once

class Button
{
public:
    bool wasPressed();
    void signalOn();
    void signalOff();

protected:
    bool isOn_ = false;
    bool wasPressed_ = false;
};

enum class ButtonCodes
{
    None = 999,
    b0 = 0,
    b1 = 1,
    b2 = 2,
    b3 = 3,
    b4 = 4,
    b5 = 5,
    b6 = 6,
    b7 = 7,
    b8 = 8,
    b9 = 9,
    plus = 10,
    minus = 11,
    multiply = 12,
    divide = 13,
    equal = 14,
    clear = 15
};

class InputState
{
public:
    void update();
    ButtonCodes getPressedButton();

protected:
    Button buttons_[16];
};

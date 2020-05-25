#ifndef INPUTSTATE_H
#define INPUTSTATE_H

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

/*
typedef struct
{
    Button numberButtons[10];
    Button plus;
    Button minus;
    Button multiply;
    Button divide;
    Button equal;
    Button clear;
} InputState;
*/

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

void inputState_init(InputState* inputState);
void inputState_update(InputState* inputState);
ButtonCodes inputState_getPressedButton(InputState* inputState);

#endif  // INPUSTATE_H

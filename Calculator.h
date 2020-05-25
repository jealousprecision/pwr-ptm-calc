#pragma once

#include "InputState.h"

class Calculator
{
public:
    Calculator();

    void update(InputState& inputState);
    float getCurrentNumber() const;

protected:
    void doOperation();
    void updateLCD();

    float numbers[2] = {0, 0};
    unsigned count = 0;
    bool show1st = false;
    bool overwrite = false;
    ButtonCodes operation = ButtonCodes::None;
};

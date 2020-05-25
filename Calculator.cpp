#include "Calculator.h"

#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>

namespace
{

bool isNumber(ButtonCodes btnCode)
{
    return (unsigned) btnCode < 10;
}

bool isMathOperation(ButtonCodes btnCode)
{
    switch(btnCode)
    {
    case ButtonCodes::plus:
    case ButtonCodes::minus:
    case ButtonCodes::multiply:
    case ButtonCodes::divide:
        return true;
    default:
        return false;
    }
}

void showFloat(float fl)
{
    char buf[16];
    dtostrf(fl, 0, 4, buf);
    LCD_HD44780::clear();
    LCD_HD44780::writeText(buf);
}

}  // namespace

Calculator::Calculator()
{
    updateLCD();
}

void Calculator::update(InputState& inputState)
{
    auto currentInput = inputState.getPressedButton();

    if (currentInput == ButtonCodes::None)
        return;

    if (isNumber(currentInput))
    {
        if (overwrite)
        {
            numbers[count] = 0;
            overwrite = false;
        }

        numbers[count] *= 10;
        numbers[count] += unsigned(currentInput);
        show1st = false;
    }
    else if (isMathOperation(currentInput))
    {
        if (count == 0)
        {
            operation = currentInput;
            count += 1;
            show1st = true;
        }
        else
        {
            doOperation();
            operation = currentInput;
            show1st = true;
        }
    }
    else if (currentInput == ButtonCodes::equal)
    {
        doOperation();
        count = 0;
        overwrite = true;
    }
    else if (currentInput == ButtonCodes::clear)
    {
        numbers[0] = 0, numbers[1] = 0;
        count = 0;
        show1st = false;
        overwrite = false;
        operation = ButtonCodes::None;
    }

    updateLCD();
}

float Calculator::getCurrentNumber() const
{
    if (show1st)
        return numbers[0];

    return numbers[count];
}

void Calculator::doOperation()
{
    switch(operation)
    {
    case ButtonCodes::plus:
        numbers[0] += numbers[1];
        break;
    case ButtonCodes::minus:
        numbers[0] -= numbers[1];
        break;
    case ButtonCodes::multiply:
        numbers[0] *= numbers[1];
        break;
    case ButtonCodes::divide:
        numbers[0] /= numbers[1];
        break;
    default:
        break;
    }
    numbers[1] = 0;
    operation = ButtonCodes::None;
}

void Calculator::updateLCD()
{
    showFloat(getCurrentNumber());
}

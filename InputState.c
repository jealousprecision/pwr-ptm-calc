#include "InputState.h"

#include <stdio.h>
#include <avr/io.h>

#define KEYBOARD_PORT PORTB
#define KEYBOARD_PIN PINB

#define BUTTON_HANDLE(input, buttonCode, ptrToButton)\
if (input == buttonCode)\
    button_signalOn(ptrToButton);\
else\
    button_signalOff(ptrToButton);


bool Button::wasPressed()
{
    if (wasPressed_)
    {
        wasPressed_ = false;
        return true;
    }

    return false;
}

void Button::signalOn()
{
    if (!isOn_)
    {
        isOn_ = true;
        wasPressed_ = true;
    }
}

void Button::signalOff()
{
    isOn_ = false;
}

unsigned getKey()
{
    const uint8_t default_power = 0x10;
    KEYBOARD_PORT = default_power;

    for (int i = 0; i < 4; KEYBOARD_PORT = default_power << (++i))
    {
        switch(KEYBOARD_PIN & 0x0f)
        {
            case 0x01:
                return 1 + i * 4;
            case 0x02:
                return 2 + i * 4;
            case 0x04:
                return 3 + i * 4;
            case 0x08:
                return 4 + i * 4;
        }
    }

    return 0;
}

// from getKey return to in-program ButtonCodes
const ButtonCodes translationTable[17]{
    ButtonCodes::None, // getKey() returns 0 if no input
    ButtonCodes::b1, // 0, 0
    ButtonCodes::b4, // 1, 0
    ButtonCodes::b7, // 2, 0
    ButtonCodes::equal, // 3, 0
    ButtonCodes::b2, // 0, 1
    ButtonCodes::b5, // 1, 1
    ButtonCodes::b8, // 2, 1
    ButtonCodes::b0, // 3, 1
    ButtonCodes::b3, // 0, 2
    ButtonCodes::b6, // 1, 2
    ButtonCodes::b9, // 2, 2
    ButtonCodes::clear, // 3, 2
    ButtonCodes::plus, // 0, 3
    ButtonCodes::minus, // 1, 3
    ButtonCodes::multiply, // 2, 3
    ButtonCodes::divide // 3, 3
};

void InputState::update()
{
    ButtonCodes key = translationTable[getKey()];

    for (unsigned i = 0; i < 16; ++i)
    {
        if (i == static_cast<unsigned>(key))
            buttons_[i].signalOn();
        else
            buttons_[i].signalOff();
    }
}

ButtonCodes InputState::getPressedButton()
{
    for (unsigned i = 0; i < 16; ++i)
        if (buttons_[i].wasPressed())
            return static_cast<ButtonCodes>(i);

    return ButtonCodes::None;
}

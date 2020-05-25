#define F_CPU 8000000UL

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "LCD_HD44780.h"
#include "InputState.h"
#include "Calculator.h"

#include <util/delay.h>
#include <avr/io.h>

void delay_ms(long unsigned ms)
{
    volatile long unsigned i = 0;
    for (; i < ms; i++)
        _delay_ms(1);
}

int main()
{
    DDRB = 0xf0;
    LCD_HD44780::init();

    InputState inputState;
    Calculator calculator;

    while (1)
    {
        inputState.update();
        calculator.update(inputState);
    }
}

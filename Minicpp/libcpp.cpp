/***********************************************************************
 libcpp.cpp, 主要是对库函数的封装
************************************************************************/

// Add more of your own, here.

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "mccommon.h"

using namespace std;

// Read a character from the console.
// If your compiler supplies an unbuffered
// character intput function, feel free to
// substitute it for the call to cin.get().
anonymous_var call_getchar()
{
    char ch;

    ch = getchar();

    // Advance past ()
    get_token();
    if(*token != '(')
        throw InterpExc(PAREN_EXPECTED);

    get_token();
    if(*token != ')')
        throw InterpExc(PAREN_EXPECTED);
    anonymous_var val;
    val.var_type = CHAR;
    val.int_value = ch;
    return val;
}

// Write a character to the display.
anonymous_var call_putchar()
{
    anonymous_var value;

    eval_exp(value);

    putchar(char(value.int_value));

    return value;
}

// Return absolute value.
anonymous_var call_abs()
{
    anonymous_var val;

    eval_exp(val);
    abs_var(val);
    return val;
}

// Return a randome integer.
anonymous_var call_rand()
{

    // Advance past ()
    get_token();
    if(*token != '(')
        throw InterpExc(PAREN_EXPECTED);

    get_token();
    if(*token != ')')
        throw InterpExc(PAREN_EXPECTED);

    anonymous_var val;
    val.var_type = INT;
    val.int_value = rand();
    return val;
}
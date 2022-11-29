//
// Created by Павло Коваль on 06.11.2022.
//

#include "int24_t.h"


int24_t::int24_t()
{
    _value = 0;
}


int24_t::int24_t(int value)
{
    _value = value;

    if (value > INT24_MAX)
        isOverflow = true;
    else
        isOverflow = false;
}


int24_t &int24_t::operator=(int value)
{
    _value = value;

    if (value > INT24_NEG)
        isOverflow = true;
    else
        isOverflow = false;

    return *this;
}


int int24_t::to_int() const
{
    if (_value >= INT24_NEG)
        return -_value;
    else
        return _value;
}


int32_t int24_t::to_uint() const
{
    return _value;
}

bool int24_t::isOverflow1() const
{
    return isOverflow;
}

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
    if (value > INT24_MAX)
        throw std::overflow_error("Overflow");

    _value = value;
}


int24_t &int24_t::operator=(int value)
{
    if (value > INT24_MAX)
        throw std::overflow_error("Overflow");

    _value = value;
    return *this;
}


int int24_t::to_int() const
{
    if (_value >= INT24_NEG)
        return -_value;
//        return _value - INT24_NEG * 2;
    else
        return _value;
}


int32_t int24_t::to_uint() const
{
    return _value;
}

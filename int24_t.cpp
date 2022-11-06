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

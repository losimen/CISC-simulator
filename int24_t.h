//
// Created by Павло Коваль on 06.11.2022.
//

#ifndef KURSOVAAK_INT24_T_H
#define KURSOVAAK_INT24_T_H

#include <cstdint>
#include <stdexcept>

#define INT24_MAX 16777215
#define INT24_NEG 8388608


class int24_t {
private:
    int32_t _value;
    bool isOverflow;
public:
    bool isOverflow1() const;

public:
    int24_t();
    int24_t(int value);

    int24_t &operator=(int value);

    int to_int() const;
    int32_t to_uint() const;

};


#endif //KURSOVAAK_INT24_T_H

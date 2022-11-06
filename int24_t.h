//
// Created by Павло Коваль on 06.11.2022.
//

#ifndef KURSOVAAK_INT24_T_H
#define KURSOVAAK_INT24_T_H

#include <cstdint>
#include <stdexcept>

#define INT24_MAX 8388607

class int24_t {
private:
    int32_t _value;

public:
    int24_t();
    int24_t(int value);

    int24_t &operator=(int value);

};


#endif //KURSOVAAK_INT24_T_H

//
// Created by Павло Коваль on 16.11.2022.
//

#ifndef KURSOVAAK_SIMULATOR_H
#define KURSOVAAK_SIMULATOR_H

#include <array>
#include <iostream>
#include <chrono>
#include <thread>
#include <stack>

#include "myerror.h"
#include "info.h"


class Simulator {
private:
    struct StateStruct
    {
        std::stack<int24_t> stack;
        std::array<int24_t, MAX_WORDS> mem;
        std::array<int24_t, AMOUNT_OF_REGISTERS> registers;

        int24_t pc = 0;
        int24_t numMemory = 0;

        void isStackEmpty() const;
    } state;

    void doRInstruction(unsigned int arg0, unsigned int arg1, unsigned int arg2,
                        std::function<unsigned int(unsigned int, unsigned int)> func);

public:
    Simulator() = delete;
    Simulator(const std::vector<std::string> &fileContent);

    void run();
};


#endif //KURSOVAAK_SIMULATOR_H

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
    unsigned int opcode;
    unsigned int arg0;
    unsigned int arg1;
    unsigned int arg2;
    unsigned int addressField;

    struct StateStruct
    {
        std::stack<int24_t> stack;
        std::array<int24_t, MAX_WORDS> mem;
        std::array<int24_t, AMOUNT_OF_REGISTERS> registers;

        int24_t pc = 0;
        int24_t numMemory = 0;

        bool CF = false;
        bool ZF = false;
        bool SF = false;

        void isStackEmpty() const;
    } state;

    void doRInstruction(std::function<unsigned int(int, int)> func);

public:
    Simulator() = delete;
    Simulator(const std::vector<std::string> &fileContent);

    const std::array<int24_t, AMOUNT_OF_REGISTERS> &getRegisters() const;
    void run();
};


#endif //KURSOVAAK_SIMULATOR_H

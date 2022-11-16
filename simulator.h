//
// Created by Павло Коваль on 16.11.2022.
//

#ifndef KURSOVAAK_SIMULATOR_H
#define KURSOVAAK_SIMULATOR_H

#include <array>
#include <iostream>
#include <chrono>
#include <thread>

#include "info.h"


class Simulator {
private:
    struct StateStruct
    {
        int pc = 0;
        std::array<int, MAX_WORDS> mem;
        std::array<int, AMOUNT_OF_REGISTERS> registers;
        int numMemory = 0;
    } state;

public:
    Simulator() = delete;
    Simulator(const std::vector<std::string> &fileContent);

    void run();
};


#endif //KURSOVAAK_SIMULATOR_H

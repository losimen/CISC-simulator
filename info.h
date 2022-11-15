//
// Created by Павло Коваль on 06.11.2022.
//

#ifndef KURSOVAAK_INFO_H
#define KURSOVAAK_INFO_H

#include <vector>
#include <map>
#include <string>
#include <array>

#include "int24_t.h"

#define AMOUNT_OF_REGISTERS 8
#define MAX_LABEL_LENGTH 7
#define MAX_LABELS_AMOUNT 100
#define MAX_ADDRESS_FIELD

#define ADD "add"
#define NAND "nand"
#define LW "lw"
#define SW "sw"
#define BEQ "beq"
#define JALR "jalr"
#define HALT "halt"
#define NOOP "noop"
#define FILL ".fill"

#define SHIFT_OP 21
#define SHIFT_ARG0 18
#define SHIFT_ARG1 15


typedef std::map<int, int24_t> Register;

namespace Info
{
    static std::map<std::string, int> opcodes {{ADD, 0},
                                               {NAND, 1},
                                               {LW, 2},
                                               {SW, 3},
                                               {BEQ, 4},
                                               {JALR, 5},
                                               {HALT, 6},
                                               {NOOP, 7}};

    static std::array<Register, AMOUNT_OF_REGISTERS> registers;
}


#endif //KURSOVAAK_INFO_H

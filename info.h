//
// Created by Павло Коваль on 06.11.2022.
//

#ifndef KURSOVAAK_INFO_H
#define KURSOVAAK_INFO_H

#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <array>

#include "int24_t.h"

#define AMOUNT_OF_REGISTERS 8
#define MAX_LABEL_LENGTH 7
#define MAX_LABELS_AMOUNT 100
#define MAX_WORDS 4096

#define STACK_SIZE 4

#define ADD "add"
#define NAND "nand"
#define LW "lw"
#define SW "sw"
#define BEQ "beq"
#define JALR "jalr"
#define HALT "halt"
#define NOOP "noop"
#define FILL ".fill"
#define DEC "dec"
#define IDIV "idiv"
#define XADD "xadd"
#define SHL "shl"
#define OR "or"
#define NEG "neg"
#define JMA "jma"
#define JMNE "jmne"
#define ADC "adc"
#define JGE "jge"
#define PUSH "push"
#define POP "pop"
#define ADC "adc"
#define JL "jl"
#define JE "je"


#define SHIFT_OP 18
#define SHIFT_ARG0 12
#define SHIFT_ARG1 15

//    18   15  12           0
//     |   |   |            |
// 00000 000 000 000000000000

//    18   15  12           0
//     |   |   |            |
// 00000 000 000 000000000 000


bool is_number(const std::string& s);


namespace Info
{
    static std::map<std::string, int> opcodes {{ADD, 0},
                                               {NAND, 1},
                                               {LW, 2},
                                               {SW, 3},
                                               {BEQ, 4},
                                               {JALR, 5},
                                               {HALT, 6},
                                               {NOOP, 7},
                                               {DEC, 8},
                                               {IDIV, 9},
                                               {XADD, 10},
                                               {SHL, 11},
                                               {OR, 12},
                                               {NEG, 13},
                                               {JMA, 14},
                                               {JMNE, 15},
                                               {ADC, 16},
                                               {JGE, 17},
                                               {PUSH, 18},
                                               {POP, 19},
                                               {JL, 21},
                                               {JE, 22}};
}


#endif //KURSOVAAK_INFO_H

//
// Created by Павло Коваль on 06.11.2022.
//

#ifndef KURSOVAAK_INFO_H
#define KURSOVAAK_INFO_H

#include <vector>
#include <string>

#define AMOUNT_OF_REGISTERS 8
#define MAX_LABEL_LENGTH 7
#define MAX_LABELS_AMOUNT 100

namespace Info
{
    const std::vector<std::string> opcodes {".fill",
                                            "add",
                                            "nand",
                                            "lw",
                                            "sw",
                                            "beq",
                                            "jalr",
                                            "noop",
                                            "halt"};

    std::array<Register, AMOUNT_OF_REGISTERS> registers;
}


#endif //KURSOVAAK_INFO_H

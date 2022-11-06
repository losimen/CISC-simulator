//
// Created by Павло Коваль on 06.11.2022.
//

#ifndef KURSOVAAK_INFO_H
#define KURSOVAAK_INFO_H

#include <vector>
#include <string>

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
}


#endif //KURSOVAAK_INFO_H

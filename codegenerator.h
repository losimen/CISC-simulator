//
// Created by Павло Коваль on 15.11.2022.
//

#ifndef KURSOVAAK_CODEGENERATOR_H
#define KURSOVAAK_CODEGENERATOR_H

#include "info.h"
#include "command.h"
#include "fileworker.h"
#include "commands.h"


class CodeGenerator
{
private:
    unsigned int _getCode(const Command &command, const Commands &commands);

public:
    void generate(const FileWorker &fileWorker, const Commands &commands);
};


#endif //KURSOVAAK_CODEGENERATOR_H

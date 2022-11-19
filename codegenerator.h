//
// Created by Павло Коваль on 15.11.2022.
//

#ifndef KURSOVAAK_CODEGENERATOR_H
#define KURSOVAAK_CODEGENERATOR_H

#include "info.h"
#include "command.h"
#include "fileworker.h"
#include "commands.h"

#include "int24_t.h"


class CodeGenerator
{
private:
    static int24_t _getCode(const Command &command, const Commands &commands);

public:
    static void generate(const FileWorker &fileWorker, const Commands &commands);
};


#endif //KURSOVAAK_CODEGENERATOR_H

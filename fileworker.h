//
// Created by Павло Коваль on 06.11.2022.
//

#ifndef KURSOVAAK_FILEWORKER_H
#define KURSOVAAK_FILEWORKER_H

#include <iostream>
#include <fstream>

class FileWorker
{
private:
    std::string fileName;

public:
    explicit FileWorker(std::string fileName);

    void write(const std::string &text);
    std::string read();
};


#endif //KURSOVAAK_FILEWORKER_H

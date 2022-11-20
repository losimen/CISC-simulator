//
// Created by Павло Коваль on 06.11.2022.
//

#ifndef KURSOVAAK_FILEWORKER_H
#define KURSOVAAK_FILEWORKER_H

#include <iostream>
#include <fstream>
#include <vector>

typedef std::vector<std::string> FileContent;

class FileWorker
{
private:
    std::string fileName;

public:
    explicit FileWorker(std::string fileName);

    void clear() const;
    void write(const std::string &text) const;
    FileContent read() const;
};


#endif //KURSOVAAK_FILEWORKER_H

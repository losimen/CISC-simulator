//
// Created by Павло Коваль on 06.11.2022.
//

#include "fileworker.h"

#include <utility>

FileWorker::FileWorker(std::string fileName): fileName(std::move(fileName))
{

}

void FileWorker::write(const std::string &text)
{
    std::ofstream file;

    if (!file.is_open())
    {
        throw std::runtime_error("Error in opening file - " + fileName);
    }

    file.open("example.txt", std::ios::trunc);
    file << text;
    file.close();
}


std::string FileWorker::read()
{
    std::ifstream file;
    file.open(fileName);

    if (!file.is_open())
    {
        throw std::runtime_error("Error in opening file - " + fileName);
    }

    std::string str((std::istreambuf_iterator<char>(file)),
                    std::istreambuf_iterator<char>());
    return str;
}

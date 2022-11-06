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


FileContent FileWorker::read()
{
    FileContent result;

    std::ifstream file;
    file.open(fileName);

    if (!file.is_open())
    {
        throw std::runtime_error("Error in opening file - " + fileName);
    }

    for(std::string line; getline(file, line); )
    {
        result.push_back(line);
    }

    return result;
}

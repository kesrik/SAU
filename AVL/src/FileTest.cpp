#include "File.hpp"

int main()
{
    File *file = new File();

    string filePath = "input.txt";
    file->read(filePath);

    delete file;
    return 0;
}
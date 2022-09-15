#ifndef FILE_HPP
#define FILE_HPP

#include "AVL.hpp"
#include <fstream>
#include <string>

class File
{
public:
    const string WHITESPACE = " ";

    File();
    int sumOfArray(int *, int) const;
    string ltrim(const string &)const;
    string rtrim(const string &)const;
    string trim(const string &)const;
    void read(string &) const;
    ~File();
};

#endif
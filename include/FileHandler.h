
#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class FileHandler
{
public:
    void saveData(string filename, string data);
    void readData(string filename);

    vector<string> loadData(string filename);
    void writeData(string filename, vector<string> data);
};

#endif

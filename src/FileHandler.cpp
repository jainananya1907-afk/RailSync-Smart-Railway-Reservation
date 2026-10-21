#include "../include/FileHandler.h"

void FileHandler::saveData(string filename, string data)
{
    ofstream file(filename, ios::app);

    if (file.is_open())
    {
        file << data << endl;
        file.close();
        cout << "Data saved successfully!" << endl;
    }
    else
    {
        cout << "Unable to open file!" << endl;
    }
}

void FileHandler::readData(string filename)
{
    ifstream file(filename);
    string line;

    if (file.is_open())
    {
        while (getline(file, line))
        {
            cout << line << endl;
        }

        file.close();
    }
    else
    {
        cout << "Unable to open file!" << endl;
    }
}

vector<string> FileHandler::loadData(string filename)
{
    vector<string> data;
    ifstream file(filename);
    string line;

    while (getline(file, line))
    {
        data.push_back(line);
    }

    file.close();
    return data;
}

void FileHandler::writeData(string filename, vector<string> data)
{
    ofstream file(filename);

    if (file.is_open())
    {
        for (int i = 0; i < data.size(); i++)
        {
            file << data[i] << endl;
        }

        file.close();
    }
    else
    {
        cout << "Unable to open file!" << endl;
    }
}


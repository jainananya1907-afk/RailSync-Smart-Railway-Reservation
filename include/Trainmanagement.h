
#ifndef Trainmanagement_h
#define Trainmanagement_h

#include "Train.h"
#include <string>
using namespace std;

struct TrainNode
{
    Train data;
    TrainNode* next;

    TrainNode(Train t)
    {
        data = t;
        next = NULL;
    }
};

class TrainManagement
{
private:
    TrainNode* head;

    void loadTrainsFromFile();
    void saveTrainsToFile();

public:
    TrainManagement();
    ~TrainManagement();

    void addTrain();
    void updateTrain();
    void deleteTrain();
    void searchTrain();
    void displayTrain();
    void checkAvailability();
    Train* findTrainByNumber(int number);
};

#endif

#include "Train.h"
using namespace std;

// Node of the singly linked list
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

public:
TrainManagement();


void addTrain();
void updateTrain();
void deleteTrain();
void searchTrain();
void displayTrain();
void checkAvailability();
Train* findTrainByNumber(int number);


};

 
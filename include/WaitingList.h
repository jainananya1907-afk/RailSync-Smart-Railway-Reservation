#ifndef WAITINGLIST_H
#define WAITINGLIST_H

#include <iostream>
#include <queue>
#include <vector>
#include <string>

using namespace std;

struct WaitingPassenger
{
    int id;
    string name;
    int trainID;
    int priority;
    int arrival;
};

struct Compare
{
    bool operator()(WaitingPassenger a, WaitingPassenger b);
};

class WaitingList
{
private:
void loadFromFile();
void saveToFile();
    priority_queue<WaitingPassenger, vector<WaitingPassenger>, Compare> pq;
    int arrivalCount;

public:
    WaitingList();

    void addToWaitingList();
    void removeFromWaitingList();
    void displayWaitingList();
bool getNextPassengerForTrain(int trainID, int &passengerID);
    bool promotePassenger(int trainID);
    void maintainOrder();
    void processAfterCancellation(int trainID);
};

#endif

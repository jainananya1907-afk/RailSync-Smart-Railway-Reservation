#ifndef JOURNEY_H
#define JOURNEY_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

class TrainManagement;

struct JourneyEdge
{
    string destination;
    string trainNumber;
    string trainName;
    int travelTime;
};

class Journey
{
private:
    unordered_map<string, string> stations;
    unordered_map<string, vector<JourneyEdge>> graph;

    string normalize(string name);
    void displayPath(vector<string> path,
                     vector<JourneyEdge> trains,
                     int totalTime);

public:
    Journey();

    void loadFromTrainManagement(TrainManagement& tm);

    void displayStations();
    void displayTrainConnections();

    void planJourney();
    void fastestJourney();
    void minimumTransferJourney();

    void run();
};

#endif
#ifndef PRIORITYALLOCATION_H
#define PRIORITYALLOCATION_H

#include "PassengerManagement.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct PriorityPassenger
{
    int passengerID;
    string name;
    int age;
    char gender;
    int arrivalOrder;
    int priority;
    bool allocated;
};

class PriorityAllocation
{
private:
    vector<PriorityPassenger> passengers;

    int availableSeats;
    int arrivalCounter;

public:
    PriorityAllocation();

    // Load passengers from Passenger Management
    void loadPassengers(PassengerManagement &pm);

    // Calculate passenger priority
    int checkPriority(int age, char gender);

    // Find highest priority passenger
    int getEligiblePassenger();

    // Allocate seat according to priority
    void allocatePrioritySeat();

    // Handle women priority
    void handleWomenPriority();

    // Handle senior citizen priority
    void handleSeniorCitizen();

    // Add passenger manually
    void addPassenger();

    // Display waiting list
    void displayWaitingList();

    // Run priority allocation module
    void run();
};

#endif
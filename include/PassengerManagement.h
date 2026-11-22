#ifndef PASSENGER_H
#define PASSENGER_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Passenger
{
    int passengerID;
    string name;
    int age;
    string gender;
    string category;
};

class PassengerManagement
{
private:
    vector<Passenger> passengers;

    void savePassengersToFile();

public:
    PassengerManagement();

    void addPassenger();
    void displayPassenger();
    void searchPassenger();
    void updatePassenger();
    void deletePassenger();
    void checkEligibility();

    vector<Passenger> &getPassengers()
    {
        return passengers;
    }

    Passenger *findPassengerByID(int id);
};

#endif

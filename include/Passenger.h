
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Passenger
{
public:
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

public:
    void addPassenger();
    void updatePassenger();
    void deletePassenger();
    void searchPassenger();
    void displayPassenger();
    void checkEligibility();
    Passenger* findPassengerByID(int id);
};

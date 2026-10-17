
#ifndef SEATAVAILABILITY_H
#define SEATAVAILABILITY_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class SeatAvailability
{
private:
    int trainID;
    int totalSeats;
    int bookedSeats;
    string seatClass;

    static vector<SeatAvailability> trains;

public:
    void addTrain();
    void getSeatAvailability();
    void updateSeatCount();
    void checkSeatClass();
    void allocateSeat();
    void releaseSeat();
};

#endif

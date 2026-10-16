

#ifndef RESERVATION_H
#define RESERVATION_H

#include <iostream>
#include <vector>
#include "Passenger.h"

using namespace std;

class Reservation
{
private:
    int reservationID;
    int passengerID;
    int trainID;
    int seatNumber;
    string status;

    static vector<Reservation> reservations;

public:
    void bookTicket();
    void cancelTicket();
    void checkAvailability();
    void confirmReservation();

    void applyPriority(PassengerManagement &pm);
    void updateSeatStatus();
};

#endif

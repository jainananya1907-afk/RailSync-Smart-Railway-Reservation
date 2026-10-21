#ifndef RESERVATION_H
#define RESERVATION_H

#include <iostream>
#include <vector>
#include <string>
#include "Passenger.h"
#include "Seat.h"
#include "Ticketmanagement.h"
#include "WaitingList.h"
using namespace std;

class Reservation
{
private:
    int reservationID;
    int passengerID;
    int trainID;
    int seatNumber;
    long long pnr;
    string status;
    static bool loaded;
void loadReservationsFromFile();
void saveReservationsToFile();

    static vector<Reservation> reservations;

public:
Reservation();
    void bookTicket(PassengerManagement &pm);
  void cancelTicket(TicketManagement &tm,
                  PassengerManagement &pm,
                  WaitingList &wl);
    void checkAvailability();
    void confirmReservation(PassengerManagement &pm,TicketManagement &tm);

    void applyPriority(PassengerManagement &pm);
    void updateSeatStatus();
    void processWaitingPassenger(
    int trainID,
    PassengerManagement &pm,
    TicketManagement &tm,
    WaitingList &wl);
};

#endif

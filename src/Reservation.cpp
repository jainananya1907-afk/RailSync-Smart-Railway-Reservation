
#include "../include/Reservation.h"
#include "../include/Seat.h"
#include "../include/Ticketmanagement.h"
#include "../include/WaitingList.h"
#include <fstream>
#include <sstream>

vector<Reservation> Reservation::reservations;
bool Reservation::loaded = false;

Reservation::Reservation()
{
    reservationID = 0;
    passengerID = 0;
    trainID = 0;
    seatNumber = -1;
    pnr = 0;
    status = "Pending";

    if (!loaded)
    {
        loaded = true;
        loadReservationsFromFile();
    }
}

void Reservation::loadReservationsFromFile()
{
    ifstream file("reservations.txt");

    if (!file.is_open())
        return;

    reservations.clear();
    string line;

    while (getline(file, line))
    {
        stringstream ss(line);
        string part;
        Reservation r;

        if (!getline(ss, part, '|')) continue;
        r.reservationID = stoi(part);

        if (!getline(ss, part, '|')) continue;
        r.passengerID = stoi(part);

        if (!getline(ss, part, '|')) continue;
        r.trainID = stoi(part);

        if (!getline(ss, part, '|')) continue;
        r.seatNumber = stoi(part);

        if (!getline(ss, part, '|')) continue;
        r.pnr = stoll(part);

        if (!getline(ss, r.status)) continue;

        reservations.push_back(r);
    }

    file.close();
}

void Reservation::saveReservationsToFile()
{
    ofstream file("reservations.txt");

    if (!file.is_open())
    {
        cout << "Error saving reservations!\n";
        return;
    }

    for (int i = 0; i < reservations.size(); i++)
    {
        file << reservations[i].reservationID << "|"
             << reservations[i].passengerID << "|"
             << reservations[i].trainID << "|"
             << reservations[i].seatNumber << "|"
             << reservations[i].pnr << "|"
             << reservations[i].status << "\n";
    }

    file.close();
}

void Reservation::bookTicket(PassengerManagement &pm)
{
    int pID;

    cout << "Enter Reservation ID: ";
    cin >> reservationID;

    for (int i = 0; i < reservations.size(); i++)
    {
        if (reservations[i].reservationID == reservationID)
        {
            cout << "Reservation ID already exists!\n";
            return;
        }
    }

    cout << "Enter Passenger ID: ";
    cin >> pID;

    Passenger *p = pm.findPassengerByID(pID);

    if (p == NULL)
    {
        cout << "Passenger not found! Please add passenger first.\n";
        return;
    }

    passengerID = pID;

    cout << "Enter Train ID: ";
    cin >> trainID;

    seatNumber = -1;
    pnr = 0;
    status = "Pending";

    reservations.push_back(*this);
    saveReservationsToFile();

    cout << "Reservation request created successfully!\n";
    cout << "Passenger Name: " << p->name << endl;
    cout << "Status: Pending\n";
}

void Reservation::confirmReservation(
    PassengerManagement &pm,
    TicketManagement &tm)
{
    int id;

    cout << "\nEnter Reservation ID to confirm: ";
    cin >> id;

    for (int i = 0; i < reservations.size(); i++)
    {
        if (reservations[i].reservationID == id)
        {
            if (reservations[i].status != "Pending")
            {
                cout << "Reservation is not pending.\n";
                return;
            }

            Passenger *p =
                pm.findPassengerByID(reservations[i].passengerID);

            if (p == NULL)
            {
                cout << "Passenger not found!\n";
                return;
            }

            SeatAvailability seatManager;

            int seat =
                seatManager.allocateSeatForTrain(reservations[i].trainID);

            if (seat == -1)
            {
                cout << "No seat available or train not found!\n";
                cout << "Reservation remains Pending.\n";
                return;
            }

            reservations[i].seatNumber = seat;
            reservations[i].status = "Confirmed";

            reservations[i].pnr =
                tm.generateTicketFromReservation(
                    p->name,
                    reservations[i].trainID,
                    seat);

            saveReservationsToFile();

            cout << "Reservation confirmed successfully!\n";
            cout << "Allocated Seat Number: " << seat << "\n";
            cout << "PNR: " << reservations[i].pnr << "\n";
            cout << "Status: Confirmed\n";
            return;
        }
    }

    cout << "Reservation not found.\n";
}

void Reservation::cancelTicket(
    TicketManagement &tm,
    PassengerManagement &pm,
    WaitingList &wl)
{
    int id;

    cout << "\nEnter Reservation ID to cancel: ";
    cin >> id;

    for (int i = 0; i < reservations.size(); i++)
    {
        if (reservations[i].reservationID == id)
        {
            if (reservations[i].status == "Cancelled")
            {
                cout << "Reservation is already cancelled.\n";
                return;
            }

            int cancelledTrainID = reservations[i].trainID;

            if (reservations[i].status == "Confirmed")
            {
                SeatAvailability seatManager;

                bool released = seatManager.releaseSeatForTrain(
                    cancelledTrainID,
                    reservations[i].seatNumber);

                if (!released)
                {
                    cout << "Seat release failed. Cancellation stopped.\n";
                    return;
                }
            }

            if (reservations[i].pnr != 0)
            {
                tm.updateTicketStatus(
                    reservations[i].pnr, "Cancelled");
            }

            reservations[i].status = "Cancelled";
            reservations[i].seatNumber = -1;

            saveReservationsToFile();

            cout << "Reservation cancelled successfully!\n";
            cout << "\nChecking waiting list...\n";

            processWaitingPassenger(
                cancelledTrainID, pm, tm, wl);

            return;
        }
    }

    cout << "Reservation not found.\n";
}

void Reservation::checkAvailability()
{
    int id;
    int count = 0;

    cout << "\nEnter Train ID: ";
    cin >> id;

    for (int i = 0; i < reservations.size(); i++)
    {
        if (reservations[i].trainID == id &&
            reservations[i].status == "Confirmed")
        {
            count++;
        }
    }

    cout << "Confirmed reservations for Train "
         << id << ": " << count << endl;
}

void Reservation::applyPriority(PassengerManagement &pm)
{
    int id;

    cout << "\nEnter Passenger ID: ";
    cin >> id;

    Passenger *p = pm.findPassengerByID(id);

    if (p == NULL)
    {
        cout << "Passenger not found.\n";
        return;
    }

    if (p->age >= 60 ||
        p->gender == "Female" ||
        p->gender == "female")
    {
        cout << "Passenger is eligible for priority consideration.\n";
    }
    else
    {
        cout << "Passenger is not eligible for priority consideration.\n";
    }
}

void Reservation::updateSeatStatus()
{
    int id, seat;

    cout << "\nEnter Reservation ID: ";
    cin >> id;

    for (int i = 0; i < reservations.size(); i++)
    {
        if (reservations[i].reservationID == id)
        {
            if (reservations[i].status != "Confirmed")
            {
                cout << "Only confirmed reservations can be assigned a seat.\n";
                return;
            }

            cout << "Enter Seat Number: ";
            cin >> seat;

            reservations[i].seatNumber = seat;
            saveReservationsToFile();

            cout << "Seat number updated successfully.\n";
            return;
        }
    }

    cout << "Reservation not found.\n";
}

void Reservation::processWaitingPassenger(
    int trainID,
    PassengerManagement &pm,
    TicketManagement &tm,
    WaitingList &wl)
{
    int pID;

    if (!wl.getNextPassengerForTrain(trainID, pID))
    {
        cout << "No waiting passenger for this train.\n";
        return;
    }

    Passenger *p = pm.findPassengerByID(pID);

    if (p == NULL)
    {
        cout << "Passenger record not found.\n";
        return;
    }

    SeatAvailability seatManager;
    int seat = seatManager.allocateSeatForTrain(trainID);

    if (seat == -1)
    {
        cout << "No available seat. Passenger cannot be promoted.\n";
        return;
    }

    Reservation r;
    int nextID = 1;

    for (int i = 0; i < reservations.size(); i++)
    {
        if (reservations[i].reservationID >= nextID)
            nextID = reservations[i].reservationID + 1;
    }

    r.reservationID = nextID;
    r.passengerID = pID;
    r.trainID = trainID;
    r.seatNumber = seat;
    r.pnr = 0;
    r.status = "Confirmed";

    reservations.push_back(r);

    long long generatedPNR =
        tm.generateTicketFromReservation(p->name, trainID, seat);

    reservations.back().pnr = generatedPNR;
    saveReservationsToFile();

    cout << "\nWaiting passenger promoted successfully!\n";
    cout << "Reservation ID: " << nextID << endl;
    cout << "Passenger: " << p->name << endl;
    cout << "Seat Number: " << seat << endl;
    cout << "PNR: " << generatedPNR << endl;
}


#include "../include/Reservation.h"

vector<Reservation> Reservation::reservations;

void Reservation::bookTicket()
{
    Reservation r;

    cout << "\nEnter Reservation ID: ";
    cin >> r.reservationID;

    cout << "Enter Passenger ID: ";
    cin >> r.passengerID;

    cout << "Enter Train ID: ";
    cin >> r.trainID;

    r.seatNumber = -1;
    r.status = "Pending";

    reservations.push_back(r);

    cout << "Reservation request created successfully.\n";
    cout << "Status: Pending\n";
}

void Reservation::confirmReservation()
{
    int id;
    cout << "\nEnter Reservation ID to confirm: ";
    cin >> id;

    for (int i = 0; i < reservations.size(); i++)
    {
        if (reservations[i].reservationID == id)
        {
            if (reservations[i].status == "Pending")
            {
                reservations[i].status = "Confirmed";
                cout << "Reservation confirmed successfully.\n";
            }
            else
            {
                cout << "Reservation is not pending.\n";
            }
            return;
        }
    }

    cout << "Reservation not found.\n";
}

void Reservation::cancelTicket()
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
            }
            else
            {
                reservations[i].status = "Cancelled";
                reservations[i].seatNumber = -1;
                cout << "Reservation cancelled successfully.\n";
            }
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

            cout << "Seat number updated successfully.\n";
            return;
        }
    }

    cout << "Reservation not found.\n";
}

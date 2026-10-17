#include "../include/seatavailability.h"
vector<SeatAvailability> SeatAvailability::trains;

void SeatAvailability::addTrain()
{
    SeatAvailability t;

    cout << "\nEnter Train ID: ";
    cin >> t.trainID;

    for (int i = 0; i < trains.size(); i++)
    {
        if (trains[i].trainID == t.trainID)
        {
            cout << "Train already exists.\n";
            return;
        }
    }

    cout << "Enter Total Seats: ";
    cin >> t.totalSeats;

    if (t.totalSeats <= 0)
    {
        cout << "Invalid seat count.\n";
        return;
    }

    t.bookedSeats = 0;

    cout << "Enter Seat Class (Sleeper/AC/General): ";
    cin >> t.seatClass;

    trains.push_back(t);

    cout << "Train added successfully.\n";
}

void SeatAvailability::getSeatAvailability()
{
    int id;

    cout << "\nEnter Train ID: ";
    cin >> id;

    for (int i = 0; i < trains.size(); i++)
    {
        if (trains[i].trainID == id)
        {
            cout << "\nTrain ID: " << trains[i].trainID;
            cout << "\nTotal Seats: " << trains[i].totalSeats;
            cout << "\nBooked Seats: " << trains[i].bookedSeats;
            cout << "\nAvailable Seats: "
                 << trains[i].totalSeats - trains[i].bookedSeats;
            cout << "\nSeat Class: " << trains[i].seatClass << endl;
            return;
        }
    }

    cout << "Train not found.\n";
}

void SeatAvailability::updateSeatCount()
{
    int id, count;

    cout << "\nEnter Train ID: ";
    cin >> id;

    for (int i = 0; i < trains.size(); i++)
    {
        if (trains[i].trainID == id)
        {
            cout << "Enter new total seat count: ";
            cin >> count;

            if (count < trains[i].bookedSeats || count <= 0)
            {
                cout << "Invalid seat count.\n";
                return;
            }

            trains[i].totalSeats = count;

            cout << "Seat count updated successfully.\n";
            return;
        }
    }

    cout << "Train not found.\n";
}

void SeatAvailability::checkSeatClass()
{
    int id;
    string seatClass;

    cout << "\nEnter Train ID: ";
    cin >> id;

    cout << "Enter Seat Class to check: ";
    cin >> seatClass;

    for (int i = 0; i < trains.size(); i++)
    {
        if (trains[i].trainID == id)
        {
            if (trains[i].seatClass == seatClass)
                cout << "Seat class is available for this train.\n";
            else
                cout << "Seat class does not match this train.\n";

            return;
        }
    }

    cout << "Train not found.\n";
}

void SeatAvailability::allocateSeat()
{
    int id;

    cout << "\nEnter Train ID: ";
    cin >> id;

    for (int i = 0; i < trains.size(); i++)
    {
        if (trains[i].trainID == id)
        {
            if (trains[i].bookedSeats < trains[i].totalSeats)
            {
                trains[i].bookedSeats++;

                cout << "Seat allocated successfully.\n";
                cout << "Seat Number: " << trains[i].bookedSeats << endl;
            }
            else
            {
                cout << "No seats available. Add passenger to waiting list.\n";
            }

            return;
        }
    }

    cout << "Train not found.\n";
}

void SeatAvailability::releaseSeat()
{
    int id;

    cout << "\nEnter Train ID: ";
    cin >> id;

    for (int i = 0; i < trains.size(); i++)
    {
        if (trains[i].trainID == id)
        {
            if (trains[i].bookedSeats > 0)
            {
                trains[i].bookedSeats--;

                cout << "Seat released successfully.\n";
            }
            else
            {
                cout << "No booked seats to release.\n";
            }

            return;
        }
    }

    cout << "Train not found.\n";
}

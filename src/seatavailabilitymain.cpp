#include <iostream>
#include "../include/seatavailability.h"

using namespace std;

int main()
{
    SeatAvailability s;
    int choice;

    do
    {
        cout << "\n===== RailSync Seat Availability =====\n";
        cout << "1. Add Train\n";
        cout << "2. Get Seat Availability\n";
        cout << "3. Update Seat Count\n";
        cout << "4. Check Seat Class\n";
        cout << "5. Allocate Seat\n";
        cout << "6. Release Seat\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            s.addTrain();
            break;

        case 2:
            s.getSeatAvailability();
            break;

        case 3:
            s.updateSeatCount();
            break;

        case 4:
            s.checkSeatClass();
            break;

        case 5:
            s.allocateSeat();
            break;

        case 6:
            s.releaseSeat();
            break;

        case 7:
            cout << "Exiting RailSync...\n";
            break;

        default:
            cout << "Invalid choice.\n";
        }

    } while (choice != 7);

    return 0;
}

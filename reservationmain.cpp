#include "include/Reservation.h"

using namespace std;

int main()
{
    Reservation r;
    int choice;

    do
    {
        cout << "\n===== RESERVATION TEST MENU =====\n";
        cout << "1. Book Ticket\n";
        cout << "2. Confirm Reservation\n";
        cout << "3. Cancel Ticket\n";
        cout << "4. Check Availability\n";
        cout << "5. Update Seat Status\n";
        cout << "0. Exit\n";

        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            r.bookTicket();
            break;

        case 2:
            r.confirmReservation();
            break;

        case 3:
            r.cancelTicket();
            break;

        case 4:
            r.checkAvailability();
            break;

        case 5:
            r.updateSeatStatus();
            break;

        case 0:
            cout << "Exiting Reservation Test Menu.\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != 0);

    return 0;
}
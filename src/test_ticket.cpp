

#include <iostream>
#include "TicketManagement.h"

using namespace std;

int main()
{
    TicketManagement manager;
    int choice;
    long long pnr;
    string status;

    do
    {
        cout << "\n========================================\n";
        cout << "       TICKET & PNR MANAGEMENT\n";
        cout << "========================================\n";

        cout << "1. Generate Ticket\n";
        cout << "2. Search Ticket by PNR\n";
        cout << "3. Display Ticket\n";
        cout << "4. Update Ticket Status\n";
        cout << "5. Print Ticket\n";
        cout << "6. Display All Tickets\n";
        cout << "7. Exit\n";

        cout << "========================================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                manager.generateTicket();
                break;

            case 2:
                cout << "Enter PNR Number: ";
                cin >> pnr;

                if (manager.searchByPNR(pnr) != NULL)
                    cout << "\nTicket found successfully!\n";
                else
                    cout << "\nTicket not found!\n";

                break;

            case 3:
                cout << "Enter PNR Number: ";
                cin >> pnr;

                manager.displayTicket(pnr);
                break;

            case 4:
                cout << "Enter PNR Number: ";
                cin >> pnr;

                cout << "Enter New Status ";
                cout << "(Confirmed/Waiting List/Cancelled): ";

                getline(cin >> ws, status);

                manager.updateTicketStatus(pnr, status);
                break;

            case 5:
                cout << "Enter PNR Number: ";
                cin >> pnr;

                manager.printTicket(pnr);
                break;

            case 6:
                manager.displayAllTickets();
                break;

            case 7:
                cout << "\nExiting Ticket Management.\n";
                break;

            default:
                cout << "\nInvalid choice! Try again.\n";
        }

    } while (choice != 7);

    return 0;
}
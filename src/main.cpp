
#include <iostream>
#include "../include/WaitingList.h"

using namespace std;

int main()
{
    WaitingList wl;
    int choice, trainID;

    do
    {
        cout << "\n===== RAILSYNC WAITING LIST =====\n";
        cout << "1. Add to Waiting List\n";
        cout << "2. Remove from Waiting List\n";
        cout << "3. Display Waiting List\n";
        cout << "4. Promote Passenger\n";
        cout << "5. Maintain Order\n";
        cout << "6. Process After Cancellation\n";
        cout << "0. Exit\n";

        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1: wl.addToWaitingList(); break;
        case 2: wl.removeFromWaitingList(); break;
        case 3: wl.displayWaitingList(); break;
        case 4:
            cout << "Enter Train ID: ";
            cin >> trainID;
            wl.promotePassenger(trainID);
            break;
        case 5: wl.maintainOrder(); break;
        case 6:
            cout << "Enter cancelled Train ID: ";
            cin >> trainID;
            wl.processAfterCancellation(trainID);
            break;
        case 0:
            cout << "Exiting Waiting List Module.\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != 0);

    return 0;
}

#include "../include/WaitingList.h"

bool Compare::operator()(WaitingPassenger a, WaitingPassenger b)
{
    if (a.priority != b.priority)
        return a.priority < b.priority;

    return a.arrival > b.arrival;
}

WaitingList::WaitingList()
{
    arrivalCount = 0;
}

void WaitingList::addToWaitingList()
{
    WaitingPassenger p;

    cout << "\nEnter Passenger ID: ";
    cin >> p.id;

    cout << "Enter Passenger Name: ";
    cin >> p.name;

    cout << "Enter Train ID: ";
    cin >> p.trainID;

    cout << "\nPriority:\n";
    cout << "1. Normal\n";
    cout << "2. Senior Citizen\n";
    cout << "3. Urgent\n";
    cout << "Enter priority: ";
    cin >> p.priority;

    if (p.priority < 1 || p.priority > 3)
    {
        cout << "Invalid priority!\n";
        return;
    }

    p.arrival = ++arrivalCount;

    pq.push(p);

    cout << "Passenger added to waiting list successfully.\n";
}

void WaitingList::removeFromWaitingList()
{
    int id;
    cout << "\nEnter Passenger ID to remove: ";
    cin >> id;

    priority_queue<WaitingPassenger, vector<WaitingPassenger>, Compare> temp;
    bool found = false;

    while (!pq.empty())
    {
        WaitingPassenger p = pq.top();
        pq.pop();

        if (p.id == id && !found)
        {
            found = true;
            continue;
        }

        temp.push(p);
    }

    pq = temp;

    if (found)
        cout << "Passenger removed successfully.\n";
    else
        cout << "Passenger not found.\n";
}

void WaitingList::displayWaitingList()
{
    if (pq.empty())
    {
        cout << "\nWaiting list is empty.\n";
        return;
    }

    priority_queue<WaitingPassenger, vector<WaitingPassenger>, Compare> temp = pq;

    cout << "\n===== WAITING LIST =====\n";

    while (!temp.empty())
    {
        WaitingPassenger p = temp.top();

        cout << "Passenger ID: " << p.id << endl;
        cout << "Name: " << p.name << endl;
        cout << "Train ID: " << p.trainID << endl;
        cout << "Priority: " << p.priority << endl;
        cout << "Arrival Order: " << p.arrival << endl;
        cout << "----------------------\n";

        temp.pop();
    }
}

bool WaitingList::promotePassenger(int trainID)
{
    priority_queue<WaitingPassenger, vector<WaitingPassenger>, Compare> temp;
    WaitingPassenger selected;
    bool found = false;

    while (!pq.empty())
    {
        WaitingPassenger p = pq.top();
        pq.pop();

        if (p.trainID == trainID && !found)
        {
            selected = p;
            found = true;
        }
        else
        {
            temp.push(p);
        }
    }

    pq = temp;

    if (found)
    {
        cout << "\nPassenger selected for promotion:\n";
        cout << "Passenger ID: " << selected.id << endl;
        cout << "Name: " << selected.name << endl;
        cout << "Train ID: " << selected.trainID << endl;

        return true;
    }

    cout << "\nNo waiting passenger found for Train ID "
         << trainID << ".\n";

    return false;
}

void WaitingList::maintainOrder()
{
    cout << "\nWaiting list order is maintained automatically.\n";
    cout << "Higher priority is served first.\n";
    cout << "Passengers with equal priority follow FIFO order.\n";
}

void WaitingList::processAfterCancellation(int trainID)
{
    cout << "\nProcessing cancellation for Train ID: "
         << trainID << endl;

    if (!promotePassenger(trainID))
    {
        cout << "No passenger to promote for this train.\n";
    }
}
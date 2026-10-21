
#include "../include/WaitingList.h"
#include <fstream>
#include <sstream>


bool Compare::operator()(WaitingPassenger a, WaitingPassenger b)
{
    if (a.priority != b.priority)
        return a.priority < b.priority;

    return a.arrival > b.arrival;
}


WaitingList::WaitingList()
{
    arrivalCount = 0;
    loadFromFile();
}


void WaitingList::loadFromFile()
{
    ifstream file("waitinglist.txt");
    string line;

    while (getline(file, line))
    {
        stringstream ss(line);
        string field;
        WaitingPassenger p;

        try
        {
            if (!getline(ss, field, '|')) continue;
            p.id = stoi(field);

            if (!getline(ss, p.name, '|')) continue;

            if (!getline(ss, field, '|')) continue;
            p.trainID = stoi(field);

            if (!getline(ss, field, '|')) continue;
            p.priority = stoi(field);

            if (!getline(ss, field)) continue;
            p.arrival = stoi(field);

            if (p.priority < 1 || p.priority > 3)
                continue;

            pq.push(p);

            if (p.arrival > arrivalCount)
                arrivalCount = p.arrival;
        }
        catch (...)
        {
            cout << "Invalid waiting list record skipped.\n";
        }
    }

    file.close();
}


void WaitingList::saveToFile()
{
    ofstream file("waitinglist.txt");

    if (!file.is_open())
    {
        cout << "Unable to save waiting list!\n";
        return;
    }

    priority_queue<WaitingPassenger,
                   vector<WaitingPassenger>,
                   Compare> temp = pq;

    while (!temp.empty())
    {
        WaitingPassenger p = temp.top();

        file << p.id << "|"
             << p.name << "|"
             << p.trainID << "|"
             << p.priority << "|"
             << p.arrival << endl;

        temp.pop();
    }

    file.close();
}


void WaitingList::addToWaitingList()
{
    WaitingPassenger p;

    cout << "\nEnter Passenger ID: ";
    if (!(cin >> p.id))
    {
        cout << "Invalid Passenger ID!\n";
        cin.clear();
        cin.ignore(1000, '\n');
        return;
    }

    cout << "Enter Passenger Name (no spaces): ";
    if (!(cin >> p.name))
    {
        cout << "Invalid name!\n";
        cin.clear();
        cin.ignore(1000, '\n');
        return;
    }

    cout << "Enter Train ID: ";
    if (!(cin >> p.trainID))
    {
        cout << "Invalid Train ID!\n";
        cin.clear();
        cin.ignore(1000, '\n');
        return;
    }

    cout << "\nPriority:\n";
    cout << "1. Normal\n";
    cout << "2. Senior Citizen\n";
    cout << "3. Urgent\n";
    cout << "Enter priority: ";

    if (!(cin >> p.priority))
    {
        cout << "Please enter 1, 2, or 3.\n";
        cin.clear();
        cin.ignore(1000, '\n');
        return;
    }

    if (p.priority < 1 || p.priority > 3)
    {
        cout << "Invalid priority! Enter 1, 2, or 3.\n";
        return;
    }

    p.arrival = ++arrivalCount;
    pq.push(p);

    saveToFile();

    cout << "Passenger added to waiting list successfully.\n";
}


void WaitingList::removeFromWaitingList()
{
    int id;

    cout << "\nEnter Passenger ID to remove: ";
    if (!(cin >> id))
    {
        cout << "Invalid Passenger ID!\n";
        cin.clear();
        cin.ignore(1000, '\n');
        return;
    }

    priority_queue<WaitingPassenger,
                   vector<WaitingPassenger>,
                   Compare> temp;

    bool found = false;

    while (!pq.empty())
    {
        WaitingPassenger p = pq.top();
        pq.pop();

        if (p.id == id && !found)
            found = true;
        else
            temp.push(p);
    }

    pq = temp;

    if (found)
    {
        saveToFile();
        cout << "Passenger removed successfully.\n";
    }
    else
    {
        cout << "Passenger not found.\n";
    }
}


void WaitingList::displayWaitingList()
{
    if (pq.empty())
    {
        cout << "\nWaiting list is empty.\n";
        return;
    }

    priority_queue<WaitingPassenger,
                   vector<WaitingPassenger>,
                   Compare> temp = pq;

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
    priority_queue<WaitingPassenger,
                   vector<WaitingPassenger>,
                   Compare> temp;

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
        saveToFile();

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
    cout << "Equal priority follows FIFO order.\n";
}


void WaitingList::processAfterCancellation(int trainID)
{
    cout << "\nProcessing cancellation for Train ID: "
         << trainID << endl;

    if (!promotePassenger(trainID))
    {
        cout << "No passenger to promote for this train.\n";
        return;
    }

    cout << "Passenger selected successfully.\n";
    cout << "Next step: allocate the released seat and "
         << "create reservation and ticket.\n";
}


bool WaitingList::getNextPassengerForTrain(
    int trainID, int &passengerID)
{
    priority_queue<WaitingPassenger,
                   vector<WaitingPassenger>,
                   Compare> temp;

    bool found = false;

    while (!pq.empty())
    {
        WaitingPassenger p = pq.top();
        pq.pop();

        if (p.trainID == trainID && !found)
        {
            passengerID = p.id;
            found = true;
        }
        else
        {
            temp.push(p);
        }
    }

    pq = temp;

    if (found)
        saveToFile();

    return found;
}

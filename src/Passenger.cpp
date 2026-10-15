
#include "../include/Passenger.h"

void PassengerManagement::addPassenger()
{
    Passenger p;
    cout << "\nEnter Passenger ID: ";
    cin >> p.passengerID;
    // Check for duplicate ID
    for (int i = 0; i < passengers.size(); i++)
    {
        if (passengers[i].passengerID == p.passengerID)
        {
            cout << "Passenger ID already exists!" << endl;
            return;
        }
    }
    cout << "Enter Name: ";
    cin >> ws;
    getline(cin, p.name);
    cout << "Enter Age: ";
    cin >> p.age;
    cout << "Enter Gender: ";
    cin >> p.gender;
    cout << "Enter Category: ";
    cin >> p.category;
    passengers.push_back(p);
    cout << "\nPassenger added successfully!" << endl;
}

void PassengerManagement::displayPassenger()
{
    if (passengers.empty())
    {
        cout << "\nNo passenger records found!" << endl;
        return;
    }

    cout << "\n--- Passenger Details ---" << endl;

    for (int i = 0; i < passengers.size(); i++)
    {
        cout << "\nPassenger ID: "
             << passengers[i].passengerID << endl;
        cout << "Name: "
             << passengers[i].name << endl;
        cout << "Age: "
             << passengers[i].age << endl;
        cout << "Gender: "
             << passengers[i].gender << endl;
        cout << "Category: "
             << passengers[i].category << endl;
    }
}

void PassengerManagement::searchPassenger()
{
    int id;
    int found = 0;

    cout << "\nEnter Passenger ID to search: ";
    cin >> id;

    for (int i = 0; i < passengers.size(); i++)
    {
        if (passengers[i].passengerID == id)
        {
            cout << "\nPassenger Found!" << endl;

            cout << "Passenger ID: "
                 << passengers[i].passengerID << endl;

            cout << "Name: "
                 << passengers[i].name << endl;

            cout << "Age: "
                 << passengers[i].age << endl;

            cout << "Gender: "
                 << passengers[i].gender << endl;

            cout << "Category: "
                 << passengers[i].category << endl;

            found = 1;
            break;
        }
    }

    if (found == 0)
    {
        cout << "Passenger not found!" << endl;
    }
}

void PassengerManagement::updatePassenger()
{
    int id;
    int found = 0;

    cout << "\nEnter Passenger ID to update: ";
    cin >> id;

    for (int i = 0; i < passengers.size(); i++)
    {
        if (passengers[i].passengerID == id)
        {
            cout << "Enter New Name: ";
            cin >> ws;
            getline(cin, passengers[i].name);

            cout << "Enter New Age: ";
            cin >> passengers[i].age;

            cout << "Enter New Gender: ";
            cin >> passengers[i].gender;

            cout << "Enter New Category: ";
            cin >> passengers[i].category;

            cout << "\nPassenger updated successfully!" << endl;

            found = 1;
            break;
        }
    }

    if (found == 0)
    {
        cout << "Passenger not found!" << endl;
    }
}

void PassengerManagement::deletePassenger()
{
    int id;
    int found = 0;

    cout << "\nEnter Passenger ID to delete: ";
    cin >> id;

    for (int i = 0; i < passengers.size(); i++)
    {
        if (passengers[i].passengerID == id)
        {
            passengers.erase(passengers.begin() + i);

            cout << "Passenger deleted successfully!" << endl;

            found = 1;
            break;
        }
    }

    if (found == 0)
    {
        cout << "Passenger not found!" << endl;
    }
}

void PassengerManagement::checkEligibility()
{
    int id;
    int found = 0;

    cout << "\nEnter Passenger ID: ";
    cin >> id;

    for (int i = 0; i < passengers.size(); i++)
    {
        if (passengers[i].passengerID == id)
        {
            found = 1;

            cout << "\nPassenger: "
                 << passengers[i].name << endl;

            if (passengers[i].age >= 60)
            {
                cout << "Senior Citizen Priority Eligible" << endl;
            }

            if (passengers[i].gender == "Female" ||
                passengers[i].gender == "female")
            {
                cout << "Women Priority Eligible" << endl;
            }

            if (passengers[i].age < 60 &&
                passengers[i].gender != "Female" &&
                passengers[i].gender != "female")
            {
                cout << "No Special Priority" << endl;
            }

            break;
        }
    }

    if (found == 0)
    {
        cout << "Passenger not found!" << endl;
    }
}
Passenger* PassengerManagement::findPassengerByID(int id)
{
    for (int i = 0; i < passengers.size(); i++)
    {
        if (passengers[i].passengerID == id)
        {
            return &passengers[i];
        }
    }

    return nullptr;
}
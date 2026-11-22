#include "../include/Priority.h"

#include <algorithm>
#include <cctype>
#include <limits>

// Constructor
PriorityAllocation::PriorityAllocation()
{
    availableSeats = 0;
    arrivalCounter = 1;
}

// =====================================
// 1. CHECK PRIORITY
// =====================================

int PriorityAllocation::checkPriority(int age, char gender)
{
    gender = toupper(static_cast<unsigned char>(gender));

    if (age >= 60)
        return 3;

    if (gender == 'F')
        return 2;

    return 1;
}

// =====================================
// 2. ADD PASSENGER
// =====================================

void PriorityAllocation::addPassenger()
{
    PriorityPassenger p;

    cout << "\nEnter Passenger ID: ";
    cin >> p.passengerID;

    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid Passenger ID!\n";
        return;
    }

    for (int i = 0; i < passengers.size(); i++)
    {
        if (passengers[i].passengerID == p.passengerID)
        {
            cout << "Passenger ID already exists!\n";
            return;
        }
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter Passenger Name: ";
    getline(cin, p.name);

    if (p.name.empty())
    {
        cout << "Name cannot be empty!\n";
        return;
    }

    cout << "Enter Age: ";
    cin >> p.age;

    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid age!\n";
        return;
    }

    if (p.age < 0)
    {
        cout << "Invalid age!\n";
        return;
    }

    cout << "Enter Gender (M/F): ";
    cin >> p.gender;

    p.gender = toupper(static_cast<unsigned char>(p.gender));

    if (p.gender != 'M' && p.gender != 'F')
    {
        cout << "Invalid gender! Enter M or F.\n";
        return;
    }

    p.priority = checkPriority(p.age, p.gender);

    p.arrivalOrder = arrivalCounter++;

    p.allocated = false;

    passengers.push_back(p);

    cout << "\nPassenger added successfully!\n";

    cout << "Priority Level: " << p.priority << endl;
}

// =====================================
// 3. HANDLE WOMEN PRIORITY
// =====================================

void PriorityAllocation::handleWomenPriority()
{
    for (auto &p : passengers)
    {
        if (!p.allocated &&
            p.gender == 'F' &&
            p.age < 60)
        {
            p.priority = 2;
        }
    }

    cout << "\nWomen priority updated!\n";
}

// =====================================
// 4. HANDLE SENIOR CITIZEN
// =====================================

void PriorityAllocation::handleSeniorCitizen()
{
    for (auto &p : passengers)
    {
        if (!p.allocated && p.age >= 60)
        {
            p.priority = 3;
        }
    }

    cout << "\nSenior citizen priority updated!\n";
}

// =====================================
// 5. GET HIGHEST PRIORITY PASSENGER
// =====================================

int PriorityAllocation::getEligiblePassenger()
{
    int selectedIndex = -1;

    for (int i = 0; i < passengers.size(); i++)
    {
        if (passengers[i].allocated)
            continue;

        if (selectedIndex == -1)
        {
            selectedIndex = i;
        }
        else if (passengers[i].priority >
                 passengers[selectedIndex].priority)
        {
            selectedIndex = i;
        }
        else if (passengers[i].priority ==
                     passengers[selectedIndex].priority &&
                 passengers[i].arrivalOrder <
                     passengers[selectedIndex].arrivalOrder)
        {
            selectedIndex = i;
        }
    }

    return selectedIndex;
}

// =====================================
// 6. ALLOCATE PRIORITY SEAT
// =====================================

void PriorityAllocation::allocatePrioritySeat()
{
    if (availableSeats <= 0)
    {
        cout << "\nNo seats available!\n";
        return;
    }

    int index = getEligiblePassenger();

    if (index == -1)
    {
        cout << "\nNo eligible passengers in waiting list!\n";
        return;
    }

    passengers[index].allocated = true;

    availableSeats--;

    cout << "\nSeat allocated successfully!\n";

    cout << "Passenger ID: "
         << passengers[index].passengerID << endl;

    cout << "Passenger Name: "
         << passengers[index].name << endl;

    cout << "Priority: "
         << passengers[index].priority << endl;

    cout << "Remaining Seats: "
         << availableSeats << endl;
}

// =====================================
// 7. DISPLAY WAITING LIST
// =====================================

void PriorityAllocation::displayWaitingList()
{
    cout << "\n========== WAITING LIST ==========\n";

    bool found = false;

    for (const auto &p : passengers)
    {
        if (!p.allocated)
        {
            found = true;

            cout << "\nPassenger ID: " << p.passengerID;
            cout << "\nName: " << p.name;
            cout << "\nAge: " << p.age;
            cout << "\nGender: " << p.gender;
            cout << "\nPriority: " << p.priority;
            cout << "\nArrival Order: " << p.arrivalOrder;

            cout << "\n----------------------------------\n";
        }
    }

    if (!found)
        cout << "Waiting list is empty!\n";
}
void PriorityAllocation::loadPassengers(PassengerManagement &pm)
{
    vector<Passenger> &data = pm.getPassengers();

    for (int i = 0; i < data.size(); i++)
    {
        bool found = false;

        for (int j = 0; j < passengers.size(); j++)
        {
            if (passengers[j].passengerID == data[i].passengerID)
            {
                found = true;
                break;
            }
        }

        if (found == false)
        {
            PriorityPassenger p;

            p.passengerID = data[i].passengerID;
            p.name = data[i].name;
            p.age = data[i].age;

            if (data[i].gender == "Female" ||
                data[i].gender == "female" ||
                data[i].gender == "F" ||
                data[i].gender == "f")
            {
                p.gender = 'F';
            }
            else
            {
                p.gender = 'M';
            }

            p.arrivalOrder = arrivalCounter++;
            p.priority = checkPriority(p.age, p.gender);
            p.allocated = false;

            passengers.push_back(p);
        }
    }

    cout << "\nPassengers loaded from Passenger Management successfully!\n";
}

// =====================================
// 8. MAIN MENU
// =====================================

void PriorityAllocation::run()
{
    int choice = -1;

    do
    {
        cout << "\n================================\n";
        cout << "       PRIORITY ALLOCATION\n";
        cout << "================================\n";

        cout << "1. Add Passenger\n";
        cout << "2. Check Priority\n";
        cout << "3. Display Waiting List\n";
        cout << "4. Allocate Priority Seat\n";
        cout << "5. Handle Women Priority\n";
        cout << "6. Handle Senior Citizen\n";
        cout << "7. Set Available Seats\n";
        cout << "0. Back to Main Menu\n";

        cout << "\nEnter your choice: ";
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Invalid input!\n";
            choice = -1;
            continue;
        }

        switch (choice)
        {
        case 1:
            addPassenger();
            break;

        case 2:
        {
            int age;
            char gender;

            cout << "Enter Age: ";
            cin >> age;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid age!\n";
                break;
            }

            if (age < 0)
            {
                cout << "Invalid age!\n";
                break;
            }

            cout << "Enter Gender (M/F): ";
            cin >> gender;

            gender = toupper(static_cast<unsigned char>(gender));

            if (gender != 'M' && gender != 'F')
            {
                cout << "Invalid gender!\n";
                break;
            }

            cout << "Priority Level: "
                 << checkPriority(age, gender) << endl;

            break;
        }

        case 3:
            displayWaitingList();
            break;

        case 4:
            allocatePrioritySeat();
            break;

        case 5:
            handleWomenPriority();
            break;

        case 6:
            handleSeniorCitizen();
            break;

        case 7:
            cout << "Enter available seats: ";
            cin >> availableSeats;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                availableSeats = 0;
                cout << "Invalid seat count!\n";
                break;
            }

            if (availableSeats < 0)
            {
                availableSeats = 0;
                cout << "Invalid seat count!\n";
            }
            else
            {
                cout << "Available seats updated successfully!\n";
            }

            break;

        case 0:
            cout << "Returning to Main Menu...\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != 0);
}
int main()
{
    PriorityAllocation pa;
    pa.run();

    return 0;
}

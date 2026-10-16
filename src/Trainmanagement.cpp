#include "TrainManagement.h"
#include <iostream>
#include <string>
using namespace std;

// Constructor
TrainManagement::TrainManagement()
{
head = NULL;
}

// 1. ADD TRAIN
void TrainManagement::addTrain()
{
int number, seats;
string name, src, dest;


cout << "\nEnter Train Number: ";
cin >> number;

// Check for duplicate train number
TrainNode* temp = head;

while (temp != NULL)
{
    if (temp->data.getTrainNumber() == number)
    {
        cout << "Train already exists!\n";
        return;
    }

    temp = temp->next;
}

cout << "Enter Train Name: ";
cin.ignore();
getline(cin, name);

cout << "Enter Source: ";
getline(cin, src);

cout << "Enter Destination: ";
getline(cin, dest);

cout << "Enter Total Seats: ";
cin >> seats;

if (seats <= 0)
{
    cout << "Invalid number of seats!\n";
    return;
}

Train t(number, name, src, dest, seats);

TrainNode* newNode = new TrainNode(t);

// If the list is empty
if (head == NULL)
{
    head = newNode;
}
else
{
    temp = head;

    // Traverse to the last node
    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    // Link the new node
    temp->next = newNode;
}

cout << "Train added successfully!\n";


}

// 2. UPDATE TRAIN
void TrainManagement::updateTrain()
{
int number;


cout << "\nEnter Train Number to Update: ";
cin >> number;

TrainNode* temp = head;

while (temp != NULL)
{
    if (temp->data.getTrainNumber() == number)
    {
        string name, src, dest;

        cout << "Enter New Train Name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter New Source: ";
        getline(cin, src);

        cout << "Enter New Destination: ";
        getline(cin, dest);

        // Preserve the original train number and seat count
        int total = temp->data.getTotalSeats();
        int available = temp->data.getAvailableSeats();

        Train updatedTrain(
            number, name, src, dest, total
        );

        // Preserve the current availability
        int booked = total - available;

        for (int i = 0; i < booked; i++)
        {
            updatedTrain.reserveSeat();
        }

        temp->data = updatedTrain;

        cout << "Train updated successfully!\n";
        return;
    }

    temp = temp->next;
}

cout << "Train not found!\n";


}

// 3. DELETE TRAIN
void TrainManagement::deleteTrain()
{
int number;


cout << "\nEnter Train Number to Delete: ";
cin >> number;

TrainNode* temp = head;
TrainNode* prev = NULL;

// Search for the train
while (temp != NULL &&
       temp->data.getTrainNumber() != number)
{
    prev = temp;
    temp = temp->next;
}

// Train not found
if (temp == NULL)
{
    cout << "Train not found!\n";
    return;
}

// Case 1: Delete the first node
if (prev == NULL)
{
    head = temp->next;
}
else
{
    // Case 2: Delete a middle or last node
    prev->next = temp->next;
}

delete temp;

cout << "Train deleted successfully!\n";


}

// 4. SEARCH TRAIN
void TrainManagement::searchTrain()
{
int number;


cout << "\nEnter Train Number to Search: ";
cin >> number;

TrainNode* temp = head;

while (temp != NULL)
{
    if (temp->data.getTrainNumber() == number)
    {
        cout << "\nTrain Found!\n";
        temp->data.displayTrain();
        return;
    }

    temp = temp->next;
}

cout << "Train not found!\n";


}

// 5. DISPLAY ALL TRAINS
void TrainManagement::displayTrain()
{
if (head == NULL)
{
cout << "\nNo trains available!\n";
return;
}


TrainNode* temp = head;

cout << "\n===== ALL TRAINS =====\n";

while (temp != NULL)
{
    temp->data.displayTrain();

    cout << "----------------------\n";

    temp = temp->next;
}


}

// 6. CHECK SEAT AVAILABILITY
void TrainManagement::checkAvailability()
{
int number;


cout << "\nEnter Train Number: ";
cin >> number;

TrainNode* temp = head;

while (temp != NULL)
{
    if (temp->data.getTrainNumber() == number)
    {
        cout << "\nTrain: "
             << temp->data.getTrainName() << endl;

        temp->data.checkAvailability();
        return;
    }

    temp = temp->next;
}

cout << "Train not found!\n";


}
Train* TrainManagement::findTrainByNumber(int number)
{
    TrainNode* temp = head;

    while (temp != NULL)
    {
        if (temp->data.getTrainNumber() == number)
        {
            return &(temp->data);
        }

        temp = temp->next;
    }

    return NULL;
} 

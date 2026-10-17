#include <iostream>
#include "Train.h"

using namespace std;

int main()
{
// Create a train object
Train t1(12001, "Dehradun Express", "Dehradun", "Delhi", 100);

// Display train details
t1.displayTrain();

// Check seat availability
if (t1.checkAvailability())
{
    cout << "\nSeats are available." << endl;
}
else
{
    cout << "\nNo seats available." << endl;
}

// Reserve a seat
cout << "\nBooking a seat..." << endl;
t1.reserveSeat();

// Display updated details
t1.displayTrain();

// Release a seat after cancellation
cout << "\nCancelling a booking..." << endl;
t1.releaseSeat();

// Display final details
t1.displayTrain();

return 0;

}

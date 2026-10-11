#include<iostream>
#include"Train.h"
using namespace std;
Train:: Train()
{
trainNumber = 0;
trainName = "Not Assigned";
source = "Not Assigned";
destination = "Not Assigned";
totalSeats = 0;
availableSeats = 0;
}
Train:: Train(int number,string name,string src,string dest,int seats)
{
trainNumber =  number;
trainName = name;
source = src;
destination = dest;
if (seats >= 0)
{
    totalSeats = seats;
    availableSeats = seats;
}
else
{
    totalSeats = 0;
    availableSeats = 0;
}

}
int Train::getTrainNumber()
{
return trainNumber;
}

string Train::getTrainName() 
{
return trainName;
}

string Train::getSource() 
{
return source;
}

string Train::getDestination() 
{
return destination;
}

int Train::getTotalSeats() 
{
return totalSeats;
}

int Train::getAvailableSeats() 
{
return availableSeats;
}
bool Train::checkAvailability() 
{
return availableSeats > 0;
}
void Train::reserveSeat()
{
if (availableSeats > 0)
{
availableSeats--;
cout << "Seat reserved successfully!" << endl;
cout << "Available seats: " << availableSeats << endl;
}
else
{
cout << "Sorry! No seats available on this train." << endl;
}
}
void Train::releaseSeat()
{
if (availableSeats < totalSeats)
{
availableSeats++;
cout << "Seat released successfully!" << endl;
cout << "Available seats: " << availableSeats << endl;
}
else
{
cout << "All seats are already available." << endl;
}
}
void Train::displayTrain() 
{
cout << "\n************= TRAIN DETAILS =************" << endl;
cout << "Train Number : " << trainNumber << endl;
cout << "Train Name : " << trainName << endl;
cout << "Source : " << source << endl;
cout << "Destination : " << destination << endl;
cout << "Total Seats : " << totalSeats << endl;
cout << "Available Seats : " << availableSeats << endl;
}

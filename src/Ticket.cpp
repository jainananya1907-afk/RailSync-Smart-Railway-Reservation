#include "Ticket.h"

long long Ticket::nextPNR = 1000000000LL;

Ticket::Ticket()
{
    ticketNumber = 0;
    pnr = 0;
    passengerName = "";
    trainNumber = 0;
    source = "";
    destination = "";
    journeyDate = "";
    status = "Waiting List";
}

Ticket::Ticket(int ticketNo, long long pnrNo,
               string name, int trainNo,
               string src, string dest,
               string date, string ticketStatus)
{
    ticketNumber = ticketNo;
    pnr = pnrNo;
    passengerName = name;
    trainNumber = trainNo;
    source = src;
    destination = dest;
    journeyDate = date;
    status = ticketStatus;
}

long long Ticket::generatePNR()
{
    nextPNR++;
    return nextPNR;
}

int Ticket::getTicketNumber()
{
    return ticketNumber;
}

long long Ticket::getPNR()
{
    return pnr;
}

string Ticket::getPassengerName()
{
    return passengerName;
}

int Ticket::getTrainNumber()
{
    return trainNumber;
}

string Ticket::getSource()
{
    return source;
}

string Ticket::getDestination()
{
    return destination;
}

string Ticket::getJourneyDate()
{
    return journeyDate;
}

string Ticket::getStatus()
{
    return status;
}

void Ticket::updateTicketStatus(string newStatus)
{
    if (newStatus == "Confirmed" ||
        newStatus == "Waiting List" ||
        newStatus == "Cancelled")
    {
        status = newStatus;
        cout << "\nTicket status updated successfully.\n";
    }
    else
    {
        cout << "\nInvalid ticket status!\n";
    }
}

void Ticket::displayTicket()
{
    cout << "\nTicket Number: " << ticketNumber;
    cout << "\nPNR Number: " << pnr;
    cout << "\nPassenger Name: " << passengerName;
    cout << "\nTrain Number: " << trainNumber;
    cout << "\nSource: " << source;
    cout << "\nDestination: " << destination;
    cout << "\nJourney Date: " << journeyDate;
    cout << "\nStatus: " << status << endl;
}

void Ticket::printTicket()
{
    cout << "\n========================================\n";
    cout << "          SMART RAIL RESERVATION\n";
    cout << "               E-TICKET\n";
    cout << "========================================\n";

    cout << "Ticket Number : " << ticketNumber << endl;
    cout << "PNR Number    : " << pnr << endl;
    cout << "Passenger     : " << passengerName << endl;
    cout << "Train Number  : " << trainNumber << endl;
    cout << "From          : " << source << endl;
    cout << "To            : " << destination << endl;
    cout << "Journey Date  : " << journeyDate << endl;
    cout << "Status        : " << status << endl;

    cout << "========================================\n";
}

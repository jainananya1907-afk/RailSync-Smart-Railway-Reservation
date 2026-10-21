#ifndef Ticket_h
#define Ticket_h


#include <iostream>
#include <string>
using namespace std;

class Ticket
{
private:
    int ticketNumber;
    long long pnr;

    string passengerName;
    int trainNumber;

    string source;
    string destination;
    string journeyDate;
    string status;

    static long long nextPNR;

public:
    Ticket();

    Ticket(int ticketNo, long long pnrNo,
           string name, int trainNo,
           string src, string dest,
           string date, string ticketStatus);

    static long long generatePNR();

    int getTicketNumber();
    long long getPNR();
    string getPassengerName();
    int getTrainNumber();
    string getSource();
    string getDestination();
    string getJourneyDate();
    string getStatus();

    void updateTicketStatus(string newStatus);

    void displayTicket();
    void printTicket();
};
#endif

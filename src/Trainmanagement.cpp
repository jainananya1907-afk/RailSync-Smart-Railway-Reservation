
#include <iostream>
#include <fstream>
#include <sstream>
#include "TicketManagement.h"

using namespace std;

TicketManagement::TicketManagement()
{
    head = NULL;
    ticketCounter = 1000;
    loadTicketsFromFile();
}

TicketManagement::~TicketManagement()
{
    Node* current = head;

    while (current != NULL)
    {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
}

void TicketManagement::loadTicketsFromFile()
{
    ifstream file("tickets.txt");
    string line;

    long long maxPNR = 1000000000LL;

    while (getline(file, line))
    {
        stringstream ss(line);
        string ticketNoStr, pnrStr, name, trainStr;
        string src, dest, date, status;

        getline(ss, ticketNoStr, '|');
        getline(ss, pnrStr, '|');
        getline(ss, name, '|');
        getline(ss, trainStr, '|');
        getline(ss, src, '|');
        getline(ss, dest, '|');
        getline(ss, date, '|');
        getline(ss, status, '|');

        if (ticketNoStr.empty() || pnrStr.empty())
            continue;

        int ticketNo = stoi(ticketNoStr);
        long long pnr = stoll(pnrStr);
        int trainNo = stoi(trainStr);

        Ticket t(ticketNo, pnr, name, trainNo,
                 src, dest, date, status);

        Node* newNode = new Node(t);

        if (head == NULL)
            head = newNode;
        else
        {
            Node* temp = head;
            while (temp->next != NULL)
                temp = temp->next;

            temp->next = newNode;
        }

        if (ticketNo > ticketCounter)
            ticketCounter = ticketNo;

        if (pnr > maxPNR)
            maxPNR = pnr;
    }

    file.close();

    // Advance PNR generator beyond previously saved PNRs.
    while (Ticket::generatePNR() <= maxPNR)
    {
    }
}

void TicketManagement::saveTicketsToFile()
{
    ofstream file("tickets.txt");

    Node* temp = head;

    while (temp != NULL)
    {
        Ticket t = temp->ticket;

        file << t.getTicketNumber() << "|"
             << t.getPNR() << "|"
             << t.getPassengerName() << "|"
             << t.getTrainNumber() << "|"
             << t.getSource() << "|"
             << t.getDestination() << "|"
             << t.getJourneyDate() << "|"
             << t.getStatus() << "\n";

        temp = temp->next;
    }

    file.close();
}

void TicketManagement::generateTicket()
{
    int trainNo;
    string name, src, dest, date;

    cout << "\nEnter Passenger Name: ";
    getline(cin >> ws, name);

    cout << "Enter Train Number: ";
    cin >> trainNo;

    cout << "Enter Source Station: ";
    getline(cin >> ws, src);

    cout << "Enter Destination Station: ";
    getline(cin >> ws, dest);

    cout << "Enter Journey Date (DD-MM-YYYY): ";
    getline(cin >> ws, date);

    long long pnr = Ticket::generatePNR();

    Ticket newTicket(++ticketCounter, pnr, name, trainNo,
                     src, dest, date, "Confirmed");

    Node* newNode = new Node(newTicket);

    if (head == NULL)
        head = newNode;
    else
    {
        Node* temp = head;
        while (temp->next != NULL)
            temp = temp->next;

        temp->next = newNode;
    }

    saveTicketsToFile();

    cout << "\nTicket generated successfully!\n";
    cout << "Your Ticket Number: " << ticketCounter << endl;
    cout << "Your PNR Number: " << pnr << endl;

    newTicket.printTicket();
}

long long TicketManagement::generateTicketFromReservation(
    string name, int trainNo, int seatNo)
{
    string src, dest, date;

    cout << "Enter Source Station: ";
    getline(cin >> ws, src);

    cout << "Enter Destination Station: ";
    getline(cin >> ws, dest);

    cout << "Enter Journey Date (DD-MM-YYYY): ";
    getline(cin >> ws, date);

    long long pnr = Ticket::generatePNR();

    Ticket newTicket(++ticketCounter, pnr, name, trainNo,
                     src, dest, date, "Confirmed");

    Node* newNode = new Node(newTicket);

    if (head == NULL)
        head = newNode;
    else
    {
        Node* temp = head;
        while (temp->next != NULL)
            temp = temp->next;

        temp->next = newNode;
    }

    saveTicketsToFile();

    cout << "\nTicket generated successfully!\n";
    cout << "Ticket Number: " << ticketCounter << endl;
    cout << "PNR Number: " << pnr << endl;
    cout << "Allocated Seat Number: " << seatNo << endl;

    newTicket.printTicket();
    return pnr;
}

Ticket* TicketManagement::searchByPNR(long long pnr)
{
    Node* temp = head;

    while (temp != NULL)
    {
        if (temp->ticket.getPNR() == pnr)
            return &(temp->ticket);

        temp = temp->next;
    }

    return NULL;
}

void TicketManagement::displayTicket(long long pnr)
{
    Ticket* ticket = searchByPNR(pnr);

    if (ticket != NULL)
        ticket->displayTicket();
    else
        cout << "\nTicket not found!\n";
}

void TicketManagement::printTicket(long long pnr)
{
    Ticket* ticket = searchByPNR(pnr);

    if (ticket != NULL)
        ticket->printTicket();
    else
        cout << "\nTicket not found!\n";
}

void TicketManagement::updateTicketStatus(long long pnr, string newStatus)
{
    Ticket* ticket = searchByPNR(pnr);

    if (ticket != NULL)
    {
        ticket->updateTicketStatus(newStatus);
        saveTicketsToFile();
        cout << "\nTicket status updated!\n";
    }
    else
        cout << "\nTicket not found!\n";
}

void TicketManagement::displayAllTickets()
{
    if (head == NULL)
    {
        cout << "\nNo tickets available.\n";
        return;
    }

    Node* temp = head;

    while (temp != NULL)
    {
        temp->ticket.displayTicket();
        cout << "\n----------------------------------------\n";
        temp = temp->next;
    }
}

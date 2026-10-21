
#include <iostream>
#include "include/Passenger.h"
#include "include/Trainmanagement.h"
#include "include/Seat.h"
#include "include/Reservation.h"
#include "include/Ticketmanagement.h"
#include "include/WaitingList.h"

using namespace std;

int main()
{
    // Create objects for all modules
    PassengerManagement passengerManager;
    TrainManagement trainManager;
    SeatAvailability seatManager;
    Reservation reservationManager;
    TicketManagement ticketManager;
    WaitingList waitingList;

    int choice;

    do
    {
        cout << "\n========================================\n";
        cout << "      SMART RAIL RESERVATION SYSTEM\n";
        cout << "========================================\n";

        cout << "1. Passenger Management\n";
        cout << "2. Train Management\n";
        cout << "3. Seat Availability Management\n";
        cout << "4. Reservation Management\n";
        cout << "5. Ticket and PNR Management\n";
        cout << "6. Waiting List Management\n";
        cout << "0. Exit\n";

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
            // =================================
            // 1. PASSENGER MANAGEMENT
            // =================================
            case 1:
            {
                int option;

                do
                {
                    cout << "\n===== PASSENGER MANAGEMENT =====\n";
                    cout << "1. Add Passenger\n";
                    cout << "2. Display All Passengers\n";
                    cout << "3. Search Passenger\n";
                    cout << "4. Update Passenger\n";
                    cout << "5. Delete Passenger\n";
                    cout << "6. Check Passenger Eligibility\n";
                    cout << "0. Back to Main Menu\n";

                    cout << "Enter your choice: ";
                    cin >> option;

                    switch (option)
                    {
                        case 1:
                            passengerManager.addPassenger();
                            break;

                        case 2:
                            passengerManager.displayPassenger();
                            break;

                        case 3:
                            passengerManager.searchPassenger();
                            break;

                        case 4:
                            passengerManager.updatePassenger();
                            break;

                        case 5:
                            passengerManager.deletePassenger();
                            break;

                        case 6:
                            passengerManager.checkEligibility();
                            break;

                        case 0:
                            cout << "Returning to Main Menu...\n";
                            break;

                        default:
                            cout << "Invalid choice!\n";
                    }

                } while (option != 0);

                break;
            }

            // =================================
            // 2. TRAIN MANAGEMENT
            // =================================
            case 2:
            {
                int option;

                do
                {
                    cout << "\n===== TRAIN MANAGEMENT =====\n";
                    cout << "1. Add Train\n";
                    cout << "2. Update Train\n";
                    cout << "3. Delete Train\n";
                    cout << "4. Search Train\n";
                    cout << "5. Display All Trains\n";
                    cout << "6. Check Train Seat Availability\n";
                    cout << "0. Back to Main Menu\n";

                    cout << "Enter your choice: ";
                    cin >> option;

                    switch (option)
                    {
                        case 1:
                            trainManager.addTrain();
                            break;

                        case 2:
                            trainManager.updateTrain();
                            break;

                        case 3:
                            trainManager.deleteTrain();
                            break;

                        case 4:
                            trainManager.searchTrain();
                            break;

                        case 5:
                            trainManager.displayTrain();
                            break;

                        case 6:
                            trainManager.checkAvailability();
                            break;

                        case 0:
                            cout << "Returning to Main Menu...\n";
                            break;

                        default:
                            cout << "Invalid choice!\n";
                    }

                } while (option != 0);

                break;
            }

            // =================================
            // 3. SEAT AVAILABILITY MANAGEMENT
            // =================================
            case 3:
            {
                int option;

                do
                {
                    cout << "\n===== SEAT AVAILABILITY MANAGEMENT =====\n";
                    cout << "1. Add Train Seat Record\n";
                    cout << "2. Get Seat Availability\n";
                    cout << "3. Update Total Seat Count\n";
                    cout << "4. Check Seat Class\n";
                    cout << "5. Allocate Seat\n";
                    cout << "6. Release Seat\n";
                    cout << "0. Back to Main Menu\n";

                    cout << "Enter your choice: ";
                    cin >> option;

                    switch (option)
                    {
                        case 1:
                            seatManager.addTrain();
                            break;

                        case 2:
                            seatManager.getSeatAvailability();
                            break;

                        case 3:
                            seatManager.updateSeatCount();
                            break;

                        case 4:
                            seatManager.checkSeatClass();
                            break;

                        case 5:
                            seatManager.allocateSeat();
                            break;

                        case 6:
                            seatManager.releaseSeat();
                            break;

                        case 0:
                            cout << "Returning to Main Menu...\n";
                            break;

                        default:
                            cout << "Invalid choice!\n";
                    }

                } while (option != 0);

                break;
            }

            // =================================
            // 4. RESERVATION MANAGEMENT
            // =================================
            case 4:
            {
                int option;

                do
                {
                    cout << "\n===== RESERVATION MANAGEMENT =====\n";
                    cout << "1. Book Reservation\n";
                    cout << "2. Confirm Reservation\n";
                    cout << "3. Cancel Reservation\n";
                    cout << "4. Check Reservation Availability\n";
                    cout << "5. Apply Passenger Priority\n";
                    cout << "6. Update Seat Status\n";
                    cout << "0. Back to Main Menu\n";

                    cout << "Enter your choice: ";
                    cin >> option;

                    switch (option)
                    {
                        case 1:
                            reservationManager.bookTicket(
                                passengerManager
                            );
                            break;

                        case 2:
                            reservationManager.confirmReservation(
                                passengerManager,
                                ticketManager
                            );
                            break;

                        case 3:
                            reservationManager.cancelTicket(
                                ticketManager,
                                passengerManager,
                                waitingList
                            );
                            break;

                        case 4:
                            reservationManager.checkAvailability();
                            break;

                        case 5:
                            reservationManager.applyPriority(
                                passengerManager
                            );
                            break;

                        case 6:
                            reservationManager.updateSeatStatus();
                            break;

                        case 0:
                            cout << "Returning to Main Menu...\n";
                            break;

                        default:
                            cout << "Invalid choice!\n";
                    }

                } while (option != 0);

                break;
            }

            // =================================
            // 5. TICKET AND PNR MANAGEMENT
            // =================================
            case 5:
            {
                int option;

                do
                {
                    cout << "\n===== TICKET AND PNR MANAGEMENT =====\n";
                    cout << "1. Generate Ticket\n";
                    cout << "2. Search Ticket by PNR\n";
                    cout << "3. Display Ticket\n";
                    cout << "4. Print Ticket\n";
                    cout << "5. Update Ticket Status\n";
                    cout << "6. Display All Tickets\n";
                    cout << "0. Back to Main Menu\n";

                    cout << "Enter your choice: ";
                    cin >> option;

                    switch (option)
                    {
                        case 1:
                            ticketManager.generateTicket();
                            break;

                        case 2:
                        {
                            long long pnr;

                            cout << "Enter PNR: ";
                            cin >> pnr;

                            Ticket* ticket =
                                ticketManager.searchByPNR(pnr);

                            if (ticket != nullptr)
                            {
                                cout << "\nTicket found!\n";
                                ticket->displayTicket();
                            }
                            else
                            {
                                cout << "Ticket not found!\n";
                            }

                            break;
                        }

                        case 3:
                        {
                            long long pnr;

                            cout << "Enter PNR: ";
                            cin >> pnr;

                            ticketManager.displayTicket(pnr);
                            break;
                        }

                        case 4:
                        {
                            long long pnr;

                            cout << "Enter PNR: ";
                            cin >> pnr;

                            ticketManager.printTicket(pnr);
                            break;
                        }

                        case 5:
                        {
                            long long pnr;
                            string status;

                            cout << "Enter PNR: ";
                            cin >> pnr;

                            cout << "Enter New Status: ";
                            cin >> status;

                            ticketManager.updateTicketStatus(
                                pnr, status
                            );

                            break;
                        }

                        case 6:
                            ticketManager.displayAllTickets();
                            break;

                        case 0:
                            cout << "Returning to Main Menu...\n";
                            break;

                        default:
                            cout << "Invalid choice!\n";
                    }

                } while (option != 0);

                break;
            }

            // =================================
            // 6. WAITING LIST MANAGEMENT
            // =================================
            case 6:
            {
                int option;

                do
                {
                    cout << "\n===== WAITING LIST MANAGEMENT =====\n";
                    cout << "1. Add Passenger to Waiting List\n";
                    cout << "2. Remove Passenger from Waiting List\n";
                    cout << "3. Display Waiting List\n";
                    cout << "4. Process After Cancellation\n";
                    cout << "5. Maintain Waiting List Order\n";
                    cout << "0. Back to Main Menu\n";

                    cout << "Enter your choice: ";
                    cin >> option;

                    switch (option)
                    {
                        case 1:
                            waitingList.addToWaitingList();
                            break;

                        case 2:
                            waitingList.removeFromWaitingList();
                            break;

                        case 3:
                            waitingList.displayWaitingList();
                            break;

                        case 4:
                        {
                            int trainID;

                            cout << "Enter Train ID: ";
                            cin >> trainID;

                            waitingList.processAfterCancellation(
                                trainID
                            );

                            break;
                        }

                        case 5:
                            waitingList.maintainOrder();
                            break;

                        case 0:
                            cout << "Returning to Main Menu...\n";
                            break;

                        default:
                            cout << "Invalid choice!\n";
                    }

                } while (option != 0);

                break;
            }

            // =================================
            // EXIT
            // =================================
            case 0:
                cout << "\nThank you for using Smart Rail Reservation System!\n";
                break;

            default:
                cout << "Invalid choice! Please try again.\n";
        }

    } while (choice != 0);

    return 0;
}

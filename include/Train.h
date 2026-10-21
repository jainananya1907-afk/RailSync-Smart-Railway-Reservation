#ifndef Train_h
#define Train_h
#include <string>
using namespace std;

class Train
{
private:
    int trainNumber;
    string trainName;
    string source;
    string destination;
    int totalSeats;
    int availableSeats;

public:
void setAvailableSeats(int seats);
    Train();
    Train(int number, string name, string src, string dest, int seats);
    int getTrainNumber();
    string getTrainName();
    string getSource();
    string getDestination();
    int getTotalSeats();
    int getAvailableSeats();

    bool checkAvailability();
    void reserveSeat();
    void releaseSeat();

    void displayTrain();
};
#endif

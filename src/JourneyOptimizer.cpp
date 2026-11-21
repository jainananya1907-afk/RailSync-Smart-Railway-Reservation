#include "../include/JourneyOptimizer.h"
#include "../include/Trainmanagement.h"
#include <cctype>
#include <algorithm>
#include <queue>
#include <limits>
#include <functional>

Journey::Journey()
{
}

// Convert station names to lowercase for comparison
string Journey::normalize(string name)
{
    transform(name.begin(), name.end(), name.begin(),
              [](unsigned char c)
              {
                  return tolower(c);
              });

    return name;
}

// Load stations and connections dynamically
void Journey::loadFromTrainManagement(TrainManagement& tm)
{
    stations.clear();
    graph.clear();

    TrainNode* ptr = tm.getHead();

    while (ptr != NULL)
    {
        if (ptr->data != NULL)
        {
            Train* t = ptr->data;

            string source = t->getSource();
            string destination = t->getDestination();

            string s = normalize(source);
            string d = normalize(destination);

            stations[s] = source;
            stations[d] = destination;

            JourneyEdge edge;

            edge.destination = d;
            edge.trainNumber = to_string(t->getTrainNumber());
            edge.trainName = t->getTrainName();
            edge.travelTime = t->getTravelTime();

            if (edge.travelTime <= 0)
                edge.travelTime = 1;

            graph[s].push_back(edge);
        }

        ptr = ptr->next;
    }
}

// Display all available stations
void Journey::displayStations()
{
    cout << "\n========== AVAILABLE STATIONS ==========\n";

    if (stations.empty())
    {
        cout << "No stations available.\n";
        return;
    }

    for (auto it = stations.begin(); it != stations.end(); it++)
    {
        cout << it->second << endl;
    }
}

// Display all train connections
void Journey::displayTrainConnections()
{
    cout << "\n========== TRAIN CONNECTIONS ==========\n";

    if (graph.empty())
    {
        cout << "No train connections available.\n";
        return;
    }

    for (auto it = graph.begin(); it != graph.end(); it++)
    {
        cout << "\nFrom: " << stations[it->first] << endl;

        for (int i = 0; i < it->second.size(); i++)
        {
            JourneyEdge edge = it->second[i];

            cout << "To: " << stations[edge.destination]
                 << " | Train: " << edge.trainNumber
                 << " | " << edge.trainName
                 << " | Travel Time: " << edge.travelTime
                 << " hours\n";
        }
    }
}

// Display journey path
void Journey::displayPath(vector<string> path,
                          vector<JourneyEdge> trains,
                          int totalTime)
{
    cout << "\n========== JOURNEY DETAILS ==========\n";

    if (path.empty())
    {
        cout << "No journey found.\n";
        return;
    }

    cout << "Source: " << stations[path[0]] << endl;

    for (int i = 0; i < trains.size(); i++)
    {
        cout << "\nTrain Number: " << trains[i].trainNumber;
        cout << "\nTrain Name: " << trains[i].trainName;
        cout << "\nFrom: " << stations[path[i]];
        cout << "\nTo: " << stations[path[i + 1]];
        cout << "\nTravel Time: " << trains[i].travelTime
             << " hours\n";
    }

    cout << "\nDestination: " << stations[path.back()] << endl;
    cout << "Total Travel Time: " << totalTime << " hours\n";
    cout << "Total Train Changes: "
         << (trains.empty() ? 0 : trains.size() - 1) << endl;
}

// Plan journey
void Journey::planJourney()
{
    string source, destination;

    cout << "\nEnter Source Station: ";
    cin >> ws;
    getline(cin, source);

    cout << "Enter Destination Station: ";
    getline(cin, destination);

    string s = normalize(source);
    string d = normalize(destination);

    if (stations.find(s) == stations.end() ||
        stations.find(d) == stations.end())
    {
        cout << "Invalid station name.\n";
        return;
    }

    if (s == d)
    {
        cout << "Source and destination are same.\n";
        return;
    }

    cout << "\nJourney: " << stations[s]
         << " to " << stations[d] << endl;

    cout << "Select Fastest Journey or Minimum Transfer Journey "
         << "to calculate your route.\n";
}

// Find fastest journey using Dijkstra
void Journey::fastestJourney()
{
    string source, destination;

    cout << "\nEnter Source Station: ";
    cin >> ws;
    getline(cin, source);

    cout << "Enter Destination Station: ";
    getline(cin, destination);

    string s = normalize(source);
    string d = normalize(destination);

    if (stations.find(s) == stations.end() ||
        stations.find(d) == stations.end())
    {
        cout << "Invalid station name.\n";
        return;
    }

    if (s == d)
    {
        cout << "Source and destination are same.\n";
        return;
    }

    unordered_map<string, int> dist;
    unordered_map<string, string> parent;
    unordered_map<string, JourneyEdge> parentEdge;

    for (auto it = stations.begin(); it != stations.end(); it++)
    {
        dist[it->first] = numeric_limits<int>::max();
    }

    priority_queue<
        pair<int, string>,
        vector<pair<int, string>>,
        greater<pair<int, string>>
    > pq;

    dist[s] = 0;
    pq.push({0, s});

    while (!pq.empty())
    {
        int currentTime = pq.top().first;
        string current = pq.top().second;

        pq.pop();

        if (currentTime > dist[current])
            continue;

        if (current == d)
            break;

        for (int i = 0; i < graph[current].size(); i++)
        {
            JourneyEdge edge = graph[current][i];

            int newTime = currentTime + edge.travelTime;

            if (newTime < dist[edge.destination])
            {
                dist[edge.destination] = newTime;

                parent[edge.destination] = current;
                parentEdge[edge.destination] = edge;

                pq.push({newTime, edge.destination});
            }
        }
    }

    if (dist[d] == numeric_limits<int>::max())
    {
        cout << "No route available between these stations.\n";
        return;
    }

    vector<string> path;
    vector<JourneyEdge> trains;

    string current = d;

    while (current != s)
    {
        path.push_back(current);

        trains.push_back(parentEdge[current]);

        current = parent[current];
    }

    path.push_back(s);

    reverse(path.begin(), path.end());
    reverse(trains.begin(), trains.end());

    displayPath(path, trains, dist[d]);
}

// Find journey with minimum train changes using BFS
void Journey::minimumTransferJourney()
{
    string source, destination;

    cout << "\nEnter Source Station: ";
    cin >> ws;
    getline(cin, source);

    cout << "Enter Destination Station: ";
    getline(cin, destination);

    string s = normalize(source);
    string d = normalize(destination);

    if (stations.find(s) == stations.end() ||
        stations.find(d) == stations.end())
    {
        cout << "Invalid station name.\n";
        return;
    }

    if (s == d)
    {
        cout << "Source and destination are same.\n";
        return;
    }

    queue<string> q;

    unordered_map<string, bool> visited;
    unordered_map<string, string> parent;
    unordered_map<string, JourneyEdge> parentEdge;

    q.push(s);
    visited[s] = true;

    while (!q.empty())
    {
        string current = q.front();
        q.pop();

        if (current == d)
            break;

        for (int i = 0; i < graph[current].size(); i++)
        {
            JourneyEdge edge = graph[current][i];

            if (!visited[edge.destination])
            {
                visited[edge.destination] = true;

                parent[edge.destination] = current;
                parentEdge[edge.destination] = edge;

                q.push(edge.destination);
            }
        }
    }

    if (!visited[d])
    {
        cout << "No route available between these stations.\n";
        return;
    }

    vector<string> path;
    vector<JourneyEdge> trains;

    string current = d;

    while (current != s)
    {
        path.push_back(current);

        trains.push_back(parentEdge[current]);

        current = parent[current];
    }

    path.push_back(s);

    reverse(path.begin(), path.end());
    reverse(trains.begin(), trains.end());

    int totalTime = 0;

    for (int i = 0; i < trains.size(); i++)
    {
        totalTime += trains[i].travelTime;
    }

    displayPath(path, trains, totalTime);
}

// Journey menu
void Journey::run()
{
    int choice;

    do
    {
        cout << "\n====================================\n";
        cout << "       JOURNEY MANAGEMENT\n";
        cout << "====================================\n";

        cout << "1. Display Available Stations\n";
        cout << "2. Display Train Connections\n";
        cout << "3. Plan Journey\n";
        cout << "4. Find Fastest Journey\n";
        cout << "5. Minimum Transfer Journey\n";
        cout << "0. Return to Main Menu\n";

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                displayStations();
                break;

            case 2:
                displayTrainConnections();
                break;

            case 3:
                planJourney();
                break;

            case 4:
                fastestJourney();
                break;

            case 5:
                minimumTransferJourney();
                break;

            case 0:
                cout << "Returning to Main Menu...\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 0);
}
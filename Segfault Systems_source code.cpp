
#include<iostream>
#include<limits>
#include<cfloat>

using namespace std;

const int STATION_SIZE = 12;

struct Route;

struct Station {
    int stationID;
    string name;
    Route* nextR;
};

struct Route {
    double distance;
    Station* to;
    Route* next;
};

Station stationList[STATION_SIZE] = {{0, "SS15", NULL}, {0, "SS18", NULL}, {0, "USJ 7", NULL}, {0, "Taipan", NULL},
    {0, "Wawasan", NULL}, {0, "USJ 21", NULL}, {0, "South Quay - USJ 1", NULL}, {0, "SunU - Monash", NULL},
    {0, "Sunmed", NULL}, {0, "Sunway Lagoon", NULL}, {0, "Mentari", NULL}, {0, "Sunway - Setia Jaya", NULL}};


// Function to create a new route and add to linked list
void addRoute(Station& from, Station& to, double distance) {
    Route* newRoute = new Route{distance, &to, from.nextR};
    from.nextR = newRoute;
}

void stationSetup(){
    //Station ID assigned using loop index
    for(int i = 0; i < STATION_SIZE; i++){
        stationList[i].stationID = i+1;
    }
    
    // Create bi-directional routes
    addRoute(stationList[0], stationList[1], 0.90); // SS15 → SS18
    addRoute(stationList[1], stationList[0], 0.90); // SS18 → SS15

    addRoute(stationList[1], stationList[2], 2.00); // SS18 → USJ 7
    addRoute(stationList[2], stationList[1], 2.00);

    addRoute(stationList[2], stationList[3], 0.84); // USJ 7 → Taipan
    addRoute(stationList[3], stationList[2], 0.84);

    addRoute(stationList[3], stationList[4], 1.50); // Taipan → Wawasan
    addRoute(stationList[4], stationList[3], 1.50);

    addRoute(stationList[4], stationList[5], 1.10); // Wawasan → USJ 21
    addRoute(stationList[5], stationList[4], 1.10);

    addRoute(stationList[2], stationList[6], 0.90); // USJ 7 → South Quay
    addRoute(stationList[6], stationList[2], 0.90); // Interchange

    addRoute(stationList[6], stationList[7], 0.67); // South Quay → SunU
    addRoute(stationList[7], stationList[6], 0.67);

    addRoute(stationList[7], stationList[8], 0.79); // SunU → SunMed
    addRoute(stationList[8], stationList[7], 0.79);

    addRoute(stationList[8], stationList[9], 0.60); // SunMed → Lagoon
    addRoute(stationList[9], stationList[8], 0.60);

    addRoute(stationList[9], stationList[10], 0.30); // Lagoon → Mentari
    addRoute(stationList[10], stationList[9], 0.30);

    addRoute(stationList[10], stationList[11], 1.50); // Mentari → Setia Jaya
    addRoute(stationList[11], stationList[10], 1.50);
}

//function to receive user inputs
int userInput(int val1){
	int input;
	cin >> input;
	if(input == -99 && val1 == -1){ //if -99, returns value to main to terminate program
	    return input;
	}
	else{
	    while(cin.fail() || input <=0 || input > STATION_SIZE){ //if input value invalid, reprompt user
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "Please input a valid station. \n";
            cout << "Enter station: ";
            cin >> input;
            if(input == -99 && val1 == -1){ //if -99, returns value to main to terminate program
	            return input;
	        }
        }
        return input;
	}
}


// Returns index of unvisited station with minimal dist[]
int minDistance(double dist[], bool visited[]) {
    double minVal = DBL_MAX;
    int minIndex = -1;
    for (int i = 0; i < STATION_SIZE; i++) {
        if (!visited[i] && dist[i] <= minVal) {
            minVal = dist[i];
            minIndex = i;
        }
    }
    return minIndex;
}

// Runs Dijkstra's algorithm from initial to destination station and prints the path
void findShortestPath(int startId, int endId) {
    bool visited[STATION_SIZE] = {false};
    double dist[STATION_SIZE];
    int prev[STATION_SIZE];

    // Initialization
    for (int i = 0; i < STATION_SIZE; i++) {
        dist[i] = DBL_MAX;
        prev[i] = -1;
    }
    dist[startId] = 0.0;

    // Main loop
    for (int count = 0; count < STATION_SIZE; count++) {
        int currentNode = minDistance(dist, visited);
        if (currentNode == -1 || dist[currentNode] == DBL_MAX){
            break;
        }
        visited[currentNode] = true;
            
        // Relax outgoing edges
        Route* route = stationList[currentNode].nextR;
        while (route) {
            int nextNode = route->to->stationID - 1;  // zero-based index
            double alt = dist[currentNode] + route->distance;
            if (!visited[nextNode] && alt < dist[nextNode]) {
                dist[nextNode] = alt;
                prev[nextNode] = currentNode;
            }
            route = route->next;
        }
    }


    // Output results
    if (dist[endId] == DBL_MAX) {
        cout << "\nNo route found.\n";
    }
    else{
        cout << "\nShortest distance: " << dist[endId] << " km\n";
    }
    

    // Reconstruct path 
    int pathArr[STATION_SIZE];
    int pathSize = 0;

    // Backtrack from destination to source
    for (int current = endId; current != -1; current = prev[current]) {
        pathArr[pathSize++] = current;
    }

    // Print in reverse (source → destination)
    cout << "Route: ";
    for (int i = pathSize - 1; i >= 0; --i) {
        cout << stationList[pathArr[i]].name;
        if (i > 0){
            cout << " -> ";
        }
    }
    cout << "\n\n";
}

int main(void) {

    int initial, destination;
    
    stationSetup();
    
    do{
        initial = -1;
        destination = -1;
        cout << "= = = =  Klang Valley Transit Route  = = = =\n";
        for(int i = 0; i < STATION_SIZE; i++){
            cout << stationList[i].stationID << " - " << stationList[i].name << endl;
        }
    
        cout << "\nEnter starting station (-99 to exit): ";
        initial = userInput(initial);
        
        if(initial == -99){
            cout << "\nHave a nice day, see you soon.";
            break;
        }
        
        cout << "Enter destination station: ";
        destination = userInput(initial);
        
        if(initial == destination){
            cout << "\nStarting and final destination cannot be the same.\nPlease try again.\n\n";
        }
        else{
            findShortestPath(initial - 1, destination - 1);
        }
    }while(initial != -99);

}




/**********************************************************************************************************************
*   Title: how to ensure an input is an integer?
*   Author: Peter87
*   Date: 2022
*   Code version: -
*   Availability: https://cplusplus.com/forum/beginner/283248/
*
***********************************************************************************************************************
*   Title: C / C++ Program for Dijkstra's shortest path algorithm | Greedy Algo-7
*   Author: GeeksforGeeks
*   Date: 23rd July 2025
*   Code version: -
*   Availability: https://www.geeksforgeeks.org/cpp/c-program-for-dijkstras-shortest-path-algorithm-greedy-algo-7/ 
*
***********************************************************************************************************************
*   Title: Dijkstra’s Algorithm for Adjacency List Representation | Greedy Algo-8
*   Author: GeeksforGeeks
*   Date: 23rd July 2025
*   Code version: -
*   Availability: https://www.geeksforgeeks.org/dsa/dijkstras-algorithm-for-adjacency-list-representation-greedy-algo-8/

***********************************************************************************************************************
*   Title: C++ Program for Dijkstra’s shortest path algorithm?
*   Author: Sudhir Sharma
*   Date: 9th August 2019
*   Code version: -
*   Availability: https://www.tutorialspoint.com/cplusplus-program-for-dijkstra-s-shortest-path-algorithm
*
***********************************************************************************************************************
*   Title: C / C++ Program for Dijkstra\'s shortest path algorithm
*   Author: Sudhir Sharma
*   Date: 8th November 2023
*   Code version: -
*   Availability: https://www.tutorialspoint.com/c-cplusplus-program-for-dijkstra-s-shortest-path-algorithm
*   
************************************************************************************************************************
*   Title: Dijkstra's Algorithm
*   Author: programiz
*   Date: -
*   Code version: -
*   Availability: https://www.programiz.com/dsa/dijkstra-algorithm
*
************************************************************************************************************************
*   Title: How to implement Dijkstra's Algorithm in C++
*   Author: HowDev
*   Date: -
*   Code version: -
*   Availability: https://how.dev/answers/how-to-implement-dijkstras-algorithm-in-cpp
************************************************************************************************************************/

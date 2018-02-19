//
//  main.cpp
//  DiscreteEventSimulation
//
//  Created by Doug on 2/16/18.
//  Copyright © 2018 Doug. All rights reserved.
//

#include <iostream>
#include <queue> // for the priority queue
#include <stdlib.h> // For random
#include <time.h> // Time for seeding random
#include "Event.hpp"

// Forward declare
void bankSimulator();
void storeSimulator();

int main(int argc, const char * argv[]) {
    
    // Based on inline argument, report error or begin simulation
    if(argc != 2){
        std::cout << "Incorrect arguments." << "\n";
        return -1;
    }
    else if(strcmp(argv[1], "bank") == 0){
        bankSimulator();
    }
    else if(strcmp(argv[1], "supermarket") == 0){
        storeSimulator();
    }
    
    else {
        std::cout << "Incorrect argument." << "\n";
    }
    
    return 0;
}


void bankSimulator(){
    
    std::cout << "bank simulator" << "\n";
}


void storeSimulator(){
    srand ( (int) time(NULL) ); // seed the RNG
    int dayLength = 28800; // Length of day in seconds (28800 seconds = 8 hours)
    int currentTime = 0; // Represents current clock time in seconds
    int timeOfLastEvent = 0;
    int customersServed = 0;
    int cashiers[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::priority_queue<Event, std::vector<Event>, std::less<Event>> events; // holds all the events
    
    // Set a customer arrival Event to occur every 32 seconds of the 28800 second day
    // Add each of these events to the priority queue of events.
    for(int time = 0; time < 28800; time += 32){
        Event arrival = Event(time, "arrival");
        events.push(arrival);
    }
    
    std::cout << "store simulator" << "\n";
    std::cout << "Number of Customers served: " << customersServed << "\n";
    
}


// Random number between 30-600, represents how long it customer will take with cashier
// int randomTime = (rand() % 571) + 30;

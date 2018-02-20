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

// Forward declare functions
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




void storeSimulator(){
    srand ( (int) time(NULL) ); // seed the RNG
    const int dayLength = 28800; // Length of day in seconds (28800 seconds = 8 hours)
    int currentTime = 0; // Represents current clock time in seconds
    int totalWaitTime = 0; // Total time it took each customer from arriving to leaving
    int timeChashierSpentIdle = 0; // Total time at least one cashier spent idle
    int timeOfLastEvent = 0;
    int customersServed = 0;
    int cashiers[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::priority_queue<Event, std::vector<Event>, std::greater<Event>> events; // holds all the events
    
    // Set a customer arrival Event to occur every 32 seconds of the 28800 second day
    // Add each of these events to the priority queue of events.
    for(int time = 0; time < 28800; time += 32){
        Event arrival = Event(time, "arrival");
        events.push(arrival);
    }
    
    // Process each event in the queue until the day runs out of time
    while(currentTime < dayLength){
        
        // Get whichever event occurs now, and remove it from queue of events
        Event event = events.top();
        events.pop();
        
        // Adjust time to the time of the current event
        timeOfLastEvent = currentTime;
        currentTime = event.getExpiration();
        
        // If a cashier has time less than the current time, they've been idle since the last event.
        // Also, re-adjust all cashier's times to the current time (reset to zero)
        bool someoneWasIdle = false;
        for(int i = 0; i < 10; i++){
            if(cashiers[i] < currentTime){
                cashiers[i] = currentTime;
                someoneWasIdle = true;
            }
        }
        
        if(someoneWasIdle){
            timeChashierSpentIdle += currentTime - timeOfLastEvent;
        }
        
        // How to process the event if it's someone arriving at checkout
        if(event.getType() == "arrival"){
            
            // Random number between 30-600, reps how long customer will take with cashier
            int processingTime = (rand() % 571) + 30;
            
            // Find the cashier line with the shortest wait time. The value contained by each
            // cashier represents the time at which all their customers will have been processed.
            int lineNumber = 0;
            int shortestLine = cashiers[0];
            for(int i = 1; i < 10; i++){
                if (cashiers[i] < shortestLine){
                    shortestLine = cashiers[i];
                    lineNumber = i;
                }
            }
            
            // Add this customer's time to the line they've entered.
            cashiers[lineNumber] += processingTime;
            
            // Add an event for when this customer will finish at checkout. This customer's time
            // will be their processing time + processing time of all customers in front of them
            Event newEvent = Event((processingTime + shortestLine), "finished");
            newEvent.setArrivalTime(currentTime);
            events.push(newEvent);
        }
        
        else if (event.getType() == "finished"){
            customersServed++;
            totalWaitTime += (currentTime - event.getArrivalTime());
        }

    }
    
    std::cout << "STORE SIMULATOR\n";
    std::cout << "Number of Customers served: " << customersServed << "\n";
    std::cout << "Average customer service time: " << totalWaitTime / customersServed << "\n";
    std::cout << "Percent of time at least one cashier spent idle: ";
    std::cout << 100 * timeChashierSpentIdle / dayLength << "\n";
    
}






void bankSimulator(){
    srand ( (int) time(NULL) ); // seed the RNG
    const int dayLength = 28800; // Length of day in seconds (28800 seconds = 8 hours)
    int currentTime = 0; // Represents current clock time in seconds
    int totalWaitTime = 0; // Total time it took each customer from arriving to leaving
    int timeTellerSpentIdle = 0; // Total time at least one cashier spent idle
    int timeOfLastEvent = 0;
    int customersServed = 0;
    int tellersBusy = 0;
    std::priority_queue<Event, std::vector<Event>, std::greater<Event>> gettingHelped; // holds all the events
    std::queue<Event> arrivals;
    
    // Set a customer arrival Event to occur every 32 seconds of the 28800 second day
    // Add each of these events to the priority queue of events.
    for(int time = 0; time < 28800; time += 32){
        Event arrival = Event(time, "arrival");
        arrivals.push(arrival);
    }
    
    // Process each event in the queue until the day runs out of time
    while(currentTime < dayLength){
        
        // If the tellers are all busy, advance to the next time someone finishes
        if(tellersBusy == 10){
            // Get whoever finishes now, and remove it from queue of events
            Event justFinishing = gettingHelped.top();
            gettingHelped.pop();
            tellersBusy--;
            
            // Adjust time to the time of the current event
            timeOfLastEvent = currentTime;
            currentTime = justFinishing.getExpiration();
            
            // Calculate leaving customers total time at bank
            totalWaitTime += (currentTime - justFinishing.getArrivalTime());
            customersServed++;
            
            // If there's a customer in line
            if(arrivals.size() != 0 && arrivals.front().getArrivalTime() <= currentTime){
                tellersBusy++;
                
                // Random number between 30-600, reps how long customer will take with cashier
                int processingTime = (rand() % 571) + 30;
                
                // Take event from the arrivals queue and put it in the 'being helped' queue
                Event newEvent = arrivals.front();
                arrivals.pop();
                newEvent.setArrivalTime(newEvent.getExpiration());
                newEvent.setExpirationTime( (processingTime + currentTime) );
                gettingHelped.push(newEvent);
            }
        }
        
        // If there's an open teller, advance until there's a customer
        else if(tellersBusy < 10){
            
            tellersBusy++;
            
            // Random number between 30-600, reps how long customer will take with cashier
            int processingTime = (rand() % 571) + 30;
            
            // Take event from the arrivals queue and put it in the 'being helped' queue
            Event newEvent = arrivals.front();
            arrivals.pop();
            newEvent.setArrivalTime(newEvent.getExpiration());
            newEvent.setExpirationTime( (processingTime + currentTime) );
            gettingHelped.push(newEvent);
            
            // Adjust time to the time of the current event
            timeOfLastEvent = currentTime;
            currentTime = newEvent.getExpiration();
            
            timeTellerSpentIdle += currentTime - timeOfLastEvent;
        }
        
    } // End while loop
        
    std::cout << "BANK SIMULATOR\n";
    std::cout << "Number of Customers served: " << customersServed << "\n";
    std::cout << "Average customer service time: " << totalWaitTime / customersServed << "\n";
    std::cout << "Percent of time at least one cashier spent idle: ";
    std::cout << 100 * timeTellerSpentIdle / dayLength << "\n";
    
}

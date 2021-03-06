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
#include <cmath>
#include "Event.hpp"

// Forward declare functions
void bankSimulator();
void storeSimulator();
int computeVariance(std::vector<int> values);

// Length of a day in seconds (standard 8 hours = 28800)
// 100000000 (100,000,000 one hundred million)
const int DAY_LENGTH = 10000000;

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


/*
 * Simulator for a supermarket.
 */
void storeSimulator(){
    srand ( (int) time(NULL) ); // seed the RNG
    int currentTime = 0; // Represents current clock time in seconds
    int totalWaitTime = 0; // Total time it took each customer from arriving to leaving
    int cashierIdleTime = 0; // Total time at least one cashier spent idle
    int timeOfLastEvent = 0;
    int customersServed = 0;
    int cashiers[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::priority_queue<Event, std::vector<Event>, std::greater<Event>> events; // holds all the events
    std::vector<int> waitTimes;
    
    // Set a customer arrival Event to occur every 32 seconds of the day
    for(int time = 0; time < DAY_LENGTH; time += 32){
        events.emplace(time, time, "arrive");
    }
    
    // Process each event in the priority queue until the day ends
    while(currentTime < DAY_LENGTH){
        
        // Get whichever event occurs now, and remove it from event queue
        Event event = events.top();
        events.pop();
        
        // Adjust time to the current time (time of event)
        timeOfLastEvent = currentTime;
        currentTime = event.eventFireTime;
        
        // If a cashier has time less than the current time, they've been idle since the last event.
        // Re-adjust all cashier's times to the current time (reset to zero).
        bool someoneWasIdle = false;
        for(int i = 0; i < 10; i++){
            if(cashiers[i] < currentTime){
                cashiers[i] = currentTime;
                someoneWasIdle = true;
            }
        }
        if(someoneWasIdle){
            cashierIdleTime += currentTime - timeOfLastEvent;
        }
        
        // ******************
        // PROCESS AN ARRIVAL
        // ******************
        if(event.type == "arrive"){
            
            // Random number between 30-600, represents time needed with cashier
            int timeNeededWithCashier = (rand() % 571) + 30;
            
            // Find the cashier line with the shortest wait time. The value contained by each
            // cashier represents the time at which all their customers will have been processed.
            int lineNumber = 0;
            int timeLeftOfShortLine = cashiers[0];
            for(int i = 1; i < 10; i++){
                if (cashiers[i] < timeLeftOfShortLine){
                    timeLeftOfShortLine = cashiers[i];
                    lineNumber = i;
                }
            }
            
            // Add this customer's time to the line they've entered.
            cashiers[lineNumber] += timeNeededWithCashier;
            
            // Add an event for when this customer will finish at checkout. This customer's time
            // will be their processing time + processing time of all customers in front of them
            event.eventFireTime = timeNeededWithCashier + timeLeftOfShortLine;
            event.type = "leave";
            events.push(event);
        }
        
        // ***************
        // PROCESS A LEAVE
        // ***************
        else if (event.type == "leave"){
            customersServed++;
            totalWaitTime += (currentTime - event.arrivalTime);
            waitTimes.push_back(currentTime - event.arrivalTime);
        }
    } // End while loop simulating a day
    
    std::cout << "STORE SIMULATOR\n";
    std::cout << "Length of simulation: " << DAY_LENGTH << " seconds = " << DAY_LENGTH / 3600 << " hours = " << DAY_LENGTH / 86400 << " days\n";
    std::cout << "Number of Customers served: " << customersServed << "\n";
    std::cout << "Average customer service time: " << totalWaitTime / customersServed << "\n";
    std::cout << "Time at least one cashier spent idle: " << 100 * cashierIdleTime / DAY_LENGTH << "%\n";
    std::cout << "Variance in customer service time: " << computeVariance(waitTimes) << "\n";
    
}


/*
 * Simulator for a bank.
 */
void bankSimulator(){
    srand ( (int) time(NULL) ); // seed the RNG
    int currentTime = 0; // Represents current clock time in seconds
    long totalWaitTime = 0; // Total time it took each customer from arriving to leaving
    int idleTellerTime = 0; // Total time at least one cashier spent idle
    int timeOfLastEvent = 0;
    int customersServed = 0;
    int tellersBusy = 0;
    std::priority_queue<Event, std::vector<Event>, std::greater<Event>> events; // holds all the events
    std::queue<Event> customers;
    std::vector<int> waitTimes;
    
    // Set a customer arrival Event to occur every 32 seconds of the 28800 second day
    // Add each of these events to the priority queue of events.
    for(int time = 0; time < DAY_LENGTH; time += 32){
        Event arrival = Event(time, time, "arrive");
        events.push(arrival);
    }
    
    // Process each event in the queue until the day runs out of time
    while(currentTime < DAY_LENGTH){
        
        // Get whichever event occurs now, and remove it from event queue
        Event event = events.top();
        events.pop();
        
        // Adjust time to the current time (time of event)
        timeOfLastEvent = currentTime;
        currentTime = event.eventFireTime;
        
        // Check if a teller has been idle since last event
        if(tellersBusy < 10){
            idleTellerTime += (currentTime - timeOfLastEvent);
        }
        
        // ******************
        // PROCESS AN ARRIVAL
        // ******************
        if(event.type == "arrive"){
            
            // If there's an open teller, go to them
            if(tellersBusy < 10){
                // Random number between 30-600, represents time needed with teller
                int timeNeededWithTeller = (rand() % 571) + 30;
                
                // Reformat event as a leave event. Set the time this customer will leave
                event.eventFireTime = currentTime + timeNeededWithTeller;
                event.type = "leave";
                events.push(event);
                tellersBusy++;
            }
            
            // If there's no open teller, jump in the line and wait
            else{
                customers.push(event);
                continue;
            }
        } // End arrive event
        
        // ***************
        // PROCESS A LEAVE
        // ***************
        else if(event.type == "leave"){
            
            // Calculate data for customer leaving
            tellersBusy--;
            customersServed++;
            totalWaitTime += (currentTime - event.arrivalTime);
            waitTimes.push_back(currentTime - event.arrivalTime);
            
            // If there's a customer waiting in line
            if(customers.size() > 0){
                // Random number between 30-600, represents time needed with teller
                int timeNeededWithTeller = (rand() % 571) + 30;
                
                // Reformat event as a leave event. Set the time this customer will leave
                event = customers.front();
                customers.pop();
                event.eventFireTime = currentTime + timeNeededWithTeller;
                event.type = "leave";
                events.push(event);
                tellersBusy++;
            }
        } // End leave event
        
        
    } // End while loop simulating a day
        
    std::cout << "BANK SIMULATOR\n";
    std::cout << "Length of simulation: " << DAY_LENGTH << " seconds = " << DAY_LENGTH / 3600 << " hours = " << DAY_LENGTH / 86400 << " days\n";
    std::cout << "Number of Customers served: " << customersServed << "\n";
    std::cout << "Average customer service time: " << totalWaitTime / customersServed << "\n";
    std::cout << "Time at least one teller spent idle: " << 100 * idleTellerTime / DAY_LENGTH << "%\n";
    std::cout << "Variance in customer service time: " << computeVariance(waitTimes) << "\n";
    
}


int computeVariance(std::vector<int> values){
    
    // Get average of all values(x) into 'averageOfValues'
    long totalOfValues = 0;
    for(int i = 0; i < values.size(); i++){
        totalOfValues += values[i];
    }
    int averageOfValues = (int) (totalOfValues / values.size());
    
    // Compute (x-m)^2 for each value, all added together
    long totalOfValues2 = 0;
    for(int i = 0; i < values.size(); i++){
        totalOfValues2 += pow((values[i] - averageOfValues), 2);
    }
    
    return (int) (totalOfValues2 / values.size());
}

//
//  main.cpp
//  DiscreteEventSimulation
//
//  Created by Doug on 2/16/18.
//  Copyright © 2018 Doug. All rights reserved.
//

#include <iostream>
#include <queue>
#include <stdlib.h> // For random
#include <time.h> // Time for seeding random
#include "Customer.hpp"
#include "Attendant.hpp"

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
    int numberOfCustomers = 0;
    int customersServed = 0;
    Attendant cashiers[10];
    
    for(int i = 0; i < 10; i++){
        cashiers[i] = Attendant();
    }
    Attendant *shortestLine = &cashiers[0]; // Cashier with the smallest line
    
    // Process each second of the day. Each loop equals one second.
    for(int time = 0; time < dayLength; time++){
        
        // Every 32 seconds a customer arrives and enters a line
        if(time % 32 == 0){
            int randomTime = (rand() % 571) + 30; // Random number between 30-600
            Customer newCustomer(randomTime);
            numberOfCustomers++;
            
            // Add the customer to the shortest line
            shortestLine->line.push(newCustomer);
            shortestLine->totalTimeForAllCustomers += newCustomer.timeToProcess;
        }
        
        // Progress the customers in each line
        for(Attendant &currCashier : cashiers){
            
            // If there's a customer, decrease their time
            if(currCashier.line.size() > 0){
                currCashier.line.front().processOneSecond();
                std::cout << "here 1: " << currCashier.line.front().timeToProcess <<"\n";
                
                // Remove customer if finished
                if(currCashier.line.front().timeToProcess <= 0){
                    std::cout << "here 2" << "\n";
                    currCashier.line.pop();
                    customersServed++;
                }
                
                // Decrease cachier's total time remaining
                currCashier.totalTimeForAllCustomers--;
            }
            
            // Check to see if this cashier has the shortest line
            if(currCashier.totalTimeForAllCustomers < shortestLine->totalTimeForAllCustomers){
                shortestLine = &currCashier;
            }
        }
        
    }
    
    std::cout << "store simulator" << "\n";
    std::cout << "Number of Customers: " << numberOfCustomers << "\n";
    std::cout << "Number of Customers served: " << customersServed << "\n";
    
}


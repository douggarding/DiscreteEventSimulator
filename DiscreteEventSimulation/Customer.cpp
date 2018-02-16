//
//  Customer.cpp
//  DiscreteEventSimulation
//
//  Created by Doug on 2/16/18.
//  Copyright © 2018 Doug. All rights reserved.
//

#include "Customer.hpp"

// Basic constructor
Customer::Customer(int timeToProcess){
    this->timeToProcess = timeToProcess;
}

void Customer::processOneSecond(){
    timeToProcess--;
}

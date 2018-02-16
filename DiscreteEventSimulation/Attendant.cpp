//
//  Attendant.cpp
//  DiscreteEventSimulation
//
//  Created by Doug on 2/16/18.
//  Copyright © 2018 Doug. All rights reserved.
//

#include "Attendant.hpp"

// Basic constructor
Attendant::Attendant(){
    line = std::queue<Customer>();
    totalTimeForAllCustomers = 0;
}

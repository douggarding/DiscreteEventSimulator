//
//  Attendant.hpp
//  DiscreteEventSimulation
//
//  Created by Doug on 2/16/18.
//  Copyright © 2018 Doug. All rights reserved.
//

#ifndef Attendant_hpp
#define Attendant_hpp

#include <stdio.h>
#include <queue>
#include "Event.hpp"

class Attendant{
public:
    Attendant();
    std::queue<Event> line;
    int totalTimeForAllCustomers;
};

#endif /* Attendant_hpp */

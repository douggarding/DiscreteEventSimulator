//
//  Customer.cpp
//  DiscreteEventSimulation
//
//  Created by Doug on 2/16/18.
//  Copyright © 2018 Doug. All rights reserved.
//

#include "Event.hpp"

// Basic constructor
Event::Event(int timeOfEvent, std::string eventType){
    timeToExpire = timeOfEvent;
    type = eventType;
}





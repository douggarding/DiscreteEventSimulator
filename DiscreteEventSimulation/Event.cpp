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

std::string Event::getType(){
    return type;
}

int Event::getExpiration(){
    return timeToExpire;
}

void Event::setArrivalTime(int time){
    arrivalTime = time;
}

int Event::getArrivalTime(){
    return arrivalTime;
}




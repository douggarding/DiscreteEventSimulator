//
//  Customer.hpp
//  DiscreteEventSimulation
//
//  Created by Doug on 2/16/18.
//  Copyright © 2018 Doug. All rights reserved.
//

#ifndef Customer_hpp
#define Customer_hpp

#include <stdio.h>
#include <string>

struct Event{

    // Constructor
    Event(int timeOfArrival, int timeOfEvent, std::string eventType);
    
    // Member variables
    int eventTime; // Clock time for when this event should fire and die
    int arrivalTime; // Time of arrival for this event (or its associated arrive event)
    std::string type; // Type: whether this is an arrive or leave event

};


// Operator overloading for <
inline bool operator< (const Event &lhs, const Event &rhs){
    return lhs.eventTime < rhs.eventTime;
}

// Operator overloading for >
inline bool operator> (const Event &lhs, const Event &rhs){
    return operator<(rhs, lhs);
}


#endif /* Customer_hpp */

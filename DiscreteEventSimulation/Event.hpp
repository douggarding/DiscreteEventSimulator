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
    Event(int timeOfEvent, std::string eventType);
    
    // Member variables
    int timeToExpire; // Clock time for when this event should fire and die
    std::string type; // Type: whether this is an arrive or leave event
    int arrivalTime; // Time of arrival for this event (or its associated arrive event)

};


// Operator overloading for <
inline bool operator< (const Event &lhs, const Event &rhs){
    return lhs.timeToExpire < rhs.timeToExpire;
}

// Operator overloading for >
inline bool operator> (const Event &lhs, const Event &rhs){
    return operator<(rhs, lhs);
}


#endif /* Customer_hpp */

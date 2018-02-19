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

class Event{
public:
    Event(int timeOfEvent, std::string eventType);
    std::string type;
    int timeToExpire; // clock time for when this event should fire and die
};

/**
 COMPARISON OPERATOR OVERLOADING
 **/

// Operator overloading for <
inline bool operator< (const Event &lhs, const Event &rhs){
    return lhs.timeToExpire < rhs.timeToExpire;
}

// Operator overloading for ==
inline bool operator== (const Event &lhs, const Event &rhs){
    return lhs.timeToExpire == rhs.timeToExpire;
}

inline bool operator!= (const Event &lhs, const Event &rhs){
    return !operator==(lhs, rhs);
}

inline bool operator> (const Event &lhs, const Event &rhs){
    return operator<(rhs, lhs);
}

inline bool operator<= (const Event &lhs, const Event &rhs){
    return !operator> (lhs, rhs);
}

inline bool operator>= (const Event &lhs, const Event &rhs){
    return !operator< (lhs, rhs);
}


#endif /* Customer_hpp */

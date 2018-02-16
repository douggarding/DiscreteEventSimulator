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

class Customer{
public:
    Customer(int timeToProcess);
    void processOneSecond();
    int timeToProcess;
    
};


#endif /* Customer_hpp */

//
//  Random.h
//  EmergencyRoom
//
//  Created by Rachel Wofford on 5/4/18.
//  Copyright © 2018 Rachel Wofford. All rights reserved.
//

#ifndef Random_h
#define Random_h

#include <cstdlib>
#include <ctime>

//Random number generator
class Random{
public:
    //Use time as seed to initialize random number generator
    Random(){
        srand((unsigned int)std::time(0));
    }
    
    //Pass a value in to initialize random number generator
    Random(int seed){
        srand(seed);
    }
    
    //Return a random integer in the range of 1 - n+1
    int next_int(int n){
        return int((next_double() *n) + 1);
    }
    
    //Return a random double in the rand of 0-1
    double next_double(){
        return double(rand()) / RAND_MAX;
    }

};

#endif /* Random_h */

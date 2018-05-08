//
//  WaitingRoom.h
//  EmergencyRoom
//
//  Created by Rachel Wofford on 5/4/18.
//  Copyright © 2018 Rachel Wofford. All rights reserved.
//

#ifndef WaitingRoom_h
#define WaitingRoom_h

#include <iostream>
#include <string>
#include <queue>
#include "Patient.h"
#include "Random.h"

using std::queue;

//Allows access to a global variable in Simulator.h
extern Random my_random;

class WaitingRoom{
private:
    //Patient arrival rate per minute
    double arrival_rate;
    //Queue of patients in the WaitingRoom
    std::queue<Patient*> the_queue;
    
public:
    WaitingRoom() {}
    
    void set_arrival_rate(double arrival_rate) {
        this->arrival_rate = arrival_rate;
    }
    
    void update(int clock)
    {
        //Add a new Patient to the WaitingRoom based on arrival_rate
        //Generate a random double
        //If random double is less than or equal to the patient arrival rate, create a new patient
        if (my_random.next_double() <= arrival_rate)
        {
            //Create a new Patient object with arrival_time set to clock and add it to the_queue
            the_queue.push(new Patient(clock));
            //ASSIGN PRIORITY VALUE AND MAKE PRIORITY QUEUE
        }
        
    }
    
    friend class EmergencyRoom;

};

#endif /* WaitingRoom_h */

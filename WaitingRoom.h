//
//  WaitingRoom.h
//  EmergencyRoom
//
//  Created by Rachel Wofford on 5/4/18.
//  Copyright � 2018 Rachel Wofford. All rights reserved.
//

#ifndef WaitingRoom_h
#define WaitingRoom_h

#include <iostream>
#include <string>
#include <queue>
#include <set>
#include <fstream>
#include <vector>
#include "Patient.h"
#include "Random.h"

using std::queue;

//Allows access to a global variable in Simulator.h
extern Random my_random;

class WaitingRoom {
private:
    //Patient arrival rate per minute
    double arrival_rate;
    //Queue of patients in the WaitingRoom
    std::priority_queue<Patient*> patient_priority_queue;
    
    
public:
    WaitingRoom() {}
    
    void set_arrival_rate(double arrival_rate) {
        this->arrival_rate = arrival_rate;
    }
    
    
    void update(int clock)
    {
        //Retrieve patient name
        std::string patient_name = Patient::getRandomName();

        //Add a new Patient to the WaitingRoom based on arrival_rate
        //Generate a random double
        //If random double is less than or equal to the patient arrival rate, create a new patient
        if (my_random.next_double() < arrival_rate)
        {
            //Generate a random priority level
            double priority_level = my_random.next_double();
            
            int patient_priority_level;
            
            //Use above randomly generated priority level to account for different percentages of patients at each priority level
            //Depending on priority level, assign patient a random priority number
            if (priority_level <= 0.7)
            {
                patient_priority_level = my_random.next_int(9);
            }
            else if (priority_level > 0.7 && priority_level <= 0.9)
            {
                patient_priority_level = my_random.next_int(4) + 10;
                
            }
            else
            {
                patient_priority_level = my_random.next_int(4) + 15;
            }
            
            //Create new patient object and add it to patient_priority_queue
            patient_priority_queue.push(new Patient(clock, patient_priority_level, patient_name));
        }
    }
    
    friend class EmergencyRoom;
    
};

#endif /* WaitingRoom_h */

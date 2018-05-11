//
//  Discharge.h
//  EmergencyRoom
//
//  Created by Rachel Wofford on 5/4/18.
//  Copyright © 2018 Rachel Wofford. All rights reserved.
//

#ifndef Discharge_h
#define Discharge_h

#include <queue>
#include "Patient.h"

class Discharge{
private:
    //Queue of Patients in the Discharge queue
    std::queue<Patient *> discharge_queue;
    //Total accumulated wait time in the Emergency Room
    int total_wait_time;
    //Total number of patients served in the Emergency Room
    int num_served;
    
public:
    Discharge() : total_wait_time(0), num_served(0) {}
    
    int get_num_served() {
        return num_served;
    }
    
    int get_total_wait() {
        return total_wait_time;
    }
    
    void update(int clock)
    {
        //Check if there are Patients in the Discharge queue
        if (!discharge_queue.empty()) {
            //Identify the Patient at the front of the queue
            Patient *patient = discharge_queue.front();
            
            //Remove the Patient from the Discharge queue
            discharge_queue.pop();
            
            //Calculate the total time of this Patient's visit
            int patient_wait = clock - patient->arrival_time;
            
            //Add this Patient's wait time to the total wait time for all Patients
            total_wait_time += patient_wait;
            
            //Increment the number of Patients served in this Emergency Room
            num_served++;
            
            //Delete this Patient object
            delete patient;
        }
    }
    
    friend class EmergencyRoom;
};

#endif /* Discharge_h */

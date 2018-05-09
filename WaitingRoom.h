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
#include <set>
#include <fstream>
#include <vector>
#include "Patient.h"
#include "Random.h"
#include "EmergencyRoom.h"

using std::queue;

//Allows access to a global variable in Simulator.h
extern Random my_random;

class WaitingRoom{
private:
    //Patient arrival rate per minute
    double arrival_rate;
    //Queue of patients in the WaitingRoom
    std::priority_queue<Patient*> priority_one_queue;
    std::priority_queue<Patient*> priority_two_queue;
    std::priority_queue<Patient*> priority_three_queue;
    std::multiset<Patient> Records;
    std::vector<std::string> PatientNames;
    
public:
    WaitingRoom() {}
    
    void set_arrival_rate(double arrival_rate) {
        this->arrival_rate = arrival_rate;
        set_patient_names();
    }
    
    //Set the PatientNames from the CS273Ville Resident and Surname files
    void set_patient_names(){
        //GET FILES
        
    }
    
    //Return the name of the given Patient from the PatientNames vector
    std::string getPatientName(int i)
    {
        return PatientNames[i];
    }
    
    //Get the Hospital Records associated with this Patient
    std::multiset<Patient> &get_records(){
        return this->Records;
    }
    
    std::priority_queue<Patient*> &get_priority_one_queue(){
        return this->priority_one_queue;
    }
    
    std::priority_queue<Patient*> &get_priority_two_queue(){
        return this->priority_two_queue;
    }
    
    std::priority_queue<Patient*> &get_priority_three_queue(){
        return this->priority_three_queue;
    }
    
    void update(int clock)
    {
        std::string patient_name = getPatientName(my_random.next_int(PatientNames.size()-1));
        //Add a new Patient to the WaitingRoom based on arrival_rate
        //Generate a random double
        //If random double is less than or equal to the patient arrival rate, create a new patient
        if (my_random.next_double() <= arrival_rate)
        {
            //Assign Patient a priority level between 0 and 1
            double priority_level = my_random.next_double();
            
            if (priority_level <= .7)
            {
                priority_one_queue.push(new Patient(clock, priority_level, patient_name));
            }
            else if (priority_level <=.9 && priority_level > .7)
            {
                priority_two_queue.push(new Patient(clock, priority_level, patient_name));
            }
            else
            {
                priority_three_queue.push(new Patient(clock, priority_level, patient_name));
            }
            
            //ASSIGN PRIORITY VALUE AND MAKE PRIORITY QUEUE
        }
        
    }

    
    
    friend class EmergencyRoom;

};

#endif /* WaitingRoom_h */

//
//  EmergencyRoom.h
//  EmergencyRoom
//
//  Created by Rachel Wofford on 5/4/18.
//  Copyright © 2018 Rachel Wofford. All rights reserved.
//

#ifndef EmergencyRoom_h
#define EmergencyRoom_h

#include <queue>
#include <list>
#include "Patient.h"
#include "Discharge.h"
#include "Random.h"

//Accesses global variable from Simulator.h
extern Random my_random;

//Takes Patient from WaitingRoom queue and adds it to EmergencyRoom queue
//Patient moves to the Disharge queue once they are done being treated in the Emergency Room
class EmergencyRoom{
protected:
    //Number of doctors from user's input
    int num_doctors;
    //Number of nurses from user's input
    int num_nurses;
    
    std::priority_queue<Patient*> treatment_queue;
    
    //Pointer to Discharge queue
    Discharge *patient_discharge_queue;
    WaitingRoom *patient_priority_queue;
    
    
public:
    EmergencyRoom() {}
    
    //Set the discharge queue
    void set_patient_priority_queue(WaitingRoom *patient_priority_queue){
        this->patient_priority_queue = patient_priority_queue;
    }
    
    void set_patient_discharge_queue(Discharge *patient_discharge_queue) {
        this->patient_discharge_queue = patient_discharge_queue;
    }
    
    //Set the number of doctors
    void set_num_doctors(int num_doctors){
        this->num_doctors = num_doctors;
    }
    
    //Set the number of nurses
    void set_num_nurses(int num_nurses){
        this->num_nurses = num_nurses;
    }
 

    friend class Discharge; 
};

#endif /* EmergencyRoom_h */

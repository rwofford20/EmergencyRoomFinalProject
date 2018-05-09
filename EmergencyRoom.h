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
#include "WaitingRoom.h"
#include "Discharge.h"
#include "Random.h"
#include "Simulator.h"

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
    
    //Pointer to WaitingRoom queue
    WaitingRoom *waiting_room_queue;
    //Pointer to EmergencyRoom queue
    EmergencyRoom *emergency_room_queue;
    //Pointer to Discharge queue
    Discharge *discharge_queue;
    
public:
    EmergencyRoom() {}
    
    //Set the WaitingRoom queue
    void set_waiting_room_queue(WaitingRoom *waiting_room_queue) {
        this->waiting_room_queue = waiting_room_queue;
    }
    
    //Set the discharge queue
    void set_discharge_queue(Discharge *discharge_queue) {
        this->discharge_queue = discharge_queue;
    }
    
    //Set the number of doctors
    void set_num_doctors(int num_doctors){
        this->num_doctors = num_doctors;
    }
    
    //Set the number of nurses
    void set_num_nurses(int num_nurses){
        this->num_nurses = num_nurses;
    }
    
    //Polymorphic function called in Nurse.h or Doctor.h
    virtual void update() = 0;

};

#endif /* EmergencyRoom_h */

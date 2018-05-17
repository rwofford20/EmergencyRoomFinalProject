//
//  Nurse.h
//  EmergencyRoom
//
//  Created by Rachel Wofford on 5/4/18.
//  Copyright � 2018 Rachel Wofford. All rights reserved.
//

#ifndef Nurse_h
#define Nurse_h

#include "Simulator.h"
#include "EmergencyRoom.h"
#include "Discharge.h"

class Nurse : public Caregiver
{
protected:
    //Nurse's maximum treatable priority level is 10
    const int clearance_level = 10;
    //Amount of time it will take Nurse to treat Patient -- randomly generated for each Patient
    int care_time;
    //Pointer to an EmergencyRoom object
    EmergencyRoom *emergency_room;
    
public:
    //Constructor for Nurse object
    Nurse(EmergencyRoom *emergency_room) : Caregiver(emergency_room) {}

    //Min Nurse care time is 1 min, max Nurse care time is 10 min
    //Function to return the randomly generated amount of time it will take Nurse to treat a Patient
    int get_care_time() {
        care_time = (my_random.next_int(9) + 1);
        return care_time;
    }
    
    //Returns Nurse's maximum treatable priority level
    int get_clearance_level() {
        return clearance_level;
    }
    
};

#endif /* Nurse_h */

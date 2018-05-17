//
//  Doctor.h
//  EmergencyRoom
//
//  Created by Rachel Wofford on 5/4/18.
//  Copyright � 2018 Rachel Wofford. All rights reserved.
//

#ifndef Doctor_h
#define Doctor_h

#include "Simulator.h"
#include "EmergencyRoom.h"
#include "Discharge.h"

class Doctor : public Caregiver
{
protected:
    //Doctor's maximum treatable priority level is 20
    const int clearance_level = 20;
    //Amount of time it will take Doctor to treat Patient -- randomly generated for each Patient
    int care_time;
    //Pointer to an EmergencyRoom object
    EmergencyRoom *emergency_room;
    
public:
    //Constructor for Doctor object
    Doctor(EmergencyRoom *emergency_room) : Caregiver(emergency_room) {}
    
    //Min Doctor care time is 1 min, max Doctor care time is 20 min
    //Function to return the randomly generated amount of time it will take Doctor to treat a Patient
    int get_care_time() {
        care_time = (my_random.next_int(19) + 1);
        return care_time;
    }
    
    //Returns Doctor's maximum treatable priority level
    int get_clearance_level() {
        return clearance_level;
    }
    
};

#endif /* Doctor_h */

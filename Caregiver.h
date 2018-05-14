//
//  Caregiver.h
//  EmergencyRoom
//
//  Created by Rachel Wofford on 5/4/18.
//  Copyright © 2018 Rachel Wofford. All rights reserved.
//

#ifndef Caregiver_h
#define Caregiver_h

#include "EmergencyRoom.h"

class EmergencyRoom;

class Caregiver{
protected:
    EmergencyRoom *emergency_room;
public:
    
    Caregiver(EmergencyRoom *emergency_room) {
        emergency_room = emergency_room;
    };
    
    //Polymorphic functions used in Nurse.h and Doctor.h
    //Polymorphic function to set the amount of time it will take a Caregiver to treat a Patient
    virtual void set_care_time() = 0;
    //Polymorphic function to return the amount of time it will take a Caregiver to treat a Patient
    virtual int get_care_time() = 0;
    //Polymorphic function to return the maximum priority level a Caregiver can treat
    virtual int get_clearance_level() = 0;
    
    friend class EmergencyRoom;
};


#endif /* Caregiver_h */

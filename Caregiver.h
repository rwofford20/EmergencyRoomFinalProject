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

class Caregiver{
public:
    
    //Polymorphic function used in Nurse.h and Doctor.h
    virtual void update() = 0;
    
    friend class EmergencyRoom;
};

#endif /* Caregiver_h */

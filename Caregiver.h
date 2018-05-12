//
//  Caregiver.h
//  EmergencyRoom
//
//  Created by Rachel Wofford on 5/4/18.
//  Copyright © 2018 Rachel Wofford. All rights reserved.
//

#ifndef Caregiver_h
#define Caregiver_h

class EmergencyRoom;

class Caregiver{
protected:
    int min_treatment_time;
    int max_treatment_time;
    EmergencyRoom *emergency_room;
public:
    
    Caregiver(EmergencyRoom *emergency_room) {
        emergency_room = emergency_room;
    };
    
    //Polymorphic function used in Nurse.h and Doctor.h
    virtual void update() = 0;
    virtual void set_care_time() = 0;
    virtual int get_care_time() = 0;
    virtual void set_treatment_time() = 0;
    virtual double get_treatment_time() = 0;
    
    
    friend class EmergencyRoom;
};

#endif /* Caregiver_h */

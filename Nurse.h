//
//  Nurse.h
//  EmergencyRoom
//
//  Created by Rachel Wofford on 5/4/18.
//  Copyright © 2018 Rachel Wofford. All rights reserved.
//

#ifndef Nurse_h
#define Nurse_h

class Nurse{
private:
    int care_time;
public:
    void setCareTime(int ct){
        care_time = ct;
    }
    int getCareTime(){
        return care_time; 
    }
};

#endif /* Nurse_h */

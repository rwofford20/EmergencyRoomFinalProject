//
//  Caregiver.h
//  EmergencyRoom
//
//  Created by Rachel Wofford on 5/4/18.
//  Copyright © 2018 Rachel Wofford. All rights reserved.
//

#ifndef Caregiver_h
#define Caregiver_h

class Caregiver{
private:
    int care_time;
public:
    virtual void setCareTime(int ct) = 0;
    virtual int getCareTime() = 0;
};

#endif /* Caregiver_h */

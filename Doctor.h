//
//  Doctor.h
//  EmergencyRoom
//
//  Created by Rachel Wofford on 5/4/18.
//  Copyright © 2018 Rachel Wofford. All rights reserved.
//

#ifndef Doctor_h
#define Doctor_h

class Doctor{
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

#endif /* Doctor_h */

//
//  Patient.h
//  EmergencyRoom
//
//  Created by Rachel Wofford on 5/4/18.
//  Copyright © 2018 Rachel Wofford. All rights reserved.
//

#ifndef Patient_h
#define Patient_h

#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <set>

struct Patient{
    
    Patient(int clock, int priority_level, std::string name) : priority_level(-1), name(""), patient_visits(-1), arrival_time(clock), start_treatment_time(-1), treatment_time(-1) {}

    int priority_level;
    std::string name;
    int patient_visits;
    int arrival_time;
    int start_treatment_time;
    int treatment_time;
    
    std::string Name() const {return name;}
    double Priority() const {return priority_level;}
    
    std::multiset<int> patient_record;
    
};

bool operator<(const Patient& first, const Patient& second){
    if (first.Name() < second.Name())
        return true;
    else if (first.Name() == second.Name() && first.Priority() > second.Priority())
        return true;
    else
        return false;
}

#endif /* Patient_h */

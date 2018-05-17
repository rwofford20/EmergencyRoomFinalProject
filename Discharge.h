//
//  Discharge.h
//  EmergencyRoom
//
//  Created by Rachel Wofford on 5/4/18.
//  Copyright � 2018 Rachel Wofford. All rights reserved.
//

#ifndef Discharge_h
#define Discharge_h

#include <queue>
#include "Patient.h"

class Discharge {
private:
    //Queue of Patients in the Discharge queue
    std::queue<Patient *> discharge_queue;
    
    //String of patients who have been seen.
    std::vector<Patient *> treated_patients;
    
    std::multiset<Patient> records;
    
    //Total accumulated wait time in the Emergency Room
    int total_wait_time;
    //Total number of patients served in the Emergency Room
    int num_served;
    int patient_wait; 
    
public:
    Discharge() : total_wait_time(0), num_served(0) {}
    
    int get_num_served() {
        return num_served;
    }
    
    int get_total_wait() {
        return total_wait_time;
    }
    
    //Multiset that contains Patient objects
    std::multiset<Patient> get_records(){
        return this->records;
    }
    
    //Returns vector of treated Patient's names so it can be accessed by other classes
    std::vector<std::string> get_treated_patients()
    {
        //Vector containing names of treated Patients
        std::vector<std::string> treated_patients_names;
        std::string treated_name;
        
        //Loop to add Patient's names to vector
        for (int i = 0; i < treated_patients.size(); i++)
        {
            treated_name = treated_patients[i]->getName();
            
            treated_patients_names.push_back(treated_name);
        }
        
        return treated_patients_names;
    }
    
    
    void update(int clock)
    {
        //Check if there are Patients in the Discharge queue
        if (!discharge_queue.empty()) {
            //Identify the Patient at the front of the queue
            Patient *patient = discharge_queue.front();
            
            //Remove the Patient from the Discharge queue
            discharge_queue.pop();
            
            patient->set_patient_visits();
            //patient->set_patient_record(patient);
            records.insert(*patient);
            
            //Calculate the total time of this Patient's visit
            patient_wait = clock - patient->get_arrival_time();
            
            //Add this Patient's wait time to the total wait time for all Patients
            total_wait_time += patient_wait;
            
            //Increment the number of Patients served in this Emergency Room
            num_served++;
            
            //Add patient to the queue of treated patients
            treated_patients.push_back(patient);
        }
    }
    
    friend class EmergencyRoom;
};

#endif /* Discharge_h */

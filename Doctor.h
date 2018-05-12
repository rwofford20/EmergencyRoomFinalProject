//
//  Doctor.h
//  EmergencyRoom
//
//  Created by Rachel Wofford on 5/4/18.
//  Copyright © 2018 Rachel Wofford. All rights reserved.
//

#ifndef Doctor_h
#define Doctor_h

#include "Simulator.h"
#include "EmergencyRoom.h"
#include "Discharge.h"

class Doctor : public Caregiver
{
protected:
    //Range of doctor service times
    int min_doctor_treatment_time = 1;
    int max_doctor_treatment_time = 20;
    int care_time;
    EmergencyRoom *emergency_room;
    
public:
    Doctor(EmergencyRoom *emergency_room): Caregiver(emergency_room) {}
    
    void set_care_time(){
        care_time = my_random.next_int(19);
    }
    
    void get_care_time(){
        return care_time;
    }
    
    
    //Loop to move a Patient from the EmergencyRoom queue to the Discharge queue if they are done being treated by a doctor
    //If the Patient moves to Discharge, this loop takes a Patient from the WaitingRoom queue and adds it to the EmergencyRoom queue
    void update(int clock)
    {
        
        //Executes if a doctor is available to treat a Patient
        if (treatment_queue.empty()) {
                
            //Move a Patient from the WaitingRoom queue to the EmergencyRoom queue if the WaitingRoom is not empty
            if(!treatment_queue.empty()){
                //Create a new Patient object pointing to the first Patient in the WaitingRoom queue
                Patient *patient = treatment_queue.front();
                //Remove first Patient object from WaitingRoom queue
                doctor_queue->the_queue.pop();
                
                //Update the start_treatment_time attribute for the Patient
                int t_time = clock;
                patient->start_treatment_time = t_time;
                    
                //Compute a random treatment time for the Patient between min_doctor_treatment_time and max_doctor_service_time
                int n = max_doctor_treatment_time - min_doctor_treatment_time;
                //Use my_random.next_int(n) to generate a random value between 0 and n
                //This number will not be in the correct range
                int treat_time = my_random.next_int(n);
                //Add the randomly generated treat_time to min_doctor_treatment_time to get a treatment time in the correct range of values
                int treatment_time = treat_time + min_doctor_treatment_time;
                //Set the patient's treatment time to the calculated treatment time
                patient->treatment_time = treatment_time;
                
                //Add the Patient to the EmergencyRoom queue for doctors
                doctor_queue.push(patient);
            }
                
        }
    }
    
    /*void setCareTime(int ct){
        care_time = ct;
    }
    int getCareTime(){
        return care_time;
    }*/
};

#endif /* Doctor_h */

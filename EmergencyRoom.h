//
//  EmergencyRoom.h
//  EmergencyRoom
//
//  Created by Rachel Wofford on 5/4/18.
//  Copyright © 2018 Rachel Wofford. All rights reserved.
//

#ifndef EmergencyRoom_h
#define EmergencyRoom_h

#include <queue>
#include <list>
#include "Patient.h"
#include "Discharge.h"
#include "Caregiver.h"
#include "Random.h"

//Accesses global variable from Simulator.h
extern Random my_random;
std::queue<Patient*> treatment_queue;

//Takes Patient from WaitingRoom queue and adds it to EmergencyRoom queue
//Patient moves to the Disharge queue once they are done being treated in the Emergency Room
class EmergencyRoom{
protected:
    //Number of doctors from user's input
    int num_doctors;
    //Number of nurses from user's input
    int num_nurses;

    std::vector<Caregiver*> caregivers;
    
    //Pointer to Discharge queue
    Discharge *patient_discharge_queue;
    WaitingRoom *wr_patient_priority_queue;
    
    
public:
    EmergencyRoom() {}
    
    //Set the discharge queue
    void set_wr_patient_priority_queue(WaitingRoom *patient_priority_queue){
        this->wr_patient_priority_queue = patient_priority_queue;
    }
    
    void set_patient_discharge_queue(Discharge *patient_discharge_queue) {
        this->patient_discharge_queue = patient_discharge_queue;
    }
    
    //Set the number of doctors
    void set_num_doctors(int num_doctors){
        this->num_doctors = num_doctors;
    }
    
    //Set the number of nurses
    void set_num_nurses(int num_nurses){
        this->num_nurses = num_nurses;
    }
    
    void add_patient_to_discharge(int clock){
        
        // Executes if the EmergencyRoom is not empty
        if (!treatment_queue.empty()) {
            
            //Identifies Patient object at the front of the Doctor Treatment queue
            Patient *patient = treatment_queue.front();
            
            //Checks if full treatment time has elapsed
            //If so, moves Patient from the EmergencyRoom queue to the Discharge queue
            if ((clock - patient->start_treatment_time) > patient->treatment_time) {
                
                //Removes Patient from the treatment queue
                treatment_queue.pop();
                
                //Adds the Patient to the Discharge queue
                patient_discharge_queue->discharge_queue.push(patient);
            }
        }
    }
    
    //Executes if a doctor or nurse is available to treat a Patient
    void add_patient_to_treatment_queue(int clock){
        //Move a Patient from the WaitingRoom queue to the EmergencyRoom queue if the WaitingRoom is not empty
        if (treatment_queue.empty()) {
            if(!wr_patient_priority_queue->patient_priority_queue.empty()){
                //Create a new Patient object pointing to the first Patient in the WaitingRoom queue
                Patient *patient = wr_patient_priority_queue->patient_priority_queue.top();
                
                //Remove first Patient object from WaitingRoom queue
                wr_patient_priority_queue->patient_priority_queue.pop();
                
                //Update the start_treatment_time attribute for the Patient
                int t_time = clock;
                patient->start_treatment_time = t_time;
                
                //Compute a random treatment time for the Patient between min_doctor_treatment_time and max_doctor_service_time
                Caregiver::get_care_time();
            }
        }
    }
            

            

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
    
    void update_caregivers(){
        for (auto a: caregivers){
            a->update();
        }
    }
 

    friend class Discharge;
    friend class Caregiver;
};

#endif /* EmergencyRoom_h */

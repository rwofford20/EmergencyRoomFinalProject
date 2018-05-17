//
//  EmergencyRoom.h
//  EmergencyRoom
//
//  Created by Rachel Wofford on 5/4/18.
//  Copyright � 2018 Rachel Wofford. All rights reserved.
//

#ifndef EmergencyRoom_h
#define EmergencyRoom_h

#include <queue>
#include <list>
#include <stack>
#include "Patient.h"
#include "Discharge.h"
#include "Caregiver.h"
#include "Random.h"
#include "Simulator.h"

class Simulator;

using std::queue;

//Accesses global variable from Simulator.h
extern Random my_random;

//Queue of Patients organized by priority number
extern std::queue<Patient*>treatment_queue;

//Takes Patient from WaitingRoom queue and adds it to EmergencyRoom queue
//Patient moves to the Disharge queue once they are done being treated in the Emergency Room
class EmergencyRoom
{
protected:
    //Number of doctors from user's input
    int num_doctors;
    //Number of nurses from user's input
    int num_nurses;
    
    Simulator *s = NULL;
    Caregiver *caregiver_pointer;
    
    //Pointer to Discharge queue
    Discharge *patient_discharge_queue;
    
    //Pointer to get patient_priority_queue in WaitingRoom that contains Patient objects
    WaitingRoom *wr_patient_priority_queue;
    
    
public:
    EmergencyRoom(Simulator *s1) {
        s = s1;
    }
    
    //Set the discharge queue
    void set_wr_patient_priority_queue(WaitingRoom *patient_priority_queue) {
        this->wr_patient_priority_queue = patient_priority_queue;
    }
    
    void set_patient_discharge_queue(Discharge *patient_discharge_queue) {
        this->patient_discharge_queue = patient_discharge_queue;
    }
    
    //Set the number of doctors
    void set_num_doctors(int num_doctors) {
        this->num_doctors = num_doctors;
    }
    
    //Set the number of nurses
    void set_num_nurses(int num_nurses) {
        this->num_nurses = num_nurses;
    }
    
    void add_patient_to_discharge(int clock)
    {
        
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
            Caregiver *c_giver = NULL;
            c_giver = patient->cg;
            
            c_giver->set_is_empty();
        }
    }
    
    //Executes if a doctor or nurse is available to treat a Patient
    void add_patient_to_treatment_queue(int clock);
    
    friend class Discharge;
    friend class Caregiver;
};

#endif /* EmergencyRoom_h */

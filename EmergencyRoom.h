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
#include <stack>
#include "Patient.h"
#include "Discharge.h"
#include "Caregiver.h"
#include "Random.h"

//Accesses global variable from Simulator.h
extern Random my_random;

//Queue of Patients organized by priority number
std::queue<Patient*> treatment_queue;

//Takes Patient from WaitingRoom queue and adds it to EmergencyRoom queue
//Patient moves to the Disharge queue once they are done being treated in the Emergency Room
class EmergencyRoom{
protected:
    //Number of doctors from user's input
    int num_doctors;
    //Number of nurses from user's input
    int num_nurses;

    Caregiver *caregivers;
    
    //Pointer to Discharge queue
    Discharge *patient_discharge_queue;
    
    //Pointer to get patient_priority_queue in WaitingRoom that contains Patient objects
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
        if (treatment_queue.empty())
        {
            //Patient is ready to see a caregiver
            if(!wr_patient_priority_queue->patient_priority_queue.empty())
            {
                //Create a new Patient object pointing to the first Patient in the WaitingRoom queue
                Patient *patient = NULL;
                    
                //If the caregiver has the proper clearance to see a patient
                Caregiver *c1 = NULL;
                
                //Stack of patients that cannot be treated
                std::stack<Patient*> patient_stack;
                
                //Find a patient with the a valid priority level
                do
                {
                    //Highest priority patient in the priortiy queue
                    patient = wr_patient_priority_queue->patient_priority_queue.top();
                    
                    //If no patients can be seen, break the for loop
                    if (wr_patient_priority_queue->patient_priority_queue.empty())
                    {
                        break;
                    }
                    
                    //Remove the patient that cannot be seen from the priority queue
                    wr_patient_priority_queue->patient_priority_queue.pop();
    
                    //Add the removed patient to the stack (these will be added back to the priority queue later)
                    patient_stack.push(patient);
                    
                }while(patient->getPriority() > c1->get_clearance_level());

                //Add a valid patient to be seen by the caregiver
                treatment_queue.push(patient);
                
                //Add patients in stack back to priortiy queue
                for (int i=0; i < patient_stack.size(); i++)
                {
                    Patient *p2 = NULL;
                    p2 = patient_stack.top();
                    patient_stack.pop();
                    wr_patient_priority_queue->patient_priority_queue.push(p2);
                }
                
                //Update the start_treatment_time attribute for the Patient
                int t_time = clock;
                patient->start_treatment_time = t_time;
                
                //Set the patient's treatment time to the calculated treatment time
                patient->treatment_time = t_time;

            }
        }
    }
    
    //Function to update the treatment and discharge queues
    void update_caregivers(int clock){
        add_patient_to_discharge(clock);
        add_patient_to_treatment_queue(clock);
    }

    friend class Discharge;
    friend class Caregiver;
};

#endif /* EmergencyRoom_h */

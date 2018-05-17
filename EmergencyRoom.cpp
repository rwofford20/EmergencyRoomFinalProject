#include "EmergencyRoom.h"
#include <queue>
#include <list>
#include <stack>
#include "Patient.h"
#include "Discharge.h"
#include "Caregiver.h"
#include "Random.h"
#include "Simulator.h"

std::queue<Patient*>treatment_queue;
Random my_random;

//Executes if a doctor or nurse is available to treat a Patient
void EmergencyRoom::add_patient_to_treatment_queue(int clock)
{
    //Move a Patient from the WaitingRoom queue to the EmergencyRoom queue if the WaitingRoom is not empty
    if (treatment_queue.empty())
    {
        //Patient is ready to see a caregiver
        if (!wr_patient_priority_queue->patient_priority_queue.empty())
        {
            //Create a new Patient object pointing to the first Patient in the WaitingRoom queue
            Patient *patient = wr_patient_priority_queue->patient_priority_queue.top();
            
            //Initialize a Caregiver object for this patient
            Caregiver *c1 = NULL;
            
            //Loop through the Caregivers to see who is available
            std::vector <Caregiver*> unavailable_caregivers;
            std::vector <Caregiver*> available_caregivers;
            s->get_Caregiver_Vector();
            
            
            //Loop to determine which Caregivers are available and adds them to their respective vectors
            for (int i = 0; i < s->caregivers.size(); i++)
            {
                c1 = s->caregivers[i];
                if (c1->get_is_busy() == false)
                {
                    available_caregivers.push_back(c1);
                }
                else
                {
                    unavailable_caregivers.push_back(c1);
                }
            }
            
            //Stack of patients that cannot be treated
            std::stack<Patient*> patient_stack;
            
            //Once an available Caregiver is found, assign them to a Patient
            for (int i = 0; i < available_caregivers.size(); i++)
            {
                //Break out of this loop if there are no patients in the waiting room
                if (wr_patient_priority_queue->patient_priority_queue.empty())
                {
                    break;
                }
                
                //Find an available Caregiver
                c1 = available_caregivers[i];
                
                //Set the Caregiver's care_time
                int c_time = 0;
                c_time = c1->get_care_time();
                
                //Locate the highest priority patient in the waiting room
                patient = wr_patient_priority_queue->patient_priority_queue.top();
                //Remove that patient from the waiting room queue
                wr_patient_priority_queue->patient_priority_queue.pop();
                
                //Compare patient priority to caregiver clearance level
                //If patient's priority is too high, add them to the stack of patients that can't be treated
                //If patient's priority is compatible with caregiver's clearance, add Patient to the treatment queue
                if (patient->getPriority() > c1->get_clearance_level()){
                    patient_stack.push(patient);
                }
                else{
                    //Add a valid patient to be seen by the caregiver
                    treatment_queue.push(patient);
                    
                    //Set patient's treatment time
                    patient->set_treatment_time(c_time);
                    //Mark Caregiver as busy
                    c1->set_is_busy();
                    
                    //Update the start_treatment_time attribute for the Patient
                    int t_time = clock;
                    patient->set_start_treatment_time(t_time);
                    
                    //Assign Caregiver to Patient
                    patient->set_caregiver(c1);
                }
                
            }

            //Add patients in stack back to priority queue
            for (int i = 0; i < patient_stack.size(); i++)
            {
                Patient *p2 = NULL;
                p2 = patient_stack.top();
                patient_stack.pop();
                wr_patient_priority_queue->patient_priority_queue.push(p2);
            }
        
        }
    }
};

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
    //Range of doctor service times
    int min_doctor_treatment_time = 1;
    int max_doctor_treatment_time = 20;
    
public:
    doctor(int num_doctors): min_doctor_treatment_time(1), max_doctor_treatment_time(20) {}
    
    //Loop to move a Patient from the EmergencyRoom queue to the Discharge queue if they are done being treated by a doctor
    //If the Patient moves to Discharge, this loop takes a Patient from the WaitingRoom queue and adds it to the EmergencyRoom queue
    void update(int clock)
    {
        // Executes if the EmergencyRoom is not empty
        if (!doctor_queue.empty()) {
                
            //Identifies Patient object at the front of the WaitingRoom priority queue
            Patient *patient = doctor_queue.front();
                
            //Checks if full treatment time has elapsed
            //If so, moves Patient from the EmergencyRoom queue to the Discharge queue
            if ((clock - patient->start_treatment_time) > patient->treatment_time) {
                    
                //Removes Patient from the EmergencyRoom queue
                doctor_queue.pop();
                    
                //Adds the Patient to the Discharge queue
                discharge_queue->the_queue.push(patient);
            }
        }
            
        //FACTOR IN HOW TO DIFFERENTIATE BETWEEN A DOCTOR AND A NURSE
        //Executes if a doctor is available to treat a Patient
        if (doctor_queue.empty()) {
                
            //Move a Patient from the WaitingRoom queue to the EmergencyRoom queue if the WaitingRoom is not empty
            if(!waiting_room_queue->the_queue.empty()){
                //Create a new Patient object pointing to the first Patient in the WaitingRoom queue
                Patient *patient = waiting_room_queue->the_queue.front();
                //Remove first Patient object from WaitingRoom queue
                waiting_room_queue->the_queue.pop();
                
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
    
    void setCareTime(int ct){
        care_time = ct;
    }
    int getCareTime(){
        return care_time;
    }
};

#endif /* Doctor_h */

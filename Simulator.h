//
//  Simulator.h
//  EmergencyRoom
//
//  Created by Rachel Wofford on 5/4/18.
//  Copyright © 2018 Rachel Wofford. All rights reserved.
//

#ifndef Simulator_h
#define Simulator_h

#include <iostream>
#include <string>
#include <stdexcept>
#include <limits>
#include <ios>
#include <iomanip>
#include <vector>
#include "WaitingRoom.h"
#include "EmergencyRoom.h"
#include "Discharge.h"
#include "Patient.h"
#include "Caregiver.h"
#include "Doctor.h"
#include "Nurse.h"
#include "Random.h"

using std::queue;

class Simulator
{
private:
    const int total_time = 10080;
    int clock;
    int num_doctors;
    int num_nurses;
    
    //Create the priority queue of Patients in the WaitingRoom
    WaitingRoom *patient_priority_queue;
    //Create a Discharge queue
    Discharge *discharge_queue;
    
    EmergencyRoom *e1 = NULL;
    
    //Vector of caregivers
    std::vector<Caregiver*> caregivers;
    
    int read_int(const std::string &prompt, int low, int high) {
        if (low >= high) // invalid range
            throw std::invalid_argument("invalid range specified");

        std::cin.exceptions(std::ios_base::failbit);

        int num = 0;
        while (true) {
            try {
                while (true) {
                    std::cout << prompt;
                    std::cin >> num;
                    if (num >= low && num <= high) { // within the specified range
                        std::cout << std::endl;
                        return num;
                    }
                }
            }
            catch (std::ios_base::failure) {
                std::cout << "Bad numeric string -- try again\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<int>::max(), '\n');
            }
        }
    }
    
public:
    Simulator() {
        
        //Create WaitingRoom and Discharge queues
        patient_priority_queue = new WaitingRoom();
        e1 = new EmergencyRoom(this);
        discharge_queue = new Discharge();
        
    }
    
    std::vector<Caregiver*> get_Caregiver_Vector(){
        return caregivers;
    }
    
    void data_entry()
    {
        //Output a welcome statement to the user
        std::cout << "Welcome to the CS273ville Hospital Simulator." << std::endl;
        
        //Prompt user to input average hourly patient arrival rate
        int rate = read_int("Please enter the average hourly patient arrival rate (patients/hour): ", 1, 59);
        
        //Turn the arrival rate into patients per minutes
        double arrival_rate = rate / 60.0;
        
        //Set the arrival rate for the WaitingRoom
        patient_priority_queue->set_arrival_rate(arrival_rate);
        
        //Prompt user to input number of doctors and accept input
        num_doctors = read_int("Please enter the number of doctors: ", 1, 500);
        
        for (int i = 0; i < num_doctors; i++) {
            caregivers.push_back(new Doctor(e1));
        }
        
        //Prompt user to input number of nurses and accept input
        num_nurses = read_int("Please enter the number of nurses: ", 1, 500);
        
        for (int i = 0; i < num_nurses; i++) {
            caregivers.push_back(new Nurse(e1));
        }
        
        //pass references to the priority queue in the WaitingRoom and the discharge queue to the EmergencyRoom queue
        e1->set_num_doctors(num_doctors);
        e1->set_num_nurses(num_nurses);
        e1->set_wr_patient_priority_queue(patient_priority_queue);
        e1->set_patient_discharge_queue(discharge_queue);
        
    }
    //Function to update the treatment and discharge queues
    void update_caregivers(int clock){
        e1->add_patient_to_treatment_queue(clock);
        e1->add_patient_to_discharge(clock);
    }

    void run_simulation() {
        //Run the simulation
        for (clock = 0; clock < total_time; ++clock) {
            //For each clock tick...
            //Update Waiting Room functions
            patient_priority_queue->update(clock);

            //Loop through each doctor and use the update function
            update_caregivers(clock);
                
            //Update Discharge functions
            discharge_queue->update(clock);
        }
    }
    
    void display_menu()
    {
        //Output information to the user
        //CALCULATE AVERAGE WAIT TIME
        int total_patients = discharge_queue->get_num_served();
        int wait_time = discharge_queue->get_total_wait();
        int total_visit_time = (total_patients / wait_time);
        
        std::cout << "Average wait time for patients in the Emergency Room: " << total_visit_time << std::endl;
        
        //OUTPUT MENU
        std::cout << "Menu" << std::endl;
    }
};

#endif /* Simulator_h */

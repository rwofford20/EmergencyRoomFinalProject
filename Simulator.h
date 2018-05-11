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

    //Vector of doctors
    std::vector<EmergencyRoom*> doctors;
    //Vector of nurses
    std::vector<EmergencyRoom*> nurses;
    
    int read_int(const std::string &prompt, int low, int high){
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
    Simulator(){
        //Create WaitingRoom and Discharge queues
        patient_priority_queue = new WaitingRoom();
        patient_discharge_queue = new Discharge();

    }
    
    void data_entry()
    {
        //Output a welcome statement to the user
        std::cout << "Welcome to the CS273ville Hospital Simulator." << std:: endl;
        
        //Prompt user to input average hourly patient arrival rate
        int rate = read_int("Please enter the average hourly patient arrival rate (patients/hour): ", 1, 59);
        //Turn the arrival rate into patients per minutes
        double arrival_rate = rate/60.0;
        
        //Set the arrival rate for the WaitingRoom
        waiting_room_queue->set_arrival_rate(arrival_rate);
        
        //Prompt user to input number of doctors and accept input
        num_doctors = read_int("Please enter the number of doctors: ", 1, 500);
        
        for (int i=0; i < num_doctors; i++){
            doctors.push_back(new EmergencyRoom());
        }
        
        //Prompt user to input number of nurses and accept input
        num_nurses = read_int("Please enter the number of nurses: ", 1, 500);
        
        for (int i=0; i < num_nurses; i++){
            nurses.push_back(new EmergencyRoom());
        }
        
        for (int i=0; i < num_doctors; i++){
            //set the number of doctors
            doctors[i].set_num_doctors(num_doctors);
            
            //pass references to the priority queue in the WaitingRoom and the discharge queue to the EmergencyRoom queue
            doctors[i]->set_patient_priority_queue(patient_priority_queue);
            doctors[i]->set_patient_discharge_queue(patient_discharge_queue);
        }
        
        for (int i=0; i < num_nurses; i++){
            //set the number of doctors
            nurses[i].set_num_nurses(num_nurses);
            
            //pass references to the priority queue in the WaitingRoom and the discharge queue to the EmergencyRoom queue
            nurses[i]->set_patient_priority_queue(patient_priority_queue);
            nurses[i]->set_patient_discharge_queue(patient_discharge_queue);
        }
        
    }
    
    void run_simulation(){
        
        //Run the simulation
        for (clock = 0; clock < total_time; ++clock){
            //For each clock tick...
            //Update Waiting Room functions
            patient_priority_queue->update(clock);
            //Loop through each doctor and use the update function
            for (int i=0; i < num_doctors; i++){
                doctors[i]->update(clock);
            }
            //Loop through each nurse and use the update function
            for (int i=0; i < num_nurses; i++){
                nurses[i]->update(clock);
            }
            //Update Discharge functions
            patient_discharge_queue->update(clock);
        }
    }
    
    void display_menu(){
        //Output information to the user
        //CALCULATE AVERAGE WAIT TIME
        std::cout << "Average wait time for patients in the Emergency Room: " <<std::endl;
        //OUTPUT MENU 
        std::cout << "Menu" << std::endl;
        
    }
};


#endif /* Simulator_h */

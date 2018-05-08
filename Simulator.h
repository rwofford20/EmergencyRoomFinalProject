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
#include <vector>
#include "WaitingRoom.h"
#include "EmergencyRoom.h"
#include "Discharge.h"
#include "Patient.h"
#include "Caregiver.h"
#include "Random.h"

using std::queue;

class Simulator
{
private:
    const int total_time = 10080;
    int clock;
    int num_doctors;
    int num_nurses;
    
    //Create a WaitingRoom queue
    WaitingRoom *waiting_room_queue;
    //Create a vector, nurses, that contains EmergencyRoom objects
    std::vector<EmergencyRoom *> nurses;
    //Create a vector, doctors, that contains EmergencyRoom objects
    std::vector<EmergencyRoom *> doctors;
    //Create a Discharge queue
    Discharge *discharge_queue;
    
    //std::vector <std::string> patients;
    
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
        waiting_room_queue = new WaitingRoom();
        discharge_queue = new Discharge();
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
        //Prompt user to input number of nurses and accept input
        num_nurses = read_int("Please enter the number of nurses: ", 1, 500);
        
        //Create a new WaitingRoom object and add it the nurses vector
        for (int i=0; i < num_nurses; i++){
            
            nurses.push_back(new EmergencyRoom());
        }
        
        //Create a new WaitingRoom object and add it to the doctors vectors
        for (int i=0; i < num_doctors; i++){
            doctors.push_back(new EmergencyRoom());
        }
        
    }
    
    void run_simulation(){
        //Run the simulation
        for (clock = 0; clock < total_time; ++clock){
            //For each clock tick...
            waiting_room_queue->update(clock);
            // loop through each gate and use the update function
            for (int i = 0; i < num_nurses; i++){
                nurses[i]->update_nurses(clock);
            }
            for (int i = 0; i < num_doctors; i++){
                doctors[i]->update_doctors(clock);
            }
            discharge_queue->update(clock);
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

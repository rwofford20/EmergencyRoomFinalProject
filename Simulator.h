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
    
    //Create a WaitingRoom queue
    WaitingRoom *waiting_room_queue;
    //Create a vector, nurses, that contains EmergencyRoom objects
    std::vector<EmergencyRoom *> nurses;
    //Create a vector, doctors, that contains EmergencyRoom objects
    std::vector<EmergencyRoom *> doctors;
    //Create a Discharge queue
    Discharge *discharge_queue;
    //Create a Doctor queue
    Doctor *doctor_queue;
    //Create a Nurse queue
    Nurse *nurse_queue;
    
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
        the_doctor_queue = new doctor_queue(num_doctors);
        //Prompt user to input number of nurses and accept input
        num_nurses = read_int("Please enter the number of nurses: ", 1, 500);
        the_nurse_queue = new nurse_doctor(num_nurses);
    }
    
    void run_simulation(){
        
        the_doctor_queue->set_waiting_room_queue(waiting_room_queue);
        the_nurse_queue->set_waiting_room_queue(waiting_room_queue);
        
        //Run the simulation
        for (clock = 0; clock < total_time; ++clock){
            //For each clock tick...
            //Update Waiting Room functions
            waiting_room_queue->update(clock);
            //Update Doctor and Nurse functions
            the_doctor_queue->update(clock);
            the_nurse_queue->update(clock);
            //Update Discharge functions
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

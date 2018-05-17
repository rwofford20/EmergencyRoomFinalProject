//
//  Simulator.h
//  EmergencyRoom
//
//  Created by Rachel Wofford on 5/4/18.
//  Copyright � 2018 Rachel Wofford. All rights reserved.
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
#include "UnitTest.h"

class Patient;

using std::queue;

class Simulator
{
private:
    //One week long of simulation time
    const int total_time = 10080;
    //Clockk to keep track of time
    int clock;
    //Number of doctors
    int num_doctors;
    //Number of nurses
    int num_nurses;
    
    WaitingRoom *patient_priority_queue; //Create the priority queue of Patients in the WaitingRoom
    Discharge *discharge_queue;	//Create a Discharge queue
    
    EmergencyRoom *e1 = NULL; //EmergencyRoom pointer
    
    std::vector<Caregiver*> caregivers; //Vector of caregivers
    
    //Determines if user input is valid
    int read_int(const std::string &prompt, int low, int high)
    {
        //Executes if number is in an invalid range
        if (low >= high)
            throw std::invalid_argument("invalid range specified");
        
        std::cin.exceptions(std::ios_base::failbit);
        
        int num = 0;
        while (true) {
            try {
                while (true) {
                    std::cout << prompt;
                    std::cin >> num;
                    //Executes if number is within the specified range
                    if (num >= low && num <= high) {
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
    Simulator();
    
    //Vector of Caregiver objects
    std::vector<Caregiver*> get_Caregiver_Vector() { return caregivers; }
    
    //Functions calls => Simulator.cpp
    void unit_testing(); 
    void data_entry();
    void update_caregivers(int clock); 
    void run_simulation();
    void display_menu();
    void ListOfPatients();
    void FindPatient();
    
    friend class EmergencyRoom;
};

#endif /* Simulator_h */

#include <iostream>
#include <string>
#include <stdexcept>
#include <limits>
#include <ios>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <iterator>
#include "WaitingRoom.h"
#include "EmergencyRoom.h"
#include "Discharge.h"
#include "Patient.h"
#include "Caregiver.h"
#include "Doctor.h"
#include "Nurse.h"
#include "Random.h"
#include "Simulator.h"
#include <set>

Simulator::Simulator()
{
    
    //Create WaitingRoom and Discharge queues
    patient_priority_queue = new WaitingRoom();
    e1 = new EmergencyRoom(this);
    discharge_queue = new Discharge();
    
}
void Simulator::data_entry()
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
        //this->caregivers = caregivers;
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
void Simulator::update_caregivers(int clock) {
    e1->add_patient_to_treatment_queue(clock);
    e1->add_patient_to_discharge(clock);
}

void Simulator::run_simulation() {
    //Run the simulation
    for (clock = 0; clock < total_time; ++clock)
    {
        //For each clock tick...
        
        //Update Waiting Room functions
        patient_priority_queue->update(clock);
        
        //Loop through each doctor and use the update function
        update_caregivers(clock);
        
        //Update Discharge functions
        discharge_queue->update(clock);
    }
}

void Simulator::display_menu()
{
    //User input for menu option
    int ans = 0;
    
    //Menu with list of names/search ability
    std::cout << "Menu: " << std::endl;
    std::cout << "1. List of all residents treated. " << std::endl;
    std::cout << "2. Search a patient by name. " << std::endl;
    std::cout << "3. Average wait time for patients in the Emergency Room. " << std::endl;
    std::cout << "4. Quit. " << std::endl;
    
    std::cin >> ans;
    
    //Checks inputted values
    while (ans < 1 || ans > 4)
    {
        std::cout << "Please enter a valid option. " << std::endl;
        std::cin >> ans;
    }
    
    //Output list of all patients treated
    if (ans == 1) { ListOfPatients(); }
    
    //Ask user to search by name.
    if (ans == 2) { FindPatient(); }
    
    if (ans == 3) {
        double total_patients = discharge_queue->get_num_served();	//Total number of patients served
        double wait_time = discharge_queue->get_total_wait(); //Total time patients waited
        
        //Average Wait time for ER
        double total_visit_time = (wait_time / total_patients);
        
        //Output of Average wait time
        std::cout << "Average wait time for patients in the Emergency Room: " << total_visit_time << " minutes " << std::endl;
        std::cout << std::endl;
        
        display_menu(); 
    }
    
}

void Simulator::ListOfPatients()
{
    
    //Loop through vector of treated_patients (in Discharge.h)
    for (int i = 0; i < discharge_queue->get_treated_patients().size(); i++)
    {
        std::vector<std::string> t_patients = discharge_queue->get_treated_patients();
    	std::cout << t_patients[i]<< std::endl;
    }
    
    display_menu();
}

void Simulator::FindPatient()
{
    std::multiset<Patient> p_records = discharge_queue->get_records();

    
    std::multiset<std::string> p_names;
    std::queue<int> p_priority;

    for (std::multiset<Patient>::iterator it=p_records.begin(); it!=p_records.end(); ++it)
    {
        p_names.insert(it->getName());
    }
    
    std::string search_name;
    
    std::cout << "Please enter a name to search. ";
    std::cin.ignore(); 
    std::getline(std::cin, search_name);
    
    double num_visits = p_names.count(std::string(search_name));
    
    std::cout << search_name << " visited the hospital " << num_visits << " times ";
    
    std::multiset<std::string>::iterator pit = p_names.lower_bound(std::string(search_name));
    for (; pit != p_names.upper_bound(std::string(search_name)); pit++) {
        //Convert the name back into a patient object and then get priority
        std::cout << "with priority levels of: " << std::endl;
        /*std::multiset<Patient>::iterator p_it = p_records.lower_bound(Patient(search_name));
        for (; p_it != p_records.upper_bound(Patient(search_name)); p_it++) {
            std::cout << p_it->getPriority() << std::endl;
        }*/
    }
    
    display_menu();
}

//  Patient.h
//  EmergencyRoom
//
//  Created by Rachel Wofford on 5/4/18.
//  Copyright � 2018 Rachel Wofford. All rights reserved.

#ifndef Patient_h
#define Patient_h

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <set>
#include <string>
#include <vector>

class Caregiver;

std::string getRandomName(std::string);

struct Patient
{
    Patient(int clock, int priority_level, std::string p_name) : priority_level(priority_level), name(p_name), patient_visits(-1), arrival_time(clock), start_treatment_time(-1), treatment_time(-1) {}
    
    Patient(std::string n)
    {
        name = n;
    }
    
    //Patient's priority level
    int priority_level;
    //Patient's name
    std::string name;
    //Number of times Patient has been to hospital
    int patient_visits;
    //Patient's arrival time
    int arrival_time;
    //When Patient began getting treated
    int start_treatment_time;
    //Hoe long it took Patient to get treated
    int treatment_time;
    //Patient's Caregiver
    Caregiver *cg = NULL;
    
    //Vector of patient names that have been treated
    std::vector<std::string> treated_patient_names;
    
    //Mutator function for generating Patient's name
    void setName() { name = getRandomName(); }
    //Accessor function for returning Patient's name
    std::string getName() const { return name; }
    //Mutator function for setting treatment time
    void set_treatment_time(int t) {treatment_time = t;}
    //Assigns a Caregiver to a Patient
    void set_caregiver(Caregiver *c_giver) { cg = c_giver; }
    //Mutator function for assigning Patient's starting treatment time
    void set_start_treatment_time(int t) {start_treatment_time = t;}
    //Accessor function for retriving Patient's starting treatment time
    int get_start_treatment_time(){return start_treatment_time;}
    //Increments number of Patient's visits
    void set_patient_visits(){patient_visits++;}
    //Returns number of Patient visits
    int get_patient_visits(){return patient_visits;}
    //Returns Patient's arrival time
    int get_arrival_time(){return arrival_time;}
    
    //Accessing vector of treated patients => set in getRandomName.
    std::vector<std::string> getTreatedNames() { return treated_patient_names; }
    
    //Provide set up for priority queue
    double getPriority() const { return priority_level; }
    
    //Allow access to individual patient records
    std::multiset<Patient> patient_record;
    
    //Adds patient to patient_record multiset
    void set_patient_record(Patient *p1){
        patient_record.insert(*p1);
    }
    
    //Returns nultiset of Patient Records
    std::multiset<Patient> getPatientRecord() {return patient_record;}
    
    //Random Name Generator
    static std::string getRandomName()
    {
        static std::vector<std::string> Full_names;
        std::string final_name;
        
        while (Full_names.size() == 0)
        {
            std::string line;
            
            //First Names
            std::vector<std::string> fnames; //Vector of first names
            std::fstream FirstNames; //File of First names
            
            //Open text file of first names
            FirstNames.open("/Users/rachelwofford/Desktop/residents_of_273ville.txt");
            
            if (FirstNames.fail())
            {
                std::cout << "Cannot open first name file" << std::endl;
            }
            
            //Store the first names in the vector names
            if (FirstNames.is_open())
            {
                
                while (std::getline(FirstNames, line))
                {
                    fnames.push_back(line);
                }
                FirstNames.close();
            }
            
            //Second Names
            std::vector<std::string> lnames; //Vector of first names
            std::fstream LastNames; //File of last names
            
            //Open the last name text file
            LastNames.open("/Users/rachelwofford/Desktop/surnames_of_273ville.txt");
            
            if (LastNames.fail())
            {
                std::cout << "Cannot open first name file" << std::endl;
                //throw invalid_argument
            }
            
            //Store the first names in the vector names
            if (LastNames.is_open())
            {
                //Outputs the list of last names twice so there will be family members (total of 2000 people in the population)
                for (int i = 0; i < 2; i++)
                {
                    while (std::getline(LastNames, line))
                    {
                        lnames.push_back(line);
                    }
                    LastNames.clear();
                    LastNames.seekg(0, std::ios::beg);
                }
                LastNames.close();
            }
            
            //Vector of full names
            
            
            for (int i = 0; i < lnames.size() - 1; i++)
            {
                int fnum = std::rand() % 1999 + 1;
                int lnum = std::rand() % 1999 + 1;
                
                //Random first name assigned to rand_name
                std::string rand_fname = fnames.at(fnum);
                std::string rand_lname = lnames.at(lnum);
                
                //Combines the first and last name into one string
                std::string fullname = rand_fname + " " + rand_lname;
                
                //Store the full name in the vector
                Full_names.push_back(fullname);
            }
            
            //Output a single name from the random number generator
        }
        
        int fn = rand() % 1998 + 1;
        final_name = Full_names.at(fn);
        
        //Return Patient's Name
        return final_name;
    }
    
    bool operator<(const Patient &other) {
        if (name < other.name)
            return true;
        else
            return false;
    }
    
    friend class Simulator;
};


bool operator<(const Patient& first, const Patient& second);

#endif /* Patient_h */

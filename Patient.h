//
//  Patient.h
//  EmergencyRoom
//
//  Created by Rachel Wofford on 5/4/18.
//  Copyright © 2018 Rachel Wofford. All rights reserved.
//

#ifndef Patient_h
#define Patient_h

#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <set>

std::string getRandomName(std::string);

struct Patient
{
    Patient(int clock, int priority_level, std::string name) : priority_level(-1), name(""), patient_visits(-1), arrival_time(clock), start_treatment_time(-1), treatment_time(-1) {}
    
    Patient(std::string n)
    {
        name = n;
    }
    
    int priority_level;
    std::string name;
    int patient_visits;
    int arrival_time;
    int start_treatment_time;
    int treatment_time;
    
    
    //set function for getting random name
    
    void setName(std::string final_name)
    {
        name = getRandomName(final_name);
    }
    
    std::string getName() const { return name; }

    double getPriority() const { return priority_level; }
    
    std::multiset<int> patient_record;
    

    friend class Simulator;
    
    
    
};

//Orders the patients priority
bool operator<(const Patient& first, const Patient& second)
{
    if (first.getPriority() < second.getPriority())
        return true;
    else if (first.getPriority() > second.getPriority())
        return true;
    else
        return false;
}

//Random Name Generator
std::string getRandomName(std::string name)
{
    std::string line;
    //First Names
    std::vector<std::string> fnames; //Vector of first names
    std::fstream FirstNames; //File of First names
    
    //Open text file of first names
    FirstNames.open("C:\\Users\\jbone\\OneDrive\\Desktop\\FirstNames.txt");
    
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
    LastNames.open("C:\\Users\\jbone\\OneDrive\\Desktop\\LastNames.txt");
    
    if (LastNames.fail())
    {
        std::cout << "Cannot open first name file" << std::endl;
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
            
            LastNames.close();
        }
    }

    //Vector of full names
    std::vector<std::string> Full_names;
    
    for (int i = 0; i < lnames.size() - 1; i++)
    {
        int fnum = std::rand() % 2000 + 1;
        int lnum = std::rand() % 2000 + 1;
        
        //Random first name assigned to rand_name
        std::string rand_fname = fnames.at(fnum);
        std::string rand_lname = lnames.at(lnum);
        
        //Combines the first and last name into one string
        std::string fullname = rand_fname + " " + rand_lname;
        
        //Store the full name in the vector
        Full_names.push_back(fullname);
    }

    //Output a single name from the random number generator
    for (int i = 0; i < Full_names.size(); i++)
    {
        int fn = rand() % 2000 + 1;
        std::string final_name = Full_names.at(fn);
    
        //Puts the randomly chosen name to the back of the Full_names vector
        Full_names.push_back(final_name);
        
        //Delete last element
        Full_names.pop_back();
        
        return final_name;
    }

#endif /* Patient_h */

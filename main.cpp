//
//  main.cpp
//  EmergencyRoom
//
//  Created by Rachel Wofford on 5/4/18.
//  Copyright � 2018 Rachel Wofford. All rights reserved.
//

#include <stdio.h>
#include "Simulator.h"

Simulator emergencyroom;

int main() {
    
    emergencyroom.data_entry();
    emergencyroom.run_simulation();
    emergencyroom.display_menu();
    
    return 0;
}

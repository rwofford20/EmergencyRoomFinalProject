//
//  UnitTest.h
//  FinalProject
//
//  Created by Rachel Wofford on 5/17/18.
//  Copyright © 2018 Rachel Wofford. All rights reserved.
//

#ifndef UnitTest_h
#define UnitTest_h

using namespace std;

class UnitTest{
public:
    //Unit test to check if Doctor has been given the correct clearance level
    void testSetDoctorClearance(int clearance){
        bool pass_or_fail = false;
        if (clearance == 20){
            pass_or_fail = true;
        }
        if (pass_or_fail == true)
        {
            cout << "Doctor clearance level test passed." << endl;
        }
        else {
            cout << "Doctor clearance level test failed." << endl;
        }
    }
    
    //Unit test to check if Nurse has been given the correct clearance level
    void testSetNurseClearance(int clearance){
        bool pass_or_fail = false;
        if (clearance == 10){
            pass_or_fail = true;
        }
        if (pass_or_fail == true)
        {
            cout << "Nurse clearance level test passed." << endl;
        }
        else {
            cout << "Nurse clearance level test failed." << endl;
        }
    }
    //Unit test to check if Doctor has been assigned a valid care time
    void testDoctorCareTime(int care_time){
        bool pass_or_fail = false;
        if (care_time <= 20 && care_time >= 1)
        {
            pass_or_fail = true;
        }
        if (pass_or_fail == true)
        {
            cout << "Doctor care time test passed." << endl;
        }
        else {
            cout << "Doctor care time test failed." << endl;
        }
    }
    //Unit test to check if Nurse has been assigned a valid care time
    void testNurseCareTime(int care_time){
        bool pass_or_fail = false;
        if (care_time <= 10 && care_time >= 1)
        {
            pass_or_fail = true;
        }
        if (pass_or_fail == true)
        {
            cout << "Nurse care time test passed." << endl;
        }
        else {
            cout << "Nurse care time test failed." << endl;
        }
    }
};
    



#endif /* UnitTest_h */

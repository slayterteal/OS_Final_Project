#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include "MedicalClinic.h"

/**
 * @brief takes in a medical professional's number then "performs" a medical checkup
 * based on the PER_PATIENT_CHECKUP_TIME.
 * 
 * @param number 
 */
void preformMedicalCheckup(int *number){
    sleep(((float)PER_PATIENT_CHECKUP_TIME)/1000.0);
    acceptPayment(number);
}
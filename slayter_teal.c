/**
 * @file slayter_teal.c
 * @author slayter teal (slayter.teal@gmail.com)
 * @brief performMedicalCheckup code
 * @Group E
 * @date 4/11/22
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <time.h>
#include "MedicalClinic.h"

/**
 * @brief takes in a medical professional's number then "performs" a medical checkup
 * based on the PER_PATIENT_CHECKUP_TIME.
 * 
 * @param number 
 */
void preformMedicalCheckup(int *number){
    usleep(((float)(PER_PATIENT_CHECKUP_TIME))*1000.0);
    acceptPayment(number);
}

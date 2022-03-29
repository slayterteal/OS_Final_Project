#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include "MedicalClinic.h"

/**
 * @brief takes in the respective number for the patient
 * then receives a medical checkup, before moving on to makePayment()
 * 
 * @param number 
 */
void getMedicalCheckup(int *number){
    printf("Patient %d (Thread ID: %ld): Receiving Checkup.\n", *number, pthread_self());
    sleep(((float)PER_PATIENT_CHECKUP_TIME)/1000.0);
    makePayment(number);
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include "MedicalClinic.h"

/**
 * @brief patient attempts to make a payment. The patient waits for a medical professional to arrive
 * at the register before making payment. At which point the patient will leave the clinic. 
 * 
 * @param number 
 */
void makePayment(int *number){
    sem_wait(&MEDICAL_PROFESSIONAL_AT_REGISTER);
    printf("Patient %d (Thread ID: %ld): Making Payment.\n", *number, pthread_self());
    sem_post(&MAKING_PAYMENT);
    leaveClinic(number, 1);
}
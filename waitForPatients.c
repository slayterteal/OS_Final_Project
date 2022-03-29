#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include "MedicalClinic.h"

/**
 * @brief takes in the argument pointer from pthread_create. The medical professional
 * then waits for patients to arrive.
 * 
 * @param args 
 * @return void* 
 */
void *waitForPatients(void *args){
    int number = *((int*)args);
    printf("Medical Professional %d (Thread ID: %ld): Waiting for Patient\n", number, pthread_self());
    
    // grab/wait a patient
    while(1){
        sem_wait(&WAITING_PATIENTS);
        preformMedicalCheckup(&number);
        sem_post(&AVAILABLE_MEDICAL_PROFESSIONALS);
    }  
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include "MedicalClinic.h"

/**
 * @brief takes in the number of the patient and a boolean value hasCheckup to 
 * determine if the patient has/has not received a checkup.
 * 
 * @param number 
 * @param hadCheckup 
 */
void leaveClinic(int* number, int hadCheckup){
    if(hadCheckup == 0){
        printf("Patient %d (Thread ID: %ld): Leaving Clinic without receiving Checkup.\n", *number, pthread_self());
    }
    else {
        printf("Patient %d (Thread ID: %ld): Leaving Clinic after receiving Checkup.\n", *number, pthread_self());
    }
    // pthread_exit(NULL);
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <time.h>
#include "MedicalClinic.h"


/**
 * Group E
 * Jacob Arthurs
 * 4/12/21
 * Jacob.Arthurs@OkState.edu
 * Description: implemented the waitForPatients and getMedicalCheckup methods. The waitForPatients
 * method allows medical professionals to wait until a patient arrives by running an infinite loop
 * that continuosly checks if there are patients that are waiting for a medical checkup. The 
 * getMedicalCheckup method allows medical professionals to get a medical checkup for a patient by
 * waiting for a predefined amount of time calculated earlier.
**/

void *waitForPatients(void *args){
    //variable to keep track of medical professional
    int num = *((int*) args);
    //Print out medical profesional num, and its thread ID
    printf("Medical Professional %d (Thread ID: %ld): Waiting for Patient\n", num, pthread_self());

    //start time
    startTime = clock();
    
    //Infinite loop to continuosly checks for waiting patients.
    while(1){
        //semaphore to wait until a patient is waiting
        sem_wait(&WAITING_PATIENTS);
        //Once a patient arrives, call the performMedicalCheckup method
        
        preformMedicalCheckup(&num);
        //Once a patient has been sent to get a medical checkup, release the semaphore
        sem_post(&AVAILABLE_MEDICAL_PROFESSIONALS);
        
    }  
    
    
}

void getMedicalCheckup(int *num){
    //Print out patient num, and its thread ID
    printf("Patient %d (Thread ID: %ld): Receiving Checkup.\n", *num, pthread_self());
    //Wait X seconds, where X is the calculated time the checkup will take
    usleep(((float)PER_PATIENT_CHECKUP_TIME)*1000.0);
    //After checkup is done, call the makePayment method
    makePayment(num);
    patientEnd = clock();
    endTime = clock();

    //end time
    //printf("%f",(double)(endTime));
    avgPatientWait += (double)(patientEnd - patientStart);
    avgProfTime += (double)(endTime - startTime);

    ++goodCheckups;
}

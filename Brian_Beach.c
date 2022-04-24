/**
 * Group E
 * Brian Beach
 * 4/12/21
 * brian.beach10@okstate.edu
 * Description: implemented the makePayment and acceptPayment funcitons to be able to
 * have threads for making and accepting payments. Also implemented leaveClinic to tell when 
 * a patient is leaving the clinic by checking if the patient had checkup
 * 
**/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#include "MedicalClinic.h"



//make payment function to use if patient goes to make payment. Takes Patients number as input
void makePayment(int *number){
    //semaphore to wait until medical_professional_at_register is available
    sem_wait(&MEDICAL_PROFESSIONAL_AT_REGISTER);

    //print out patient number and thread id when client is making payment
    printf("Patient %d (Thread ID: %ld): Making Payment.\n", *number, pthread_self());

    //unlock semaphore when payment made
    sem_post(&MAKING_PAYMENT);

    //calls leaveClinic with patient number and 1 (boolean) meaning patient made payment
    leaveClinic(number, 1);
}

//function if payment is accepted, prints out medical professional as well as the threadid
void acceptPayment(int *number){
    //semaphores for waiting for someone to be at register and unlocking when at register

    sem_wait(&CASH_REGISTER);
    sem_post(&MEDICAL_PROFESSIONAL_AT_REGISTER);
    printf("Medical Professional %d (Thread ID: %ld): Accepting payment.\n", *number, pthread_self());

    //make semaphore for making payment wait and unlock cash register semaphore
    sem_wait(&MAKING_PAYMENT);
    sem_post(&CASH_REGISTER);
}


//leaveClinic function to print out if patient is leaving the clinic 
//patient number and hadCheckup (used as bool) parameters
void leaveClinic(int* number, int hadCheckup){
    //prints patient number and if leaving with/without checkup
    if(hadCheckup == 0){
        printf("Patient %d (Thread ID: %ld): Leaving Clinic without receiving Checkup.\n", *number, pthread_self());
        ++leaveCount;
    }
    else {
        printf("Patient %d (Thread ID: %ld): Leaving Clinic after receiving Checkup.\n", *number, pthread_self());
        
    }
    
}



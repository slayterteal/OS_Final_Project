/*
michael douglas
Michael.douglas@okstate.edu
Group E
date 4/11/22
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include "MedicalClinic.h"

/**
 * @brief After entering the waiting room the patient will sit on a sofa if it is available
 * or stand if there are no sofas available. The patient then waits for an available medical
 * professional to receive service. 
 * 
 * @param number 
 */
void sitOnSofa(int *number){
    // get the current number of available sofas
    int number_of_available_sofas = 0;
    sem_getvalue(&NUMBER_OF_AVAILABLE_SOFAS, &number_of_available_sofas); 

    // if there are no sofas stand, else sit
    if(number_of_available_sofas <= 0){
        printf("Patient %d (Thread ID: %ld): Standing in the waiting room.\n", *number, pthread_self());
        // add patient to number of patients waiting.
        sem_post(&WAITING_PATIENTS); 

        // wait for available doctor
        sem_wait(&AVAILABLE_MEDICAL_PROFESSIONALS);
        sem_post(&REMAINING_WAITING_ROOM_CAPACITY);
        getMedicalCheckup(number);
    }
    else{
        sem_wait(&NUMBER_OF_AVAILABLE_SOFAS);
        printf("Patient %d (Thread ID: %ld): Sitting on a sofa in the waiting room.\n", *number, pthread_self());
        
        // add patient to number of patients waiting.
        sem_post(&WAITING_PATIENTS); 

        // wait for available doctor
        sem_wait(&AVAILABLE_MEDICAL_PROFESSIONALS);
        sem_post(&NUMBER_OF_AVAILABLE_SOFAS);
        sem_post(&REMAINING_WAITING_ROOM_CAPACITY);
        getMedicalCheckup(number);
    }
}

/**
 * @brief takes in a pointer of args from pthread_create containing the number for
 * the respective patient. The patient then joins the waiting room if there are open spots 
 * or leaves without receiving any service. 
 * 
 * @param args 
 * @return void* 
 */
void *enterWaitingRoom(void *args){
    int number = *((int*)args);
    printf("Patient %d (Thread ID: %ld): Arrived at the Clinic\n", number, pthread_self());
    
    // get current number of open places in the waiting room.
    int remaining_waiting_room_capacity = 0;
    sem_getvalue(&REMAINING_WAITING_ROOM_CAPACITY, &remaining_waiting_room_capacity);
    
    // if there are no more spots in the room, leave the clinic
    if(remaining_waiting_room_capacity <= 0){
        leaveClinic(&number, 0); // leave w/o checkup
    }
    else{
        sem_wait(&REMAINING_WAITING_ROOM_CAPACITY);
        sitOnSofa(&number);
    }
    pthread_exit(NULL);
}
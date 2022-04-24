/**
 * @file main.c
 * @author slayter teal (slayter.teal@gmail.com)
 * @brief main runner for the Final Project
 * @Group E
 * @date 4/11/22
 * compile: gcc *.c -o a.out -lpthread
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include "MedicalClinic.h"

// statistical trackers
/*
Keeping track of:
- Number of sucessful checkups
- Average waiting time for a medical professional // ms
- number of patients that left
- Average wait time for patients // ms
*/

int NUMBER_OF_MEDICAL_PROFESSIONALS = 0; 
int NUMBER_OF_PATIENTS = 0;
int NUMBER_OF_SOFAS = 0; 
int WAITING_ROOM_CAPACITY = 0;
int MAXIMUM_ARRIVAL_TIME = 0;
int PER_PATIENT_CHECKUP_TIME = 0;

sem_t NUMBER_OF_PATIENTS_TO_ARRIVE;
sem_t WAITING_PATIENTS;
sem_t REMAINING_WAITING_ROOM_CAPACITY; 
sem_t AVAILABLE_MEDICAL_PROFESSIONALS; 
sem_t NUMBER_OF_AVAILABLE_SOFAS;
sem_t MEDICAL_PROFESSIONAL_AT_REGISTER; // mutex
sem_t CASH_REGISTER; // mutex
sem_t MAKING_PAYMENT; // mutex

/**
 * @brief goal of the main loop is to take user input, generate the thread pool,
 * and delegate the threads to individual users. 
 * 
 * @return int 
 */
int main(int argc, char* argv[]){
    if(argc < 7){
        printf("Not enough command-line arguments...\n");
        printf("./a.out numberOfMedicalProfessionals numberOfPatients waitingRoomCapacity numberOfSofas maximumArrivalTime perPatientCheckupTime\n");
        return 0;
    }
    // else {
    //     printf("String to int conversion: %d, %d, %d, %d, %d, %d\n ", atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), atoi(argv[5]), atoi(argv[6]));
    //     return 0;
    // }

    // TODO: Set from args ======================================
    NUMBER_OF_MEDICAL_PROFESSIONALS = atoi(argv[1]); 
    NUMBER_OF_PATIENTS = atoi(argv[2]);
    NUMBER_OF_SOFAS = atoi(argv[3]); 
    WAITING_ROOM_CAPACITY = atoi(argv[4]);
    MAXIMUM_ARRIVAL_TIME = atoi(argv[5]);
    PER_PATIENT_CHECKUP_TIME = atoi(argv[6]);
    // ==================================================================

    // initalize our variables
    pthread_t medicalProfessionalThreadPool[NUMBER_OF_MEDICAL_PROFESSIONALS];
    pthread_t patientThreadPool[NUMBER_OF_PATIENTS];
    sem_init(&REMAINING_WAITING_ROOM_CAPACITY, 0, WAITING_ROOM_CAPACITY);
    sem_init(&NUMBER_OF_AVAILABLE_SOFAS, 0, NUMBER_OF_SOFAS);
    sem_init(&AVAILABLE_MEDICAL_PROFESSIONALS, 0, NUMBER_OF_MEDICAL_PROFESSIONALS);
    sem_init(&WAITING_PATIENTS, 0, 0);
    sem_init(&CASH_REGISTER, 0, 1); // a binary semaphore (i.e. a mutex);
    sem_init(&MEDICAL_PROFESSIONAL_AT_REGISTER, 0, 0);
    sem_init(&MAKING_PAYMENT, 0, 0);
    
    /*
    Medical professionals should be assigned to a thread, then 
    automatically begin waiting for patients.
    */
    int medicalProfessionalNumber[NUMBER_OF_MEDICAL_PROFESSIONALS];
    for(int i = 0; i < NUMBER_OF_MEDICAL_PROFESSIONALS; i++){
        medicalProfessionalNumber[i] = i;
        if(pthread_create(&medicalProfessionalThreadPool[i], NULL, &waitForPatients, (void *)&medicalProfessionalNumber[i]) != 0){
            printf("Failure to create thread...\n");
        }
    }

    /*
    Create Patient Threads
    */
    int patientNumber[NUMBER_OF_PATIENTS];
    for(int i = 0; i < NUMBER_OF_PATIENTS; i++){
        patientNumber[i] = i;
        if(pthread_create(&patientThreadPool[i], NULL, &enterWaitingRoom, (void *)&patientNumber[i]) != 0){
            printf("Failure to create thread...\n");
        }
        sleep(((float)MAXIMUM_ARRIVAL_TIME)/1000.0); // wait MAXIMUM_ARRIVAL_TIME(ms) before the next patient arrives.
    }
    // the main thread will wait untill all patients have left.
    for(int i = 0; i < NUMBER_OF_PATIENTS; i++){
        pthread_join(patientThreadPool[i], NULL);
    }

    printf("\nStatistical Analysis goes here...\n");

    //analysis
    printf("-------------------------------------------------------\n");
    printf("Number of successful Checkups: %d\n", goodCheckups);
    avgProfTime = avgProfTime / (NUMBER_OF_MEDICAL_PROFESSIONALS * 1000);
    printf("Average waiting time for Medical Professionals: %0.1f ms\n", avgProfTime);
    printf("Number of Patients that left: %d\n", leaveCount);
    avgPatientWait = avgPatientWait / (NUMBER_OF_MEDICAL_PROFESSIONALS* 1000);
    printf("Average wait time for patients: %0.1f\n", avgPatientWait);

    // free memory/destroy mutexes or semaphores
    sem_destroy(&REMAINING_WAITING_ROOM_CAPACITY);
    sem_destroy(&NUMBER_OF_AVAILABLE_SOFAS);
    sem_destroy(&AVAILABLE_MEDICAL_PROFESSIONALS);
    sem_destroy(&WAITING_PATIENTS);
    sem_destroy(&CASH_REGISTER);
    sem_destroy(&MEDICAL_PROFESSIONAL_AT_REGISTER);
    sem_destroy(&MAKING_PAYMENT);

    return 0;
}

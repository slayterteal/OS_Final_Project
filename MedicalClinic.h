/**
 * @file MedicalClinic.h
 * @author slayter teal (slayter.teal@okstate.edu)
 * @brief header file for the OS Final Project, contains functions
 * and variable definitions needed for the execution of the program.
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef MEDICALCLINIC_H_
#define MEDICALCLINIC_H_


#include <semaphore.h>

// Define the global variables/user input variables
extern int NUMBER_OF_MEDICAL_PROFESSIONALS; 
extern int NUMBER_OF_PATIENTS;
extern int WAITING_ROOM_CAPACITY; 
extern int NUMBER_OF_SOFAS; 
extern int MAXIMUM_ARRIVAL_TIME; // ms
extern int PER_PATIENT_CHECKUP_TIME; // ms

// define some semaphores/mutexes
extern sem_t NUMBER_OF_PATIENTS_TO_ARRIVE;
extern sem_t WAITING_PATIENTS;
extern sem_t REMAINING_WAITING_ROOM_CAPACITY; 
extern sem_t AVAILABLE_MEDICAL_PROFESSIONALS; 
extern sem_t NUMBER_OF_AVAILABLE_SOFAS;
extern sem_t MEDICAL_PROFESSIONAL_AT_REGISTER; // mutex
extern sem_t CASH_REGISTER; // mutex
extern sem_t MAKING_PAYMENT; // mutex

// medical professional functions
void *waitForPatients(void *args);
void preformMedicalCheckup(int *number);
void acceptPayment(int *number);

// patient functions
void *enterWaitingRoom(void *args);
void sitOnSofa(int *number);
void getMedicalCheckup(int *number);
void makePayment(int *number);
void leaveClinic(int *number, int hadCheckup);

#endif

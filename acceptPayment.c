#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include "MedicalClinic.h"

void acceptPayment(int *number){
    sem_wait(&CASH_REGISTER);
    sem_post(&MEDICAL_PROFESSIONAL_AT_REGISTER);
    printf("Medical Professional %d (Thread ID: %ld): Accepting payment.\n", *number, pthread_self());
    sem_wait(&MAKING_PAYMENT);
    sem_post(&CASH_REGISTER);
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include "MedicalClinic.h"

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
#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h> 
#include <sys/sem.h>

typedef struct {
    long messageType;
    int airportArrival;
    int airportDeparture;
    int planeID;
    int weightOfPlane;
    int planeType;
    int noOfPassengers;
    int flag;
} PlaneDetails;

#define KEY_PATH "plane.c"

int main(){
    
    key_t key = ftok(KEY_PATH, 'Z');
    if (key == -1) {
        perror("Failed to generate IPC key");
        exit(1);
    }

    char response;
    do {
        printf("Do you want the Air Traffic Control System to terminate?(Y for Yes and N for No) : \n");
        scanf(" %c", &response);

        // Process the response
        if (response == 'Y' || response == 'y') {

        } else if (response == 'N' || response == 'n') {

        } else {
            // Invalid response, handle accordingly
            printf("Invalid response. Please enter Y or N.\n");
        }
    } while (response != 'N' && response != 'n');

    int msgQueue = msgget(key, 0666);
    if (msgQueue == -1) {
        perror("Failed to get the message queue");
        exit(1);
    }

    PlaneDetails planeDetails;
    planeDetails.messageType= 999;
    if (msgsnd(msgQueue, &planeDetails, sizeof(PlaneDetails) - sizeof(long), 0) == -1) {
        perror("Failed to send the message");
        exit(1);
    }
    return 0;
}
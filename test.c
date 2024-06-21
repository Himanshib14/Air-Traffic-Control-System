#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <pthread.h>
#include <semaphore.h>
#include <limits.h>

#define MAX_AIRPORTS 10
#define MAX_RUNWAYS 10
#define BACKUP_LOAD_CAPACITY 15000

#define KEY_PATH "plane.c"

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

int main(){
    key_t key = ftok(KEY_PATH, 'Z');
    if (key == -1) {
        perror("Failed to generate IPC key");
        exit(1);
    }

    int msgQueue = msgget(key, 0666 | IPC_CREAT);
    if (msgQueue == -1) {
        perror("Failed to get the message queue");
        exit(1);
    }
    if (msgctl(msgQueue, IPC_RMID, NULL) == -1) {
        perror("Failed to remove the message queue");
        exit(1);
    }
}
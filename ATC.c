#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>

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

void func1(PlaneDetails planeDetails) {
    FILE *file = fopen("AirTrafficController.txt", "a");
    if (file == NULL) {
        perror("Failed to open the file");
        return;
    }

    // Write details to the file
    char msg[100];
    sprintf(msg, "Plane %d has departed from Airport %d and will land at Airport %d.\n", planeDetails.planeID, planeDetails.airportDeparture, planeDetails.airportArrival);
    fprintf(file, "%s", msg);

    // Close the file
    fclose(file);
}

int main() {
    int numberOfAirports;
    printf("Enter the number of airports to be handled/managed :");
    scanf("%d",&numberOfAirports);

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

    PlaneDetails planeDetails;
    planeDetails.messageType=0;
    while(1){
        if (msgrcv(msgQueue, &planeDetails, sizeof(PlaneDetails) - sizeof(long), 1, 0) == -1) {
            perror("Failed to receive the message");
            exit(1);
        }

        if (msgrcv(msgQueue, &planeDetails, sizeof(PlaneDetails) - sizeof(long), 999, IPC_NOWAIT) == -1) {

        }
        if(planeDetails.messageType == 999){break;}

        planeDetails.messageType = 2; // Set the message type for B to C communication
        if (msgsnd(msgQueue, &planeDetails, sizeof(PlaneDetails) - sizeof(long), 0) == -1) {
            perror("Failed to send the message");
            exit(1);
        }

        // Receive the message from departure airport
        if (msgrcv(msgQueue, &planeDetails, sizeof(PlaneDetails) - sizeof(long), 3, 0) == -1) {
            perror("Failed to receive the message");
            exit(1);
        }

        func1(planeDetails);

        printf("\n");

        // Inform arrival airport about the arrival of the plane
        planeDetails.messageType = 4;
        if (msgsnd(msgQueue, &planeDetails, sizeof(PlaneDetails) - sizeof(long), 0) == -1) {
            perror("Failed to send the message");
            exit(1);
        }
        printf("message of type 4 sent!\n");

        // Receive the message about unloading process completion
        if (msgrcv(msgQueue, &planeDetails, sizeof(PlaneDetails) - sizeof(long), 5, 0) == -1) {
            perror("Failed to receive the message");
            exit(1);
        }
        printf("message of type 5 recd!\n");

        planeDetails.messageType = 6;
        if (msgsnd(msgQueue, &planeDetails, sizeof(PlaneDetails) - sizeof(long), 0) == -1) {
            perror("Failed to send the message");
            exit(1);
        }
        printf("message of type 6 sent!\n");
    }

    planeDetails.messageType = 6;
    if (msgsnd(msgQueue, &planeDetails, sizeof(PlaneDetails) - sizeof(long), 0) == -1) {
        perror("Failed to send the message");
        exit(1);
    }

    if (msgctl(msgQueue, IPC_RMID, NULL) == -1) {
        perror("Failed to remove the message queue");
        exit(1);
    }

    return 0;
}

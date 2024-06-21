#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h> 

#define read_end 0
#define write_end 1
#define KEY_PATH "plane.c"

typedef struct{
    int luggageWeight;
    int bodyWeight;
} Weights;

typedef struct{
    long messageType;
    int airportArrival;
    int airportDeparture;
    int planeID;
    int weightOfPlane;
    int planeType;
    int noOfPassengers;
    int flag;
}PlaneDetails;

int func1(int seats){ 
    int pipefd[seats][2];
    int total_weight=0;
    for(int i=0;i<seats;i++){
        pid_t child_pid;

        if(pipe(pipefd[i]) == -1){
            perror("pipe creation failed");
            return 1;
        }

        child_pid = fork();
        
        if(child_pid == -1){
            perror("fork failed");
            return 1;
        }
        else if(child_pid==0){
            //child process :
            close(pipefd[i][read_end]);
            int luggageWeight, bodyWeight;
            printf("Enter Weight of Your Luggage (max. 25kg): ");
            scanf("%d", &luggageWeight);
            printf("Enter your Body Weight (between 10kg and 100kg): ");
            scanf("%d", &bodyWeight);

            Weights weights;
            weights.luggageWeight = luggageWeight;
            weights.bodyWeight = bodyWeight;
            write(pipefd[i][write_end], &weights, sizeof(weights));
            close(pipefd[i][write_end]);
            exit(0);
        }   
        else{
            //parent process :
            wait(NULL);
            close(pipefd[i][write_end]);
            Weights weights;
            read(pipefd[i][read_end], &weights, sizeof(weights));
            total_weight+= weights.luggageWeight + weights.bodyWeight;
        }
    }
    //adding the weight of the crew members :
    total_weight+= 75*7;
    return total_weight;
}

int main(){
    int planeID,planeType;
    printf("Enter Plane ID: ");
    scanf("%d",&planeID);
    printf("Enter Type of Plane: ");
    scanf("%d",&planeType);
    PlaneDetails planeDetails;
    planeDetails.planeID = planeID;
    planeDetails.planeType = planeType;
    if(planeType){
        //passenger plane
        int seats;
        printf("Enter Number of Occupied Seats (between 1 and 10): ");
        scanf("%d",&seats);
        int weightOfPassengerPlane = func1(seats);
        planeDetails.noOfPassengers = seats;
        planeDetails.weightOfPlane = weightOfPassengerPlane;
    }
    else{
        //cargo plane 
        int items, avgWeight;
        printf("Enter the number of Cargo Items (between 1 and 100): ");
        scanf("%d",&items);
        printf("Enter Average Weight of Cargo Items (between 1 and 100):");
        scanf("%d", &avgWeight);
        //taking into consideration the weight of crew members :
        int weightOfCargoPlane = items*avgWeight + 75*2;
        planeDetails.weightOfPlane = weightOfCargoPlane;
    }   
    int airportArrival, airportDeparture;
    printf("Enter Airport Number for Departure (between 1 and 10): ");
    scanf("%d", &airportDeparture);
    printf("Enter Airport Number for Arrival (between 1 and 10): ");
    scanf("%d", &airportArrival);
    planeDetails.airportArrival = airportArrival;
    planeDetails.airportDeparture = airportDeparture;

    // Generate a unique IPC key
    key_t key = ftok(KEY_PATH, 'Z');
    if (key == -1) {
        perror("Failed to generate IPC key");
        exit(1);
    }

    // Create and get the message queue
    int msgQueue = msgget(key, 0666);
    if (msgQueue == -1) {
        perror("Failed to create the message queue");
        exit(1);
    }

    // Send the details struct via the message queue
    planeDetails.messageType = 1;
    if (msgsnd(msgQueue, &planeDetails, sizeof(PlaneDetails) - sizeof(long), 0) == -1) {
        perror("Failed to send the message from plane to ATC");
        exit(1);
    }

    // Receive the modified details struct from the message queue
    int msgtyp = 6;
    if (msgrcv(msgQueue, &planeDetails, sizeof(PlaneDetails), msgtyp, 0) == -1) {
        perror("Failed to receive the message");
        exit(1);
    }

    printf("\nPlane %d has successfully travelled from Airport %d to Airport %d!", planeID, airportDeparture, airportArrival);
    return 0;
}

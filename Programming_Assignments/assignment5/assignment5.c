/* Assignment 5 | CS360
 * Author: Amethyst Skye
 *
 * Description: A program written in C which will address the dining philosophers problem.
 * There will be 5 philosophers and 5 chopsticks at the table. Each philosopher will
 * repeat a cycle of eating and thinking until all philosophers have eaten for a total of
 * at least 100 seconds. Once a philosopher has eaten for 100 seconds, they will leave (terminate).
 *
 * Rules:
 * - In order to eat, a philosopher must acquire both the chopsticks adjacent to them.
 * If they cannot, they are made to wait until they can.
 *
 * - Once they have a pair of chopsticks, they eat for the expected period of time and then
 * replace (release) the chopsticks onto the table and begin their period of thinking.
 *
 */

#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <math.h>
#include <time.h>

/* Definitions */
#define N 5
#define DOWN 1
#define UP -1
#define THINK 0
#define EATING 1
#define LEFT (procNum == 0) ? N - 1 : procNum - 1
#define RIGHT (procNum + 1) % N

int randomGaussian(int mean, int stddev) {
    double mu = 0.5 + (double) mean;
    double sigma = fabs((double) stddev);
    double f1 = sqrt(-2.0 * log((double) rand() / (double) RAND_MAX));
    double f2 = 2.0 * 3.14159265359 * (double) rand() / (double) RAND_MAX;
    if (rand() & (1 << 5))
        return (int) floor(mu + sigma * cos(f2) * f1);
    else
        return (int) floor(mu + sigma * sin(f2) * f1);
}

/*************************************************************************************/

int main(int argc, char *argv[]){

    /*counter, process ID, semaphore ID, shared mem ID, Semaphore Value holder, philo number*/
    int i, procID, chops, shmID, semVal, procNum;

    /*sembuf for chopstick singals*/
    struct sembuf stick;
    stick.sem_op = 1;
    stick.sem_flg = 0;

    /*Create Shared Memory for philo states*/
    shmID = shmget(IPC_PRIVATE, N, IPC_CREAT | IPC_EXCL | 0600);
    char *philState = (char*) shmat(shmID, NULL, 0);

    /*Create a set of N Semaphores for N Chopsticks*/
    if((chops = semget(IPC_PRIVATE, N, IPC_CREAT | IPC_EXCL | 0600)) == -1){
        fprintf(stderr, "Error(semget) -- %s\n", strerror(errno));
        exit(1);
    }
    printf("Semaphore ID = %d\n", chops);

    /*Initialize semaphores to 1*/
    for(i = 0; i < N; i++){
        if((semVal = semctl(chops, i, SETVAL, 1)) == -1){
            fprintf(stderr, "Error(semctl) -- %s\n", strerror(errno));
            exit(1);
        }

        printf("Semaphore %d initial value = %d\n", i, stick.sem_op);
    }

    /*Philosopher Forking*/
    for (i = 0; i < N; i++){
        procID = fork();
            /*Error*/
            if(procID == -1){
                fprintf(stderr, "Error(fork) -- %s\n", strerror(errno));
                exit(1);
            }
            /*Children*/
            if(procID == 0){
                procNum = i;
                break;
            }
    }

    /*Dining*/
    switch(procID){
            /*Children*/
            case 0:
                int eat = 0, think = 0, cycles = 0;
                struct sembuf stick[1] = {{procNum, -1, 0}};
                srand(procNum);
                printf("Forked Philosopher %d (process %d)\n", procNum, getpid());

                while(eat <= 100){
                    /*Start with thinking*/
                    philState[procNum] = THINK;
                    time_t t;
                    t = randomGaussian(12,5);
                    think += t;
                    printf("Philosopher %d is thinking for %d seconds (%d)\n", procNum, t, eat);
                    sleep(t % N); /*to allow for output to print quicker*/
                    fflush(stdout);

                    /*Waiting after thinking*/
                    printf("Philosopher %d wants chopsticks %d and %d.\n", procNum, procNum, RIGHT);
                    fflush(stdout);

                    /*If philosopher's turn to eat*/
                    if ((philState[procNum] == THINK) && (philState[LEFT] != EATING) && (philState[RIGHT] != EATING)){
                            philState[procNum] = EATING;
                            t = randomGaussian(15,5);

                            /*Pick up Chopsticks*/
                            stick->sem_num = procNum;
                            stick->sem_op = UP;
                            semop(chops, stick, 1);
                            stick->sem_num = RIGHT;
                            stick->sem_op = UP;
                            semop(chops, stick, 1);
                            printf("Philosopher %d has obtained chopsticks %d and %d\n", procNum, procNum, RIGHT);
                            printf("Philosopher %d is eating for %d seconds (%d)\n", procNum, t, (eat += t));
                            fflush(stdout);
                            //eat += t;
                            sleep(t % N); /*to allow for output to print quicker*/

                            /*Lay Chopsticks down*/
                            printf("Philosopher %d is laying down chopsticks %d and %d\n", procNum, procNum, RIGHT);
                            fflush(stdout);
                            stick->sem_num = RIGHT;
                            stick->sem_op = DOWN;
                            semop(chops, stick, 1);
                            stick->sem_num = procNum;
                            stick->sem_op = DOWN;
                            semop(chops, stick, 1);
                            philState[procNum] = THINK;
                            cycles++;
                    }
                }
                printf("Philosopher %d ate for %d seconds and thought for %d seconds over %d cycles.\n", procNum, eat, think, cycles);
                printf("Process %d terminated with status 0\n", getpid());
                fflush(stdout);
                exit(0);
            /*Parents*/
            default:
                for(i = 0; i < N; i++) wait(NULL);
                if((semctl(chops, N, IPC_RMID) == -1)){
                    fprintf(stderr, "Error(semctl) -- %s\n", strerror(errno));
                    exit(1);
                }
    }
    return 0;
}

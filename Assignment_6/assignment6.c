/* Assignment 6 | CS360
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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define _GNU_SOURCE
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <sys/types.h>
#include <math.h>
#include <time.h>

#define N 5 /*number of philosophers*/
#define MAXEAT 100
#define RIGHT (philo + 1) % N

/*This allows us to see thread id*/
pid_t gettid(void);

/*Mutex Declartion*/
pthread_mutex_t chops[N];

/*Ben's code for generating a random number*/
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

/*Philosopher Function*/
static void *philosopher(void *n){
    int philo = *(int *)n;
    int eat = 0, think = 0, cycles = 0;
    srand(philo);
    printf("Thread %d created.\n", gettid());
    printf("Philospoher %d joined the table.\n", philo);

    while(eat <= MAXEAT){
        time_t time;
        time = randomGaussian(11,3);
        think += time;
        printf("Philopsher %d is thinking for %ld seconds (%d)\n", philo, time, eat);
        sleep(time);

        /*Chopsticks are available for Philosopher to use*/
        if(pthread_mutex_trylock(&chops[philo]) && pthread_mutex_trylock(&chops[RIGHT])){
            printf("Philosopher %d has obtained chopsticks %d and %d\n", philo, philo, RIGHT);
            time = randomGaussian(11,3);
            printf("Philosopher %d is eating for %ld seconds (%d)\n", philo, time, eat);
            fflush(stdout);
            eat += time;
            sleep(time);
            printf("Philosopher %d is laying down chopsticks %d and %d.\n", philo, philo, RIGHT);
            pthread_mutex_unlock(&chops[philo]);
            pthread_mutex_unlock(&chops[RIGHT]);
            cycles++;
        }
    }
    /*Philosopher has finished eating*/
    printf("Philosopher %d ate for %d seconds and thought for %d seconds over %d cycles.\n", philo, eat, think, cycles);
    printf("Thread %d terminated successfully.\n", gettid());
    fflush(stdout);
    return NULL;
}

/*****************************************************************************************/

int main(int argc, char *argv[]){
    int i;
    int eye[N];
    pthread_t philo[N]; /*here are our philosophers*/

    /*Mutex (chopsticks) initialization*/
    for(i = 0; i < N; i++){
        if((pthread_mutex_init (&chops[i], NULL)) != 0){
            fprintf(stderr, "Error(%d) -- %s\n", errno, strerror(errno));
            exit(1);
        }
    }

    /*Philosopher Creation*/
    for(i = 0; i < N; i++){
        eye[i] = i;
        if((pthread_create(&philo[i], NULL, (void*)philosopher, &eye[i])) != 0){
            fprintf(stderr, "Error(%d) -- %s\n", errno, strerror(errno));
            exit(1);
        }
    }

    /*Wait for threads to terminate*/
    for(i = 0; i < N; i++){
        if((pthread_join(philo[i], NULL)) != 0){
            fprintf(stderr, "Error(%d) -- %s\n", errno, strerror(errno));
            exit(1);
        }
    }

    return 0;
}

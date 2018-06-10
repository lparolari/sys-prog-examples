/*!
\mainpage Philosophers Example
\section intro Introduction
  An implementation example for left-handled philosophers protocol.

  Note: some docs are in italian because it is "recyced" code from some 
   execises made at lesson. The other docs are mine.
\date       01/06/2018
\version    0.1.0
\author     Luca Parolari
*/

/*!
  Implements a philosopher protocol and simulates a context.

  \file      philo.c
  \brief     Main file
  \author    L. Parolari
  \date      01/06/2018
*/
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include "sem.h"

static int sem_rods[5] = { 1, 2, 3, 4, 5 }; //!< Rods semaphores array
static int ipcid; //!< The IPC identified
const char MY_CODE = 'a'; //!< Code for generating the IPC key

/*!
    /return An integer representing the i rod
*/
int rod1(int i) { return i; }
/*!
  \/return An integer representing the i+1 rod handled in circular way
*/
int rod2(int i) { return (i+4) % 5; }

/*!
    Simulates eating of the i philosopher printing the start and the end of eating,
     waiting 5 seconds between start and end. 
    The wait is to simulate some real work with a peripheral device for example.
    \brief Simulates eating of the i philosopher
*/
void eat(int i) {
  printf("Philosopher %d is eating\n",i);
  sleep(5);
  printf("Philosopher %d finished eating\n",i);
}

/*!
    Takes the rods from the table implementing the left-handled version
     of philosophers protocol.
    The resources taking has hold-and-wait. 

    \brief Takes the rods
    \param The philosopher
*/
void take(int i) {
  if(i==0) { // left-handed philosopher.
    sem_down(ipcid,sem_rods[rod1(i)]);
    sem_down(ipcid,sem_rods[rod2(i)]);
  }
  else { // philosophers.
    sem_down(ipcid,sem_rods[rod1(i)]);
    sem_down(ipcid,sem_rods[rod2(i)]);
  }
}

/*!
    Places the rods on the table implementing the left-handled version
     of philosophers protocol.

    \brief Places the rods
    \param The philosopher
*/
void place(int i) {
  if(i==0) {
    sem_up(ipcid,sem_rods[rod2(i)]);
    sem_up(ipcid,sem_rods[rod1(i)]);
  }
  else {
    sem_up(ipcid,sem_rods[rod2(i)]);
    sem_up(ipcid,sem_rods[rod1(i)]);
  }
}

/*!
    Simulates the think of a philosopher, and after a while the philosopher
     wakes up and wants to eat. He takes the rod (if he can) then he eat and then he
     places the rods on the table.

    \brief Simulates the behaviour of a philosopher
    \param The philosopher number
*/
void philo(int i) {
  printf("Philosopher %d is thinking\n",i);
  sleep(i*3);

  // wants to eat...
  printf("Philosopher %d is hungry\n",i);

  // rods taking is not atomical, there is hold-and-wait.
  take(i);

  // eating...
  eat(i);

  place(i);
}


/*!
    Creates and initializes the mutex and philos semaphores,
     then starts the philosophers. 

    \brief Start a simulation of left-handled philosopers protocol
*/
int main() {

  key_t key;
  int sid, val, pid;

  // ottiene chiave IPC da pathname (".") e codice (MY_CODE)
  if ((key = ftok(".", MY_CODE)) == -1) { 
    perror("Error ftok");
    exit(1);
  }
  if ((sid = semget(key, 6, 0600 | IPC_CREAT )) == -1) {
    perror("Error sem creation");
    exit(1);
  }

  ipcid = sid;

  // mutex.
  sem_set(ipcid,0,1);
  
  // initializing rods semaphores.
  sem_set(ipcid,sem_rods[0],1);  
  sem_set(ipcid,sem_rods[1],1);  
  sem_set(ipcid,sem_rods[2],1);  
  sem_set(ipcid,sem_rods[3],1);  
  sem_set(ipcid,sem_rods[4],1);  

  // starts the 5 philosophers
  for (int i=0; i<5; ++i) {
    switch (pid = fork()) {
    case -1:
      perror("Error fork");
      exit(2);
    case 0:
      philo(i);
      exit(0);
    default:
      0;
    }
  }

  // waits all the 5 philosophers to end
  wait(&val);
  wait(&val);
  wait(&val);
  wait(&val);
  wait(&val);
  
  if (semctl(sid, 0, IPC_RMID, 0) == -1)
    perror("Error removing sem");
  printf("Father end\n");
}

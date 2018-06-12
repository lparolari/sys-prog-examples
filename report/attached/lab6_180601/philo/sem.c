/*!
  Implements some sintax sugars to easely use semaphores.

  Note: docs and functions were defined by A. Dal Palù.

  \file      sem.c
  \brief     Semaphore sintaxt sugars implementations
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

const int DOWN = -1;
const int UP = 1;

void sem_up(int ipcid, int nsem)
{
    struct sembuf sops[1];
    sops[0].sem_num = nsem;
    sops[0].sem_op = UP;
    sops[0].sem_flg = 0;
    if (semop(ipcid, sops, 1) == -1) {
      perror("Errore in semop");
      exit(3);
    }
}

void sem_down(int ipcid, int nsem)
{
    struct sembuf sops[1];
    sops[0].sem_num = nsem;
    sops[0].sem_op = DOWN;
    sops[0].sem_flg = 0;
    if (semop(ipcid, sops, 1) == -1) {
      perror("Errore in semop");
      exit(3);
    }
}

void sem_set(int ipcid, int nsem, int initial)
{
  union semun arg;
  arg.val = initial;
  if (semctl(ipcid, nsem, SETVAL, arg) == -1) {
    perror("set value sem");
    exit(2);
  }
}

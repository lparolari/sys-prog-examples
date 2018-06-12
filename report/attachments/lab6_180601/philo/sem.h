/*!
  Declare some sintax sugars to easely use semaphores.

  Note: docs and functions were defined by A. Dal Palù.

  \file      sem.h
  \brief     Semaphore sintaxt sugars
  \author    L. Parolari
  \date      01/06/2018
*/

#ifndef SEM_H_INCLUDE_GUARD
#define SEM_H_INCLUDE_GUARD 1

  // Definizione della struttura semun
#ifdef _SEM_SEMUN_UNDEFINED
#define _SEM_SEMUN_UNDEFINED  1
  union semun /* definita in bits/sem.h */
  {
    int val;                              /* value for SETVAL */
    struct semid_ds *buf;                 /* buffer for IPC_STAT & IPC_SET */
    unsigned short int *array;            /* array for GETALL & SETALL */
    struct seminfo *__buf;                /* buffer for IPC_INFO */
  };
#endif



/************************  sem_up() ***********************/
/*!
    \brief  Dello zucchero sintattico per fare la UP
    \param  ipcid Riceve il numero dell`oggetto IPC
    \param  nsem Il semaforo su cui fare UP

    Questa chiamata maschera i dettagli implementativi sul buffer delle operazioni IPC
*/
void sem_up(int ipcid, int nsem);

/************************  sem_up() ***********************/
/*!
     \brief  Dello zucchero sintattico per fare la DOWN
     \param  ipcid Riceve il numero dell`oggetto IPC
     \param  nsem Il semaforo su cui fare DOWN
    
     Questa chiamata maschera i dettagli implementativi sul buffer delle operazioni IPC
*/
void sem_down(int ipcid, int nsem);

/************************  sem_set() ***********************/
/*!
     \brief  Dello zucchero sintattico per impostare il valore di un semaforo
     \param  ipcid Riceve il numero dell`oggetto IPC
     \param  nsem Il semaforo da impostare
     \param  initial Il valore iniziale del semaforo
    
     Questa chiamata maschera i dettagli implementativi sul buffer delle operazioni IPC
*/
void sem_set(int ipcid, int nsem, int initial);

#endif // SEM_H_INCLUDE_GUARD

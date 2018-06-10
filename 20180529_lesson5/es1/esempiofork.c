/*!
\mainpage Esempio Fork
\section intro Introduzione
esempio di creazione processi\n

\date 31/05/2018
\version   0.0.0.1
\author Luca Parolari
*/

/*!
*
* \file      esempiofork.c
* \brief     file principale
* \author    L. Parolari
* \date      31.05.18
*/

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

#define PROVA 5 //!< Questa e' una macro globale

int temp; //!< Questa e' una Variabile globale

/************************  main() ***********************/
/*!
    \brief  Questa e' la funzione principale
    \param  argc Il numero di argomenti
    \param  argv Il vettore degli argomenti
    \return 0 = Esecuzione terminata con successo
    \return -1 = Esecuzione ha generato un errore

    Lo scopo di questa funzione e` quello di lanciare un processo figlio
    e attendere la sua terminazione
*/

int main(int argc, char *argv[])
{  
  int pid;  
  
  int retv; /// Si utilizza retv per ricevere il valore di ritorno del figlio

  switch(pid=fork()) {
  case -1:
    printf("Errore in creazione figlio\n");
    exit(-1);
  case 0 :
    printf("Figlio sospende per 2 secondi...\n"); // figlio
    printf("Pid del figlio: %d, pid di suo padre: %d\n", getpid(), getppid());
    sleep(5); 
    printf("Figlio si risveglia\n");
    exit(3);
  default:
    printf("Padre esegue e attende figlio\n"); // padre
    printf("Pid del padre: %d, pid di suo padre: %d\n", getpid(), getppid());
    wait(&retv); 
    printf("Padre riceve da figlio exit status %d\n",WEXITSTATUS(retv));
  }

 return 0;
}

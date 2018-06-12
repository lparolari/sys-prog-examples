#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/*!
\mainpage Esempio Pipe
\section intro Introduzione

Esercizio pag. 5 slide lezione 6.

Modificare il file:
 - il processo figlio manda alla pipe del testo mediante
cout o printf, il testo viene prelevato da standard input tramite cin o
scanf
 - Il processo padre legge da pipe e scrive a video un carattere alla volta
(usare la system call read() sul file di standard input) finché non appare
il carattere “.”

\date      01/06/2018
\version   0.1.0
\author    Luca Parolari
*/

const int READ_END = 0;
const int WRITE_END = 1;

int main() {
  int pid;
  int fd[2]; // file descriptors.

  pipe(fd); // pipe() could return an error, not checking it.

  if ((pid = fork()) == 0) { // child.

    // no need to read.
    close(fd[READ_END]);
    
    // Note: this comment is not mine, but i finded it very helpful.

    // When we write to stdout for this process, actually write to
		// the write end of the pipe. I.e., make the stdout file
		// descriptor be an "alias" for the write end of the pipe.
		//
		// To do this, dup2() will actually close stdout and then
		// create a new file descriptor with the same number as
		// stdout---and ensure that it behaves exactly the same as the
    // write end of the pipe.

    dup2(fd[WRITE_END], STDOUT_FILENO); // not checking return value for error.

    printf("some text that sould be printed to the standard output. Some text that will not be printed.");
    
    exit(0);
  }
  else if (pid > 0) { // parent.
    // no need to write.
    close(fd[WRITE_END]);

    // instead to read from stdin read from pipe.
    dup2(fd[READ_END],STDIN_FILENO);

    printf("Readed from pipe: ");

    char data[1];
    do {
      if (read(STDIN_FILENO,data,1) != 0) {
        if(data[0]=='.') {
          printf("\n");
          break;
        }
        else printf("%s",data);
      }
      else break;
    } while(1);
    
  }

  // parent.
  close(fd[READ_END]);
  close(fd[WRITE_END]);
}

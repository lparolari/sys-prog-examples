/*!
\mainpage Esempio Leggi-Scrivi
\section intro Introduzione
Esempio system call per scrittura e lettura su file

\date 29/05/2018
\version   0.1.0
\author Luca Parolari

*/

/*!
* \file      leggi.c
* \brief     Esempio lettura da file
* \author    Luca Parolari
* \date      29/05/2018
*/

#define _GNU_SOURCE

#define BUF_SIZE 256

#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main() {
  int fd, count;
  char data[ BUF_SIZE ];

  /* crea un file in sola scrittura */
  fd = open( "data.txt", O_RDONLY);
  if( fd == - 1 ) {
    printf( "%s\n", strerror( errno ) );
    exit( -1 );
  }

  /* memorizza la stringa sul file */
  count = read( fd, data, BUF_SIZE );
  if( count == -1 ) {
    printf( "%s\n", strerror( errno ) );
    exit( -1 );
  }

  printf( "%s", data );

  close( fd );

  exit( 0 );
}

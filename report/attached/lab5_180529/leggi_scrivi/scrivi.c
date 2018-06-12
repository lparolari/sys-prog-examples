/*!
* \file      scrivi.c
* \brief     Esempio scrittura su file
* \author    Luca Parolari
* \date      29/05/2018
*/

#define _GNU_SOURCE

#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

int main() {
  int fd, count;
  char* data = "Questo e' un file di prova.\n";

  /* crea un file in sola scrittura */
  fd = open( "data.txt", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR );
  if( fd == - 1 ) {
    printf( "%s\n", strerror( errno ) );
    exit( -1 );
  }

  /* memorizza la stringa sul file */
  count = write( fd, data, strlen( data ) );
  if( count == -1 ) {
    printf( "%s\n", strerror( errno ) );
    exit( -1 );
  }

  close( fd );

  exit( 0 );
}

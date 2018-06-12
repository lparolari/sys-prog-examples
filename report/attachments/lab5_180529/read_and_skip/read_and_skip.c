/*!
\mainpage Read and Skip
\section intro Introduzione
The goal of this program is to read from a file 2 characters, prints them on screen and skips the next 3 until the file is empty.\n

\date 29/05/2018
\version 0.1.0
\author Luca Parolari

*/

/*!
* \file      read_and_skip.c
* \brief     Main file
* \author    L. Parolari
* \date      31/05/2018
*/

#define _GNU_SOURCE

#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

/************************  main() ***********************/
/*!
    \brief  Main function.
    \param  argc Arguments' number
    \param  argv Arguments' values.
    \return 0  = Success
    \return -1 = Error occurred

    The goal of this program is to read from a file 2 characters, prints them on screen and skips the next 3 until the file is empty.
*/
int main() {
  int file;
  
  // opens data.txt.
  file = open( "data.txt", O_RDONLY);
  if(file == - 1) {
    printf( "%s\n", strerror(errno) );
    exit(-1);
  }

  int nread = 0;  // number of chars readed.
  int nlseek = 0; // number of chars skipped.
  char data[2];

  while(1) {
    nread = read(file, data, 2);
    nlseek = lseek(file,3,SEEK_CUR);
    if (nread <= 0) break;
    printf( "%s", data);
    //printf( ", nread: %d", nread);
    //printf( ", nlseek: %d\n", nlseek);
  }
  if(nread == -1 || nlseek == -1) {
    printf( "Error(s) occurred: %s\n", strerror(errno));
    exit(-1);
  }
  
  printf("\n");

  close(file);

  // Input:  abcdefghijk   (from file data.txt)
  // Output: abfgjk

  exit(0);
}

/*!
\mainpage   Reader-Writers Example
\section intro Introduction
            An implementation example for reader-writers protocol, giving priority to readers.
            
            The goal of this example is to
             - create two or more readers,
             - create a writer
             - simlutate some reads and some writes on shared data
            following the reader-writers protol.

            See \link main main \endlink function to run the code.

\date       06/05/2018
\version    0.1.0
\author     Luca Parolari
*/

/*!
* \file      rws.c
* \brief     Main file
* \author    L. Parolari
* \date      06/05/2018
*/
#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static sem_t mutex; //!< Mutex semaphore, used to syncronize readers while the writer is writing.
static sem_t write_sem; //!< Writer semaphore, used to syncronize writer: waits until there aren't any reader.

int readers_no = 0; //!< Counts the readers number, in order to lock or unlock the writer mutex.
int shared[100]; //!< Shared array on which readers read and writer write.
int writed_no = 0; //!< Counts writed cells number.

/*!
Simulates a read procedure reading things from the shared data,
and waits for some seconds simulating reader pause.

\brief Simulates a read procedure
\param The reader number
*/
void* reader(void* arg) {
    while(1) {
        reader_internal((int)arg);

        // simulating a delay between reads (different for every thread) in order to allo
        //  the writer to write again.
        sleep(((int)arg)+2);
    }
 }

/*!
Execute a read following reader-writers protocol.

\brief Executes a read
\param The reader thread number
*/
void reader_internal(int r) {
    int r_id = r;

    sem_wait(&mutex); // mutex down
    ++readers_no;
    if (readers_no == 1) 
        sem_wait(&write_sem); // write down if the first
    sem_post(&mutex); // mutex up

    printf("Thread %d start reading\n",r_id);
    for(int i = 0; i < writed_no; i += r_id+1) printf("%d, ",shared[i]);
    printf("\n");
    sleep(2);
    printf("Thread %d end reading\n\n",r_id);

    sem_wait(&mutex); // mutex down
    --readers_no;
    if (readers_no == 0)
        sem_post(&write_sem);
    sem_post(&mutex); // mutex up
}

/*!
Simulates a write procedure writing a shared data cell per time,
and waits for some seconds simulating writer pause.

\brief Simulates a write procedure
\param The writer name
*/
void* writer(void* arg) {
    while(1) {
        writer_internal((char*)arg);
        // waits at least 2 seconds between two writes, in order to allow
        //  readers to read something.
        sleep(2);
    }
}

/*!
Execute a write following reader-writers protocol.

\brief Executes a write
\param The writer thread name
*/
void writer_internal(char* w) {
    sem_wait(&write_sem); // write down

    printf("Thread %s start writing\n",w);
    shared[writed_no] = writed_no*10;
    ++writed_no;
    sleep(2);
    printf("Thread %s end writing\n\n",w);

    sem_post(&write_sem); // write up
}

/*!
Initializes semaphores and creates thread, making them starting writing or reading.

\brief Entry point function
\param The arguments number
\param The arguments data
\ref main
*/
int main(int argc, char const *argv[])
{
    const int r_no = 5;
    // threads
    pthread_t readers[r_no];
    pthread_t wrt;

    void * ret; // threads return value

    // semaphore inits.
    sem_init(&mutex,0,1);       // mutex(1) 
    sem_init(&write_sem,0,1);   // write_sem(1)

    // creating a writer.
    if (pthread_create(&wrt, NULL, writer, "writer") < 0) { 
        printf("pthread_create error for thread writer\n");
        exit (1);
    }

    // creating r_no readers.
    for(int i=0; i<r_no; ++i) {
        if (pthread_create(&readers[i], NULL, reader, i) < 0){ 
            printf("pthread_create error for thread\n");
            exit (1);
        }
    }

    // main waits each thread before exiting.
    for(int i=0; i<r_no; ++i) pthread_join (readers[i], &ret);
    pthread_join (wrt, &ret);

    printf("Exit\n");

    return 0;
}

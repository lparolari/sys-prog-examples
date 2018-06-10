/*!
\mainpage MYSH
\section intro Introduzione
Shell minimale a scopo didattico.\n
Thanks to Roberto Alfieri for the version 0.1.0

\date 29/02/2018
\version   0.2.0
\author Luca Parolari
\author Roberto Alfieri
 */

/*!
*
* \file      mysh.cpp
* \brief     file principale
* \author    L. Parolari
* \date      31.05.18
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <sys/wait.h>

#define MAXPARAMS 6 //!< Numero elementi del vettore comando
#define MAXPATH 60  //!< Numero elementi del vettore PATH

int string2vpunt(char *stringa, int maxchar, char *vpunt[], int maxpunt, char *sep);
int vpunt_print(char *vpunt[]);
int get_command(char *comando[]);
int esegui(char *cmd[], char *argv[], char *envp[]);
int exec_down(char *vpunt[]);
int command(char* cmd, char* argv[]);
int which(char* cmd, char* cmdfq);

char *path[MAXPATH];      //!< path Vettore di puntatori che verra' riempito con i PATH
char *comando[MAXPARAMS]; //!< comando Vettore comando: comando e opzioni

/************************  main() ***********************/
/*!
    \brief  Funzione principale
    \param  argc Numero di elementi in argv
    \param  argv
    \param  envp
    \return 0=ok
*/
int main(int argc, char *argv[], char *envp[])
{
    string2vpunt((char *)getenv("PATH"), strlen(getenv("PATH")), path, MAXPATH, ":\n");

    while (!get_command(comando))
    {
        esegui(comando, argv, envp);
    }

    return 0;
}

/************************  esegui() ***********************/
/*!
    \brief  Esegue il comando
    \param  cmd vettore comando (VP)
    \param  argv vettore argv (VP)
    \param  envp vettore delle variabili d'ambiente (VP)
    \return 0=ok 1=cmd_not_found
*/
int esegui(char *cmd[], char *argv[], char *envp[])
{
    if (!strcmp(cmd[0], "printenv"))
    {
        vpunt_print(envp);
        return 0;
    }
    else if (!strcmp(cmd[0], "printargv"))
    {
        vpunt_print(argv);
        return 0;
    }
    else if (!strcmp(cmd[0], "printpath"))
    {
        vpunt_print(path);
        return 0;
    }
    else if (!strcmp(cmd[0], "printcmd"))
    {
        vpunt_print(cmd);
        return 0;
    }
    else
    {
        if (exec_down(cmd) == 0) return 0; 
        else{
            printf("Command '%s' not found\n", cmd[0]);
            return 1;
        }
    }
}

/********************** string2vpunt() ******************/
/*!
    \brief  Separa i  tokens di una stringa in un vettore di puntatori
    \param  stringa stringa da suddividere
    \param  maxchar massima lunghezza dele a stringa
    \param  vpunt vettore dei  tokens (VP)
    \param  maxpunt  massima lunghezza di vpunt
    \param  sep    stringa dei catarreri separatori
    \return 0=ok
*/
int string2vpunt(char *stringa, int maxchar, char *vpunt[], int maxpunt, char *sep)
{
    char temp[maxchar];
    int i;
    char *p;

    //   for(i=0;i<maxpunt;i++) {free(vpunt[i]); vpunt[i]=NULL;}
    strcpy(temp, stringa);
    p = strtok(temp, sep);
    for (i = 0; p && i < maxpunt; i++)
    {
        vpunt[i] = (char *)malloc(strlen(p) + 1);
        strcpy(vpunt[i], p);
        p = strtok(NULL, sep);
    }
    vpunt[i] = NULL;
    return 0;
}

/************************  get_command() ****************/
/*!
    \brief  Funzione per l'input e la gestione del comando
    \param  cmd  vettore comando (VP)
    \return 0=ok  1=exit
*/
int get_command(char *cmd[])
{
    char string_command[100];

    do
    {
        printf("mysh> ");
        fgets(string_command, sizeof(string_command), stdin);
        string2vpunt(string_command, 100, cmd, MAXPARAMS, " \n");
    } while (!cmd[0]);

    if (!strcmp(cmd[0], "exit"))
        return 1;
    else
        return 0;
}

/************************* vpunt_print() ******************/
/*!
    \brief  Stampa le stringhe da un vettore di puntatori
    \param  vpunt  vettore di puntatori
    \return 0=OK
*/
int vpunt_print(char *vpunt[])
{
    int i;

    for (i = 0; vpunt[i]; i++)
        printf(" %s \n", vpunt[i]);
    return 0;
}

/* ******************** which() ******************* */
/*!
    \brief  Search in paths the first occurence of target command, and returns the fully
             qualified name in cmdfq.
    \param  cmd The command to search
    \param  cmdfq The fully qualified command path as output if exists
    \return 0 = Command found
    \return 1 = Command not found
*/
int which(char* cmd, char* cmdfq) {
    int i;

    for (i = 0; path[i]; ++i)
    {
        // assemblig searching path for command.
        std::string cmd_path = std::string(path[i]) 
            + std::string("/") 
            + std::string(cmd);
        
        // testing if command exist.
        if (access(cmd_path.c_str(),F_OK) == 0) {
            cmdfq = strcpy(cmdfq,cmd_path.c_str());
            return 0;
        }
    }
    
    return 1;
}

/* ******************** command() ******************* */
/*!
    \brief  Execute a command using down machine.
    \param  cmd The command to execute
    \return 0 = Command executed
    \return 1 = Something went wrong
*/
int command(char* cmd, char* argv[]) {
    char cmdfq[128];

    // checking cmd is a valid command.
    if (which(cmd,cmdfq)==0) {
        
        // forking the process.
        int pid = fork(); 

        // son will execute the command to the down machine,
        //  the father will wait for the son.

        // return value of son, readed by father.
        int ret_value;

        // error.
        if (pid == -1) return 1;
        // son.
        else if (pid == 0) {
            int x = 0;
            x = execv(cmdfq,argv); // executing.
            if (x == -1) exit(1);
            else exit(0);
        }
        // father.
        else { 
            wait(&ret_value);
            return WEXITSTATUS(ret_value);
        }
    }
    else return 1;
}

/* ******************** exec_down() ******************* */
/*!
    \brief  Execute a command making a call to the down machine.
    \param  vpunt Vector of pointers
    \return 0 = Command executed
    \return 1 = Command not found
*/
int exec_down(char *vpunt[]) {
    
    char* cmd = vpunt[0];
    
    // which.
    if (strcmp(cmd,"which") == 0) {
        char cmdfq[100];
        if (vpunt[1]) {
            if (which(vpunt[1],cmdfq) == 0) 
                printf("Command found, fully qualified name is %s\n",cmdfq);
            else
                printf("Command %s is not installed\n",vpunt[1]); 
        }
        else 
            printf("%s\n","Usage: which command");

        return 0;
    }

    // exec.
    else {
        if (command(cmd,vpunt) == 0) {
            printf("Executed %s\n",cmd);
            return 0;
        }
        else return 1;

        //char cmdfq[100];
        //if (which(cmd,cmdfq) != 0) 
        //    return 1; // command not found.
        //else {
            //if (vpunt[1]) {
            // making argv for down command.
            //char* argv_tmp[] = {0,0,0,0,0}; // exec + 5 params (max).
            // filling argv from vpunt, excluding exec.
            //for(int i=1; vpunt[i]; ++i)
            //    argv_tmp[i-1] = vpunt[i];

            // calling procedure to execute commands.
            
        //} 
    }

    // exec.
    /*else if (strcmp(cmd,"exec") == 0) {
        
        }
        else 
            printf("%s\n","Usage: exec command");

        return 0;
    }

    // command not found.
    else return 1;*/
}

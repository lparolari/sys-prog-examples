#!/bin/bash

BLUE='\033[0;34m'
NC='\033[0m' # no color

usage() {
    echo ""
    echo "HELP"
    echo ""
    echo " USAGE: processutils.sh"
    echo ""
    echo " ACTIONS:"
    echo "   <h|help>: show this guide"
    echo "   <1|p|pid>: pid and command line giving user"
    echo "   <2|a|all>: show system processes ordered by pid"
    echo "   <3|k|kill>: kill -9 on pid"
    echo "   <4|e|exit>: exit from this tool"
    echo "  where | is OR."
    echo ""
    echo " EXAMPLES:"
    echo "   1) this can be a possible sequence of operations: "
    echo "        foo@foo:~$ processutils.sh"
    echo "        Chose an action [p,a,k,e] or h for help: p"
    echo "        Enter the user: user"
    echo "        UID        TTY"
    echo "        lparola+   pts/0"
    echo "      p is the action selected, and than user is the user searched in system"
    echo "   2) or this: "
    echo "        foo@foo:~$ processutils.sh"
    echo "        Chose an action [p,a,k,e] or h for help: e"
    echo "        Exiting..."
    echo "        foo@foo:~$"
    echo "   3) even this: "
    echo "        foo@foo:~$ processutils.sh"
    echo "        Chose an action [p,a,k,e] or h for help: hello"
    echo "        Unknown action 'hello'"       
    echo ""
}

pid() {
    echo ""
    echo "ACTION: PID"
    echo -n "Enter the user: "
    read user
    echo ""
    ps -f | awk ' { printf("%-10s %s\n", $1, $6) } ' #' { if ($1!="UID") { print $1 " " $2 } } ' | sort
}

all() {
    echo ""
    echo "ACTION: ALL"
    ps -fe --sort=pid
}

kill_pid() {
    echo ""
    echo "ACTION: KILL"
    echo -n "Enter pid to kill: "
    read pid
    kill -9 $pid
}


echo -e $BLUE"Welcome to Process Utils CLI"
echo "Made by lparolari <luca.parolari23@gmail.com>"
echo -e $NC""

usage

while true
do
    echo "******************"
    echo "Chose an action [p,a,k,e] or h for help:"
    echo -n "#? "
    

    read action
    
    case $action in
	"h"|"help")
	    usage
	    ;;
	1|"p"|"pid")
	    pid
	    ;;
	2|"a"|"all")
	    all
	    ;;
	3|"k"|"kill")
	    kill_pid
	    ;;
	4|"e"|"exit")
	    echo "Exiting..."
	    exit 0;;
	*)
	    echo "Unknown action '$action'"
    esac

    echo ""
    echo ""
done

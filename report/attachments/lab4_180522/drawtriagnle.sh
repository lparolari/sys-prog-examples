#!/bin/bash

# display the usage of drawitriangle and exit with code 1
usage() {
    echo "usage: drawtriangle <height>"
    echo ""
    echo " <height>: the height of the triangle."
    echo "   must be a number"
    echo "   must be between 3 and 15"
	exit 1
}



height=$1


# test if height is given
if [ $# -ne 1 ]
then usage; fi;

# test if height is a number
re='^[0-9]+$'
if ! [[ $height =~ $re ]] ; then
   usage
fi

# test if 3 < height < 15
if test $height -lt 3 -o $height -gt 15
then usage; fi;


# drawing triangle
for i in `seq 1 $[$height-1]` # iterate on height
do
    echo -n "|"
    for j in `seq 1 $[$i-1]`  # iterate on spaces between left and right
    do
	 echo -n " "
    done
    echo "\\"                 # draw right side
done
for i in `seq 1 $[$height+1]` # draw the base
do
    echo -n "-"
done
echo ""

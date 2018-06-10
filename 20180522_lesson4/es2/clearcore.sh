#!/bin/bash

# display the usage of drawitriangle and exit with code 1
usage() {
    echo "usage: clearcore <dirpath>"
    echo ""
    echo "Deletes all file named 'core' recursively from dirpath"
    echo ""
    echo "ARGS:"
    echo " <dirpath>: directory from which deleting core files."
    exit 1
}



dirpath=$1


# test if dirpath is given
if [ $# -ne 1 ]
then usage; fi;

# test if dirpath exist and if dirpath is a directory
if test ! -e $dirpath -o ! -d $dirpath
then usage; fi;


echo "Following file will be deleted:"
echo ""
for i in `find $dirpath -name core -type f`
do
    echo $i
done
echo ""
echo "are you sure?"
select continue in "yes" "no"
do
    for i in `find $dirpath -name core -type f`
    do
	rm $i
    done
    echo ""
    echo "Deleted"
    break
done

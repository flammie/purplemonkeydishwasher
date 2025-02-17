#!/bin/bash
# generate homogenouse edit distance with weight of 1 for each edit
if test $# -lt 4 ; then
    echo "Usage: $0 NUMBER WEIGHT A L [P H A B E T]"
    echo "Generate text representation of homogenouse edit distance NUMBER WFST"
    echo "The weight of each edit will be WEIGHT"
    echo
    echo "Argument list must contain at least 2 alphabets"
    echo
    echo "Examples:"
    echo "  $0 2 3.141 a b c d e f g h i j k l m n o p q | hfst-txt2fst -v -o errmodel.edit-distance-2.hfst"
    exit 1
fi
echo 0
n=$1
shift
w=$1
shift
j=$n
for i in $(seq 0 $((n-1))) ; do
	for c in $@ ; do
		echo "$i	$i	$c	$c	0"
		echo "$i	$((i+1))	$c	@0@	$w"
		echo "$i	$((i+1))	@0@	$c	$w"
		for d in $@ ; do
			if [[ $c != $d ]] ; then
				j=$(($j+1))
				echo "$i	$j	$c	$d	$w"
				echo "$j"
				echo "$j	$((i+1))	$d	$c	0"
                echo "$j	$((i+1))	@0@	@0@	0"
			fi
		done
	done
	echo $((i+1))
	for c in $@ ; do
		echo "$((i+1))	$((i+1))	$c	$c	0"
	done
done

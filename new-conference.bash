#!/bin/bash

#set -x

if test $# -lt 4 ; then
    echo Usage: $0 AUTHOR YEAR CONFERENCE TITLE
    exit 1
fi
AUTHOR=$1
YEAR=$2
CONFERENCE=$3
TITLE=$4

mkdir -v $YEAR-$CONFERENCE
sed -e "s/@AUTHOR@/$AUTHOR/g" \
    -e "s/@YEAR@/$YEAR/g" \
    -e "s/@CONFERENCE@/$CONFERENCE/g" \
    -e "s/@TITLE@/$TITLE/g" template/Makefile.in > $YEAR-$CONFERENCE/Makefile
for f in template/*.tex ; do
    newf=$(echo $f | sed -e "s:template/:$YEAR-$CONFERENCE/:" \
        -e "s/AUTHOR/$AUTHOR/" -e "s/YEAR/$YEAR/" -e "s/CONFERENCE/$CONFERENCE/" \
        -e "s/TITLE/$TITLE/")
    sed -e "s/AUTHOR/$AUTHOR/g" \
        -e "s/YEAR/$YEAR/g" \
        -e "s/CONFERENCE/$CONFERENCE/g" \
        -e "s/TITLE/$TITLE/g" $f > $newf
    echo "$f --sed-> $newf"
done
cp -v bibs/master.bib $YEAR-$CONFERENCE/$CONFERENCE$YEAR.bib

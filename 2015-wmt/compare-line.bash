#!/bin/bash

if test $# -lt 3 ; then
    echo Usage: $0 LINEN FILEs...
    exit 1
fi

linen=$1
shift
mytmp=$(mktemp -dt comparelines.XXXXXXXXXX)
for f in $@ ; do
    head -n ${linen} < $f | tail -n 1 > $mytmp/$(basename ${f})
done
ls ${mytmp}/*
paste ${mytmp}/*


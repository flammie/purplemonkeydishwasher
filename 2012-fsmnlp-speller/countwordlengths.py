#!/usr/bin/env -O python3

from sys import argv, exit

if len(argv) != 3:
    print("Usage:", argv[0], "INFILE OUTFILE")
    exit(1)

inp = open(argv[1], "r")
outp = open(argv[2], "w")

wordlengths = dict()
length = 0
words = 0
for line in inp:
    line = line.strip()
    if not line:
        continue
    if not len(line) in wordlengths.keys():
        wordlengths[len(line)] = 1
    else:
        wordlengths[len(line)] += 1
    words += 1
    length += len(line)

print("Average word length:", length/words)

for wlen, count in wordlengths.items():
    print(wlen, count, sep="\t", file=outp)


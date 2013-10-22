#!/bin/env -O python3
# script to evaluate result sets in two apertium stream format files.

from sys import stdin, stdout, stderr, exit, argv
from os.path import basename
from getopt import getopt, GetoptError
import re

def usage():
    """
    print std. usage info
    """
    print(basename("Usage:", argv[0]), "[SETTINGS]")
    print("Evaluate apertiums and stuff")
    print()
    print("  -1, --input1   the apertium data")
    print("  -2, --input2   the hfst data")
    print("  -o, --output   save log in O")
    print()

def main():
    input1file = stdin
    input1filename = False
    input2file = stdin
    input2filename = False
    outputfile = stdout
    outputfilename = False

    try:
        opts, args = getopt(argv[1:], "h1:o:2:", ["help", "input1=", "output=", "input2="])
    except GetoptError:
        usage()
        exit(2)
    for opt, arg in opts:
        if opt in ("-h", "--help"):
            usage()
            exit(0)
        elif opt in ("-1", "--input1"):
            input1filename = arg
        elif opt in ("-o", "--output"):
            outputfilename = arg
        elif opt in ("-2", "--input2"):
            input2filename = arg
        else:
            usage()
            exit(1)
    if not input1filename or not input2filename:
        print("need -1 and -2")
        usage()
        exit(1)
    if input1filename:
        input1file = open(input1filename, "r")
    if input2filename:
        input2file = open(input2filename, "r")
    if outputfilename:
        outputfile = open(outputfilename, "w")

    print("Reading from", input1filename, "and", input2filename, "writing to", outputfilename)
    input1line = input1file.readline()
    input2line = input2file.readline()
    rights = 0
    wrongs = 0
    sets = 0
    lines = 0
    while input1line and input2line:
        lines += 1
        input1sets = re.findall(r'\^[^$]*\$', input1line)
        input2sets = re.findall(r'\^[^$]*\$', input2line)
        j = 0
        for i in range(len(input1sets)):
            sets += 1
            input1slash = input1sets[i].find('/')
            if len(input2sets) == 0:
                print(lines, ":", i, ": no results")
                break
            elif j >= len(input2sets):
                print(lines, ":", i, ": not enough results")
                j = len(input2sets) -1
            if not input1slash:
                input1lemma = input1sets[i][1:-1]
                input1results = set(input1sets[i][1:-1])
            else:
                input1lemma = input1sets[i][1:input1slash]
                input1results = set(input1sets[i][input1slash:-1].split('/'))
            input2slash = input2sets[j].find('/')
            if not input2slash:
                input2lemma = input2sets[j][1:-1]
                input2results = set(input2sets[j][1:-1])
            else:
                input2lemma = input2sets[j][1:input2slash]
                input2results = set(input2sets[j][input2slash:-1].split('/'))
            if input1lemma != input2lemma:
                print(lines, ":", i, ": lemma mismatch ", input1lemma, " != ", input2lemma)
                wrongs += 1
                j += 1
                continue
            if input2results != input1results:
                input2minus1 = input2results - input1results
                input1minus2 = input1results - input2results
                if len(input2minus1) > 0:
                    print(lines, ":", i, ": extra results ", input2minus1)
                if len(input1minus2) > 0:
                    print(lines, ":", i, ": missing results ", input1minus2)
                wrongs += 1
                j += 1
                continue
            rights += 1
            j += 1
        input1line = input1file.readline()
        input2line = input2file.readline()
        lines += 1
    print("right & wrong & total \\\\", file=outputfile)
    print(rights, "&", wrongs, "&", sets, "\\\\", file=outputfile)


main()

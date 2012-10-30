#!/bin/env -O python3
# script to dump TSV histogram of word-forms per tokens for R

from sys import stdin, stdout, stderr, exit, argv
from os.path import basename
from getopt import getopt, GetoptError

def usage():
    """
    print std. usage info
    """
    print(basename("Usage:", argv[0]), "[SETTINGS]")
    print("Create forms per tokens statistics")
    print()
    print("  -i, --input   the token list")
    print("  -o, --output  save log in O")
    print()

def main():
    inputfile = stdin
    inputfilename = False
    outputfile = stdout
    outputfilename = False
    seenwords = set()
    tokens = 0
    uniqs = 0
    sparsity = 10

    try:
        opts, args = getopt(argv[1:], "hi:o:c:", ["help", "input=", "output=", "csv="])
    except GetoptError:
        usage()
        exit(2)
    for opt, arg in opts:
        if opt in ("-h", "--help"):
            usage()
            exit(0)
        elif opt in ("-i", "--input"):
            inputfilename = arg
        elif opt in ("-o", "--output"):
            outputfilename = arg
        else:
            usage()
            exit(1)
    if not inputfilename:
        print("need -i")
        usage()
        exit(1)
    if inputfilename:
        inputfile = open(inputfilename, "r")
    if outputfilename:
        outputfile = open(outputfilename, "w")

    print("Reading from", inputfilename, "writing to", outputfilename)
    for inputline in inputfile:
        tokens += 1
        if not inputline.strip() in seenwords:
            uniqs += 1
            seenwords.add(inputline.strip())
        if tokens % sparsity == 0:
            print(tokens, uniqs, sep="\t", file=outputfile)
            print(tokens, "... ")
        input


main()

#!/bin/env -O python3
# script to evaluate pr on hunspell like output and
# tsv of mispelt tab correct

from sys import stdin, stdout, stderr, exit, argv
from os.path import basename
from getopt import getopt, GetoptError

def usage():
    """
    print std. usage info
    """
    print(basename("Usage:", argv[0]), "[SETTINGS]")
    print("Evaluate hunspells and stuff")
    print()
    print("  -i, --input   the hunspell data")
    print("  -c, --csv     the correct data")
    print("  -o, --output  save log in O")
    print()

def main():
    inputfile = stdin
    inputfilename = False
    csvfile = stdin
    csvfilename = False
    outputfile = stdout
    outputfilename = False
    statsfile = stdout
    statsfilename = False

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
        elif opt in ("-c", "--csv"):
            csvfilename = arg
        else:
            usage()
            exit(1)
    if not inputfilename and not csvfilename:
        print("need -i or -c")
        usage()
        exit(1)
    if inputfilename:
        inputfile = open(inputfilename, "r")
    if csvfilename:
        csvfile = open(csvfilename, "r")
    if outputfilename:
        statsfilename = outputfilename.replace("spells", "stats", 1)
        outputfile = open(outputfilename, "w")
        statsfile = open(statsfilename, "w")

    print("Reading from", inputfilename, "and", csvfilename, "writing to", outputfilename, "and", statsfilename)
    csvline = csvfile.readline()
    inputline = inputfile.readline()
    in_lm = 0
    missing = 0
    firsts = 0
    seconds = 0
    thirds = 0
    fourths = 0
    fifths = 0
    lower = 0
    no_tries = 0
    roots = 0
    no_corrects = 0
    lines = 0
    split = 0
    guesses = 0
    compounds = 0
    while inputline and csvline:
        if not inputline:
            print("input ended before csv", file=stderr)
            break
        if not csvline:
            print("csv ended before input", file=stderr)
            break
        if inputline.startswith("Hunspell"):
            inputline = inputfile.readline()
            continue
        if not inputline.strip():
            inputline = inputfile.readline()
            continue
        csvparts = csvline.strip().split()
        if inputline[0] == "#":
            missing += 1
            no_tries += 1
        elif inputline[0] == "*":
            in_lm += 1
        elif inputline[0] == "+":
            in_lm += 1
            roots += 1
        elif inputline[0] == "-":
            in_lm += 1
            compounds += 1
        elif inputline[0] == "?":
            in_lm += 1
            guesses += 1
        elif inputline[0] == "&":
            parts = inputline[2:].strip().split(",")
            mispelt = parts[0][:parts[0].find(" ", 3)]
            first = parts[0][parts[0].find(":")+2:]
            if first == csvparts[1]:
                firsts += 1
            else:
                position = 2
                found = False
                for sug in parts[1:]:
                    if sug.strip() == csvparts[1]:
                        if position == 2:
                            seconds += 1
                            found = True
                        elif position == 3:
                            thirds += 1
                            found = True
                        elif position == 4:
                            fourths += 1
                            found = True
                        elif position == 5:
                            fifths += 1
                            found = True
                        else:
                            lower += 1
                            found = True
                        break
                    position += 1
                if not found:
                    missing += 1
                    no_corrects +=1
        else:
            print("unrecognised analysis", inputline[0], file=stderr)
        inputline = inputfile.readline()
        csvline = csvfile.readline()
        lines += 1
    if lines < 1:
        print("DATOISSA VIRHE. END.")
        exit(1)
    print("All\t1st\t2nd\t3rd\t4th\t5th\tWorse\tnone\tin LM", file=statsfile)
    print(lines,  firsts,  seconds,  thirds,  fourths,  fifths,  lower,  no_corrects,  in_lm, sep="\t", file=statsfile)
    print(lines/lines*100,  firsts/lines*100,  seconds/lines*100,  thirds/lines*100,  fourths/lines*100,  fifths/lines*100,  lower/lines*100,  no_corrects/lines*100,  in_lm/lines*100, sep="% \t", file=statsfile)


main()

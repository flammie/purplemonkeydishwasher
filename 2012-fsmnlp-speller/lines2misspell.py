#!/usr/bin/env python
# -*- coding: utf8 -*-
# script to misspell strings for omor-eval

from sys import stdin, stdout, argv, exit
from os.path import basename
from getopt import getopt, GetoptError
from codecs import open, getreader, getwriter
from math import log
from random import Random

def usage():
    """
    Standard usage message.
    """
    print "Usage: %s [settings]" %(basename(argv[0]))
    print "Convert blah"
    print
    print "  -h, --help            print this help"
    print "  -i, --input=I         read input from I"
    print "  -o, --output=O        write output to O"
    print "  -s, --seed=N          seed random number generator with N"
    print "  -p, --probability=P   likelihood of spelling error P"
    print "  -n, --limit=X         limit to X blah"
    print



def main():
    input_file = stdin
    input_file_name = False
    output_file = stdout
    output_file_name = False
    probability = False
    seednumber = False
    random = Random()
    max_lines = 100000000000000
    try:
        opts, args = getopt(argv[1:], "hi:o:s:p:n:", 
                    ["help", "input=", "output=", "seed=", "probability=", "limit="])
    except GetoptError:
            usage()
            exit(2)
    for opt, arg in opts:
        if opt in ("-h", "--help"):
            usage()
            exit()
        elif opt in ("-i", "--input"):
            input_file_name = arg
        elif opt in ("-o", "--output"):
            output_file_name = arg
        elif opt in ("-s", "--seed"):
            seednumber = int(arg)
        elif opt in ("-p", "--probability"):
            probability = float(arg)
        elif opt in ("-n", "--limit"):
            max_lines = int(arg)
        else:
            usage()
    if output_file_name:
        output_file = open(output_file_name, 'w', 'UTF-8')
    else:
        print "no --output spec, using stdout"
        output_file = getwriter('utf-8')(stdout)
    if input_file_name:
        input_file = open(input_file_name, 'r', 'UTF-8')
    else:
        print "no --input= specified, using stdin"
        input_file = getreader('utf-8')(stdin)
    if seednumber:
        random.seed(seednumber)
    else:
        random.seed()
    if not probability:
        probability = 0.033
    line = input_file.readline()
    lines = 0
    print "Misspelling"
    while line:
        line = line.strip()
        if lines > max_lines:
            break
        lines += 1
        if not line:
            line = input_file.readline()
            continue
        words = line.split()
        for i in range(0, len(words)):
            word = words[i]
            misspelt = u""
            for character in word:
                x = random.random()
                if x < probability*1/4 and len(misspelt) > 0:
                    # swap
                    misspelt = misspelt[:-1] + character + misspelt[-1]
                    print "^",
                elif x < probability*1/2:
                    # replace
                    misspelt += random.choice(u"abcdefghijklmnopqrstuvwxyz")
                    print "X",
                elif x < probability*3/4:
                    # insert
                    misspelt += character
                    misspelt += random.choice(u"abcdefghijklmnopqrstuvwxyz")
                    print "+",
                elif x < probability:
                    # delete
                    misspelt = misspelt
                    print "-",
                else:
                    misspelt += character
            if misspelt != word:
                print >> output_file, "%s\t%s" %(misspelt, word)
                print "|",
            else:
                print >> output_file, "%s\t%s" %(misspelt, word)
                print ".",
        line = input_file.readline()
    exit()


if __name__ == "__main__":
    main()


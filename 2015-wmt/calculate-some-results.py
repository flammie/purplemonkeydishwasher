#!/usr/bin/env -O python3

from sys import argv
import csv

if len(argv) < 2:
    print("Usage", argv[0], "CSVFILE")
    print()
    print("Parses WMT results in abumatran compare two results format and prints stuff")
    exit(1)

judges = dict()
rankcounts = {"-4": {}, "-3": {}, "-2": {}, "-1": {}, "0": {}, "1": {}, "2": {}, "3": {}, "4": {}}
ranksbyseg = dict()
with open(argv[1]) as csvfile:
    csvreader = csv.DictReader(csvfile)
    for csvrow in csvreader:
        judge = csvrow['judgeID']
        if not judge in judges:
            judges[judge] = list()
        rank = csvrow['diffranks']
        seg = csvrow['segmentId']
        if not seg in rankcounts[rank]:
            rankcounts[rank][seg] = 0
        rankcounts[rank][seg] += 1
##        if rank == 4:
##            if not csvrow['segmentId'] in oursworst:
##                oursworst[csvrow['segmentId']] = 0
##            oursworst[csvrow['segmentId']] += 1
##        if rank == -4:
##            if not csvrow['segmentId'] in theirsworst:
##                theirsworst[csvrow['segmentId']] = 0
##            theirsworst[csvrow['segmentId']] += 1
        judges[judge].append(int(rank))
        if not seg in ranksbyseg:
            ranksbyseg[seg] = {"-4": 0, "-3": 0, "-2": 0, "-1": 0, "0": 0, "1": 0, "2": 0, "3": 0, "4": 0}
        ranksbyseg[seg][rank] +=1

for judge,ranks in judges.items():
    ranktotal = 0
    rankcount = 0
    print(judge, ranks)
    for rank in ranks:
        ranktotal = rank
        rankcount += 1
    print("avg", ranktotal / rankcount)

for rd in ['4', '3', '2', '1', '0', '-1', '-2', '-3', '-4']:
    print("Rankdiffs", rd)
    for segment, times in rankcounts[rd].items():
        print(segment, times)

for seg, ranks in ranksbyseg.items():
    print(seg, ranks['4'], ranks['3'], ranks['2'], ranks['1'], ranks['0'], ranks['-1'], ranks['-2'], ranks['-3'], ranks['-4'])
    if ((ranks['4'] > 0) or (ranks['3'] > 0)) and ((ranks['-4'] > 0) or (ranks['-3'] > 0)):
        print(seg, "4 ×", ranks['4'], "3 ×", ranks['3'],
                "-3 ×", ranks['-3'], "-4 ×", ranks['-4'])


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

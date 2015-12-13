#!/usr/bin/env -O python3

from sys import argv
import csv

if len(argv) < 2:
    print("Usage", argv[0], "CSVFILE")
    print()
    print("Parses WMT results in abumatran compare two results format and prints stuff")
    exit(1)

judges = dict()
oursworst = dict()
theirsworst = dict()
with open(argv[1]) as csvfile:
    csvreader = csv.DictReader(csvfile)
    for csvrow in csvreader:
        judge = csvrow['judgeID']
        if not judge in judges:
            judges[judge] = list()
        rank = int(csvrow['diffranks'])
        if rank == 4:
            if not csvrow['segmentId'] in oursworst:
                oursworst[csvrow['segmentId']] = 0
            oursworst[csvrow['segmentId']] += 1
        if rank == -4:
            if not csvrow['segmentId'] in theirsworst:
                theirsworst[csvrow['segmentId']] = 0
            theirsworst[csvrow['segmentId']] += 1
        judges[judge].append(rank)

for judge,ranks in judges.items():
    ranktotal = 0
    rankcount = 0
    print(judge, ranks)
    for rank in ranks:
        ranktotal = rank
        rankcount += 1
    print("avg", ranktotal / rankcount)

print("Rankdiff 4")
for segment, times in oursworst.items():
    print(segment, times)
print("Rankdiff -4")
for segment, times in theirsworst.items():
    print(segment, times)


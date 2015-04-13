#!/usr/bin/env python

import sys

def main():
    if (len(sys.argv) != 2):
        print "Usage: python csv_list_output.py CSV"
        sys.exit(1)

    filename = sys.argv[1]
    data = []

    with open(filename) as csv:
        data = [line.split(",") for line in csv.readlines()[1:]]

    index = input("Please enter an index from 0 to " + str(len(data[0]) - 1) + ": ")

    for i in range(index + 1):
        print "Line " + str(i) + ": " + data[i][i]

if __name__ == "__main__":
    main()


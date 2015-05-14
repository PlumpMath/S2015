#!/usr/bin/env python

import sys

def noNewLine(string):
    return string.split("\n")[0]

def main():
    # Check number of args.
    if (len(sys.argv) != 2):
        print "Usage: python read_csv.py FILENAME"
        sys.exit(1)

    filename = sys.argv[1]

    with open(filename) as csv:
        data = csv.readlines()
        labels = data[0].split(",")

        lineCount = 1
        for line in data[1:]:
            book_info = line.split(",")
            print lineCount,
            for i in range(len(labels)):
                print "{}:{}".format(noNewLine(labels[i]),
                        noNewLine(book_info[i])),
            print ""
            lineCount += 1


if __name__ == "__main__":
    main()

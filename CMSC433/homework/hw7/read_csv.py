#!/usr/bin/env python

import sys

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
            print book_info
            print "{} {}:{} {}:{} {}:{}".format(lineCount, labels[0],
                    book_info[0], labels[1], book_info[1], labels[2],
                    book_info[2]) 
            lineCount += 1


if __name__ == "__main__":
    main()

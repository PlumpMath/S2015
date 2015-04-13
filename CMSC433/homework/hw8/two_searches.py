#!/usr/bin/env python

import re
import sys

def main():
    filename = raw_input("Enter a filename: ")
    p1 = raw_input("Enter the first search phrase: ")
    p2 = raw_input("Enter the second search phrase: ")

    with open(filename) as infile:
        for line in infile:
            if re.search(p1, line) or re.search(p2, line):
                print line.split('\n')[0]


if __name__ == "__main__":
    main()

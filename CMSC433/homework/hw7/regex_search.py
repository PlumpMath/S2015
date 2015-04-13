#!/usr/bin/env python

import re
import sys

def main():
    numArgs = len(sys.argv)
    if numArgs < 2:
        print "Usage: python regex_search.py REGEX [FILENAME]"
        sys.exit(1)
    elif numArgs == 2:
        # No filename passed. Get input from user. 
        regex = sys.argv[1]
        while True:
            try:
                text = raw_input("> ")
                if re.search(regex, text):
                    print "Pattern found!!!"
            except (EOFError, KeyboardInterrupt) as e:
                print ""
                sys.exit(0)
    elif numArgs == 3:
        regex, filename = sys.argv[1:]
        # Open filename
        with open(filename) as infile:
            for line in infile:
                if re.search(regex, line):
                    print "Pattern found!!!"

if __name__ == "__main__":
    main()

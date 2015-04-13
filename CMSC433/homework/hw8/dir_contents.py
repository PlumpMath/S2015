#!/usr/bin/env python2

import os
import re
import sys

def main():
    directory = raw_input("Enter a directory name: ")
    pattern = raw_input("Enter a regular expression: ")

    if directory.strip() == "":
        os.chdir(os.path.expanduser("~"))
    else:
        try:
            os.chdir(directory)
        except Exception:
            print "Directory could not be reached."
            sys.exit(1)

    files = [f for f in os.listdir(".") if re.search(pattern, f) is not None]
    files.sort()
    for f in files:
        print f

if __name__ == "__main__":
    main()

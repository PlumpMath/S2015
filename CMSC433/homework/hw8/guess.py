#!/usr/bin/env python

import random
import sys

def main():
    first = input("Enter a number: ")
    second = input("Enter another number: ")

    if first < second and second - first >= 99:
        secret = first + random.randint(0, second)
        
        guess = -1

        while guess != secret:
            guess = raw_input("Guess the secret number: ")
            if guess == "" or guess == "quit" or guess == "exit":
                sys.exit(0)

            guess = int(guess)

            if guess > secret:
                print "Too high!"
            elif guess < secret:
                print "Too low!"
            else:
                print "Correct!!!"
                sys.exit(0)

if __name__ == "__main__":
    main()

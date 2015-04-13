#!/usr/bin/env python

def main():
    string = raw_input("Enter a string: ")
    number = input("Enter a number: ")

    number = number ** 2

    for i in range(number):
        print string

if __name__ == "__main__":
    main()

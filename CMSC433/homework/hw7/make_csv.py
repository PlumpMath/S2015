#!/usr/bin/env python

FILENAME = "books.csv"
books = [
        { 
            "title": "The Weirdstone of Brisingamen",
            "author": "Alan Garner",
            "year": "1960"
        },
        {
            "title": "Perdido Street Station",
            "author": "China Mieville",
            "year": "2000"
        },
        {
            "title": "Thud!",
            "author": "Terry Pratchett",
            "year": "2005"
        },
        {
            "title": "The Spellman Files",
            "author": "Lisa Lutz",
            "year": "2007"
        },
        {
            "title": "Small Gods",
            "author": "Terry Pratchett",
            "year": "1992"
        }
    ]

def main():
    with open(FILENAME, "w") as infile:
        # Write heading line.
        infile.write("title,author,year\n")

        for book in books:
            book_output = ",".join([book["title"], book["author"], book["year"]])
            infile.write(book_output + "\n")


if __name__ == "__main__":
    main()

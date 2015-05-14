import sys
import os
import re
import math

USAGE = "Usage: python[2] exam2.py FILENAME"
PATTERN = re.compile(r'[\s|\.|\!|\?|\-|,|"|^\]|^\[|;|:]+')
env = {}

def main():
    # Check number of arguments.
    if len(sys.argv) < 2:
        sys.exit(USAGE)

    filename = sys.argv[1]
    parse_file(filename)

def parse_file(filename):
    # Open file
    with open(filename) as infile:
        for line in infile:
            # Ignore comment lines.
            if line.startswith('#'):
                pass
            else:
                # Split line into key and value.
                key, value = line.split(':')
                # Add entry to global env dict.
                env[key] = value.rstrip()

    # Store filedir variable to prevent numerous accesses.
    filedir = env["filedir"]

    # Dispatch on key. Value is the output filename
    for key, value in env.iteritems():
        if key == "tfoutput":
            tfoutput(filedir, value)
        elif key == "idfoutput":
            idfoutput(filedir, value)
        elif key == "tf-idfoutput":
            tf_idfoutput(filedir, value)
        else:
            pass

def tfoutput(filedir, out_filename):
    # Open output file.
    with open(out_filename, 'w') as outfile:
        # Write headers in file.
        outfile.write("Document Name, Term, TF\n")
        # Open up each file in the directory
        for filename in sorted(os.listdir(filedir)):
            term_count = 0
            tf_table = {}
            with open(os.path.join(filedir, filename)) as infile:
                # Count all terms in each document.
                for line in infile:
                    terms = re.split(PATTERN, line)
                    for term in terms:
                        if not term.lower() in tf_table:
                            tf_table[term.lower()] = 1
                            term_count += 1
                        else:
                            tf_table[term.lower()] += 1

                # Output to file.
                for term in sorted(tf_table.iterkeys()):
                    outfile.write("{},{},{:.10f}\n".format(filename, term, float(tf_table[term]) /
                        float(term_count)))

def idfoutput(filedir, out_filename): 
    # Open output file.
    with open(out_filename, 'w') as outfile:
        # Write headers in file.
        outfile.write("Term, TF\n")

        # Count number of files in directory
        doc_count = len(os.listdir(filedir))

        terms = {}

        # Open up each file in the directory
        for filename in sorted(os.listdir(filedir)):
            with open(os.path.join(filedir, filename)) as infile:
                # Count all terms in each document.
                local_terms = set()
                for line in infile:
                    line_terms = re.split(PATTERN, line)
                    for term in line_terms:
                        if not term.lower() in local_terms:
                            local_terms.add(term.lower())
                        else:
                            pass

            # For all terms in local terms, update count in global terms
            for term in local_terms:
                if not term in terms:
                    terms[term] = 1
                else:
                    terms[term] += 1

        # Write to file.
        for term in sorted(terms.iterkeys()):
            outfile.write("{},{:.10f}\n".format(term, math.log(float(doc_count) /
                float(terms[term]))))


def tf_idfoutput(filedir, out_filename): 
    # Open output file.
    with open(out_filename, 'w') as outfile:
        # Write headers in file.
        outfile.write("Document Name, Term, TF-IDF\n")

        # Count number of files in directory
        doc_count = len(os.listdir(filedir))
        terms = {}
        tf_table = {}

        # Open up each file in the directory
        # Keep track of what file we're on.
        for filename in sorted(os.listdir(filedir)):
            term_count = 0
            with open(os.path.join(filedir, filename)) as infile:
                # Count all terms in each document.
                local_terms = set()
                for line in infile:
                    line_terms = re.split(PATTERN, line)
                    for term in line_terms:
                        if not term.lower() in local_terms:
                            local_terms.add(term.lower())
                            tf_table[term.lower()] = 1
                            term_count += 1
                        else:
                            tf_table[term.lower()] += 1

            # For all terms in local terms, update count in global terms
            for term in local_terms:
                if not term in terms:
                    terms[term] = 1
                else:
                    terms[term] += 1

            # Write to file.
            for term in sorted(terms.iterkeys()):
                tf_idf = (math.log(float(doc_count) / float(terms[term]))) *\
                (float(tf_table[term]) /
                        float(term_count))
                outfile.write("{},{},{:.10f}\n".format(filename, term, tf_idf))

if __name__ == "__main__":
    main()

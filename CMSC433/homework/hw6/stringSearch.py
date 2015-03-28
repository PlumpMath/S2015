import re

searchString = """
We the People of the United States, in Order to form a more perfect Union,
establish Justice, insure domestic Tranquility, provide for the common
defence, promote the general Welfare, and secure the blessings of Liberty
to ourselves and our Posterity, do ordan and establish this Constitution
for the United States of America.
"""

endsWithty = [x for x in re.split('\W+', searchString) if re.match('.*ty$', x)]
for x in endsWithty:
    print x

startsWithp = [x for x in re.split('\W+', searchString) if re.match('^p', x)]
for x in startsWithp:
    print x

theOccurrences = re.findall('the', searchString)
for x in theOccurrences:
    print x

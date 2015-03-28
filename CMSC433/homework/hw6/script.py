evenNumbers = [i for i in range(98) if i % 2 == 0]

cubes = {x: x**3 for x in range(7)}

oddNumbers = {x for x in range(40) if i % 2 == 1}

gotGenerator = ("Got " + str(x) for x in range(10))
for i in gotGenerator:
    print i

class OopsException(Exception):
    def __init__(self, value):
        self.value = value

    def __str__(self):
        return repr(self.value)

try:
    raise OopsException("oops")
except OopsException as e:
    print "Caught an", e.value

_type = ["Commedy", "Drama"]
audiance = ["Happy people", "Serious people"]
movies = {t: a for t, a in zip(_type, audiance)}
print movies

// List of 20 long numbers.
val longList = (1l to 20l).toList filter (_ % 2 == 1)

// Factors function
def factors(x: Int) = {
  var factors = List[Int]()
  for (i <- 2 to (x / 2)) {
    if (x % i == 0) factors = factors :+ i
  }
  factors
}

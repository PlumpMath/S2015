val myMax = (x: Int, y: Int) => if (x > y) x else y

val myMin = (x: Int, y: Int) => if (x > y) y else x

val mySecond = (x: Int, y: Int) => y

def maxOfThree(x: Int, y: Int, z: Int, f: (Int, Int) => Int) = f(f(x, y), f(y, z))

def myCompFunc(x: Int, y: Int, f: (Int, Int) => Int) = f(x, y)

myCompFunc(util.Random.nextInt, util.Random.nextInt, myMax)
myCompFunc(util.Random.nextInt, util.Random.nextInt, myMin)
myCompFunc(util.Random.nextInt, util.Random.nextInt, mySecond)

def mult(x:Int) = (y: Int) => {
  x * y
}

val multBy3 = mult(3)
multBy3(12)

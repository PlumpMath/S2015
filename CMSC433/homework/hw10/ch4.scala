def area(radius : Double) : Double = {
  radius * radius * math.Pi
}

@annotation.tailrec
def countByFives(start : Int, end : Int) : Int = {
  println(start)
  if (start + 5 > end) end
  else countByFives(start+5, end)
}

def msInfo(ms: Long) = {
  val seconds : Long = ms / 1000
  val minutes : Long = seconds / 60
  val hours   : Long = minutes / 60
  val  days   : Long = hours / 24
  println (f"In $ms milliseconds, there are $seconds seconds, $minutes minutes, $hours hours, and $days days.")
}

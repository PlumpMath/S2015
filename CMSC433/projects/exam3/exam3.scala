/* Java Imports */
import java.io.File
import java.io.FileWriter
import java.io.BufferedWriter

/* Scala imports */
import scala.io.Source

def tfoutput(filedir: String, outputFile: String) = {
  println(s"calculating tf on $filedir, output to $outputFile")
  val files = getFilesInDir(filedir)
  val bw = new BufferedWriter(new FileWriter(new File(outputFile)))
  bw.write("Document Name, Term, TF\n")

  for (file <- files) {
    var terms = collection.mutable.Map[String, Float]()
    for (line <- Source.fromFile(file).getLines) {
      // Split line up into terms.
      var _terms = processLine(line)
      // Append keys to terms map, update count.
      _terms.map(s => if ((s == "") == false) updateCount(s, terms)) 
    }

    var termCount = terms.size
    for (term <- terms) {
      terms(term._1) = tf(term._1, terms, termCount)
    }

    // Write to file.
    val filename = file.toString.split("/").last
    terms.toList.sorted foreach {
      case (key, value) => bw.write(s"$filename, $key, $value\n")
    }
  }
  bw.close
}

def idfoutput(filedir: String, outputFile: String) = {
  println(s"calculating idf on $filedir, output to $outputFile")
  val files = getFilesInDir(filedir)
  val docCount = files.size
  val bw = new BufferedWriter(new FileWriter(new File(outputFile)))
  var termsByDoc = collection.mutable.Map[String, Float]()
  
  bw.write("Term, IDF\n")
  for (file <- files) {
    var terms = collection.mutable.Map[String, Float]()
    for (line <- Source.fromFile(file).getLines) {
      var _terms = processLine(line)
      _terms.map(s => if ((s == "") == false) updateCount(s, terms))
    }
    for (term <- terms) {
      updateCount(term._1, termsByDoc)
    }
  }

  termsByDoc.toList.sorted foreach {
    case (key, value) => bw.write(s"$key, ${idf(key, termsByDoc, docCount)}\n")
  }
  bw.close
}

def tf_idfoutput(filedir: String, outputFile: String) = {
  println(s"calculating tf-idf on $filedir, output to $outputFile")
  val files = getFilesInDir(filedir)
  val docCount = files.size
  val bw = new BufferedWriter(new FileWriter(new File(outputFile)))
  val termsByDoc = collection.mutable.Map[String, Float]()
  val termsStorage = collection.mutable.Map[String, collection.mutable.Map[String, Float]]()

  bw.write("Document Name, Term, TF-IDF\n")

  for (file <- files) {
    var terms = collection.mutable.Map[String, Float]()
    for (line <- Source.fromFile(file).getLines) {
      var _terms = processLine(line)
      _terms.map(s => if ((s == "") == false) updateCount(s, terms))
    }
    
    val termCount = terms.size

    for (term <- terms) {
      updateCount(term._1, termsByDoc)
      terms(term._1) = tf(term._1, terms, termCount)
    }
    
    termsStorage(file.toString) = terms
  }

  for (file <- files) {
    // Get terms from storage map
    val terms = termsStorage(file.toString)
    val filename = file.toString.split("/").last
    terms.toList.sorted foreach {
      case (key, value) => bw.write(s"${filename}, ${key}, ${value * idf(key, termsByDoc, docCount)}\n")
    }
  }

  bw.close
}

def getFilesInDir(filedir: String): Array[File] = {
  val path = new File(".").getCanonicalPath() + '/' + filedir
  new File(path).listFiles.sorted
}

def processLine(line: String) = {
  line.split(termPattern).map(_.toLowerCase).map(_.trim)
}

def updateCount(k: String, terms: collection.mutable.Map[String, Float]) = {
  terms(k) = terms.getOrElse(k, 0f) + 1f 
}

def tf(term: String, terms: collection.mutable.Map[String, Float], count: Float) = {
  terms.getOrElse(term, 0f) / count 
}

def idf(term: String, termDocFreq: collection.mutable.Map[String, Float], docCount: Float) = {
  math.log(docCount / termDocFreq.getOrElse(term, 0f))
}

def tf_idf(term: String, terms: collection.mutable.Map[String, Float], termCount: Float,
	   termDocFreq: collection.mutable.Map[String, Float], docCount: Float) = {
  tf(term, terms, termCount) * idf(term, termDocFreq, docCount)
}


val filename:String = "test.txt"
var filedir:String = ""
val termPattern = "[\\s|\\?|\\!|\'|\"|;|,|\\.|:|-|\\[|\\]]+"
for (line <- Source.fromFile(filename).getLines) {
  val splitValues = line.split(":")
  val (k, v) = (splitValues(0), splitValues(1))
  val process = k match {
    case "filedir" => filedir = v
    case "tfoutput" => tfoutput(filedir, v)
    case "idfoutput" => idfoutput(filedir, v)
    case "tf-idfoutput" => tf_idfoutput(filedir, v)
    case other => println(s"Unexpected key $k")
  }
}

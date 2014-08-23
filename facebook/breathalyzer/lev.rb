require 'benchmark'

def levenshteinA(a, b)
  case
    when a.empty? then b.length
    when b.empty? then a.length
    else [(a[0] == b[0] ? 0 : 1) + levenshteinA(a[1..-1], b[1..-1]),
      1 + levenshteinA(a[1..-1], b),
      1 + levenshteinA(a, b[1..-1])].min
  end
end

def levenshteinB(a,b)
  m = a.length
  n = b.length
  case
    when a.empty? then n
    when b.empty? then m
    else
      d = Array.new(m+1){Array.new(n+1)}
      for i in 0..m do 
        d[i][0] = i 
      end #deletion
      for j in 0..n do 
        d[0][j] = j 
      end #insertion
      for j in 1..n
        for i in 1..m
          if a[i] == b[j] 
            d[i][j] = d[i-1][j-1]
          else
            d[i][j] = [ d[i-1][j]+1,    #deletion
                        d[i][j-1]+1,    #insertion
                        d[i-1][j-1]+1   #substitution
                      ].min
          end #if
        end #for i
      end #for j
      return d[m][n]
  end #case
end
a = 0
b = 0
Benchmark.bm { |x|
  x.report("levA:") { a = levenshteinA("QWERTYUIOPAM", "QWERTYIUZ") }
  x.report("levB:") { b = levenshteinB("QWERTYUIOPAM", "QWERTYIUZ") }
}
puts "Method A: #{a.inspect}"
puts "Method B: #{b.inspect}"
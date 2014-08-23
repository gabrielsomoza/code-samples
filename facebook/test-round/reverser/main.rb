#!usr/bin/ruby

def f(word, i)
  if word.length <= i
    return word
  else
    middle = word.length / 2
    return f(word[middle..-1], i) + f(word[0...middle], i)
  end
end

input = File.open(ARGV.first)
n = input.readline.to_i
for i in 0...n
  warn "Remaining: #{n-i}"
  input.readline.split().each_with_index { |word, i|
    print f(word, i + 1) + " "
  }
  print "\n"
end
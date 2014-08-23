#!/usr/bin/ruby
input = File.open(ARGV.first)
N = input.readline.to_i
for i in 1..N
  puts "Case ##{i}: #{input.readline.split.reverse.join(" ")}"
end

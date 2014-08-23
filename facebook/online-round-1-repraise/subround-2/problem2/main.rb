#!/usr/bin/ruby
# @author Gabriel Somoza
# @url    http://gabrielsomoza.com

input = File.read(ARGV.first).split

T = input.shift.to_i
for i in 0...T
  warn "Remaining: #{T-i}"
  n = input.shift.to_i
  k = input.shift.to_i
  people = []
  for i in 0...n
    people << i + 1
  end
  i = -1
  while people.length > 1
    i = (i+k+1)%(people.length)
    people.delete_at(i)
    i -= 1
  end
  puts people[0]
end
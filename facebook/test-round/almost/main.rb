#!/usr/env/ruby

INFINITY = 1.0/0

def almost(a,c)
  smallest = INFINITY
  b = -1
  buffer = 1000000 #grace buffer, just to make sure
  i = 0
  #b shouldn't be too big, gracefully brute-force =D  
  while(true) do
    result = (a * i - c).abs
    #warn "#{i} #{result}"
    if result <= smallest
      smallest = result
      b = i
    else
      buffer -= 1
    end
    break if buffer == 0
    i += 1
  end
  b
end

input = File.open(ARGV.first)
n = input.readline.to_i
for i in 0...n
  a,c = input.readline.split
  warn "Remaining: #{n-i} - {#{a},#{c}}"
  puts almost(a.to_i,c.to_i)
end

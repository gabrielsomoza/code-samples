#!/usr/bin/ruby

input = File.open(ARGV.first)
n = input.readline.to_i
for i in 0...n
  #warn "Remaining: #{n-i}"
  used = Array.new 
  puts input.readline.downcase.split(//).inject(0) {
    |sum, c|
    if (c =~ /[a-z ?!.'$%&*:;,]/).nil? || used.include?(c) 
       sum
    else 
      used << c
      sum += 1
    end 
  }
end

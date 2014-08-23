#!/usr/bin/ruby

file = File.open(ARGV.first)
count = file.readline.to_i
count.times do
  line = file.readline.split
  words = line.delete_at(0).to_i
  
  permuted = Array.new;
  line.permutation do |perm|
    permuted << perm.join
  end
  
  permuted.sort!
  puts permuted.first
  
end
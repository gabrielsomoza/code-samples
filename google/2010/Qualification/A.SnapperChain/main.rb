#!/usr/bin/ruby\
# Small (1k):  203ms
# Large (10k): 221ms

#checks if the n rightmost bits of k are 1s
def calc(n,k)
  # the expressions '(1<<n)-1' and '2**n-1' are equivalent
  (k & ((1<<n)-1)) == 2**n-1
end

input = ARGF.read.split.map(&:to_i)
N = input.shift
for i in 1..N
  n = input.shift
  k = input.shift
  #warn "Remaining: #{N-i} - #{n},#{k}"
  puts "Case ##{i}: " + (calc(n,k) ? "ON" : "OFF")
end
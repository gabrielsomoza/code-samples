#!/usr/bin/ruby
input = ARGF.read.split.map(&:to_i)
N = input.shift
for n in 1..N
  #warn "Case #{n} of #{N}"
  c = input.shift
  j = input.shift
  catalog = input.slice!(0,j)
  smaller = nil
  bigger = nil
  catalog.each_with_index do |price, i1|
    rest = c - price
    #warn "Considering #{price}, trying to find item with price #{rest}"
    #warn (catalog - [price]).inspect
    i2 = catalog[(i1+1)..-1].index(rest)
    unless i2.nil?
      i2 += i1 + 1
      #warn "Found item with price #{rest}, at index #{i2}"
      smaller, bigger = [i1+1,i2+1].sort #add one to return index starting at 1
      break
    end
  end
  puts "Case ##{n}: #{smaller} #{bigger}"
end

#!/usr/bin/ruby

$map = {
  2 => ['a','b','c'],
  3 => ['d','e','f'],
  4 => ['g','h','i'],
  5 => ['j','k','l'],
  6 => ['m','n','o'],
  7 => ['p','q','r','s'],
  8 => ['t','u','v'],
  9 => ['w','x','y','z'],
}

def t9(c)  
  if c == ' '
    return [0,1]
  else
    i = nil
    $map.each do |key,val|
      return [key, i+1] unless (i = val.index(c)).nil?
    end
  end
  nil
end

def spell(line)
  warn "Spelling: '#{line}'"
  spelled = ''
  last = ''
  line.each_char do |c|
    number,repetitions = t9(c)
    spelled += ' ' if last == number
    spelled += number.to_s * repetitions
    last = number
  end
  spelled
end

input = ARGF.lines
N = input.next.to_i
for n in 1..N
  warn "Remaining: #{N-n}"
  puts "Case ##{n}: " + spell(input.next.chomp)
end
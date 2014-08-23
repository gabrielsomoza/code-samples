#!/usr/bin/ruby
fin = File.open(ARGV.first)
fout = STDOUT

tests = fin.readline.to_i

def generate_seeds(seed)
  seeds = []
  while seed < 10000001
      seeds << seed
      seed += 1000
  end
  seeds
end

def apply_func(x)
  (x * 5402147 + 54321) % 10000001
end

for t in 0...tests
    clues = []
    input = fin.readline.split
    nClues = input[0].to_i
    for i in 0...nClues
        clues << input[i + 1].to_i
    end
    # generate initial seeds
    seeds = generate_seeds(clues[0])
    solutions = []
    seeds.each do |seed|
        secret = seed
        match = true
        for i in 1...nClues
            clue = clues[i]
            secret = apply_func(secret)
            if clue != (secret % 1000)
                match = false
                break
            end
        end #for
        if match
            solutions << secret
        end
    end
    if solutions.size > 1
        fout.write("Not enough observations\n")
    elsif solutions.size == 0
        fout.write("Wrong machine\n")
    else
        secret = solutions[0]
        for i in 0...10
            secret = apply_func(secret)
            fout.write((secret % 1000).to_s)
            fout.write(" ")
        end
        fout.write("\n")
    end
end #for each test

fin.close()
fout.close()

class DNAPrediction
  attr_accessor :start, :stop, :score
  
  def initialize(line)
    @start, @stop, @score = line.split.map{|e| e.to_i}
  end
  
  def collides?(prediction)
    (prediction.start > @start && prediction.start < @stop) ||
    (prediction.stop < @stop && prediction.stop > @stop) if prediction
  end
end

class DNA
  attr_accessor :sequence, :predictions
  
  def initialize
    @sequence = ''
    @predictions = Array.new
  end
  
  def add(prediction)
    predictions << prediction unless collides = self.collides?(prediction)
    collides
  end
  
  def collides?(prediction)
    predictions.each do |p| 
      return true if p.collides?(prediction)
    end
    return false
  end
  
  def reset
    @predictions = Array.new
  end
  
  def score
    @predictions.inject(0){|acc, p| acc + p.score}
  end
  
  def debug
    puts @sequence
    offset = 0
    self.sort_by_start.each_with_index do |p, i|
      start = (p.start == 0) ? offset : p.start - offset - 1
      start.times do
        print ' '
      end
      print '|'
      (p.stop - p.start - 2).times do
        print '-'
      end
      print '|'
      offset = p.stop
    end
    print "\n"
    puts self.score
  end
  
  def sort_by_start
    @predictions.sort_by{|p| p.start}
  end
end

file = File.open(ARGV.first)
dna_length = file.readline.to_i
lines = (dna_length / 80.0).ceil
dna = DNA.new
lines.times do
  dna.sequence << file.readline.chomp
end

pcount = file.readline.to_i
predictions = Array.new
pcount.times do |i|
  s = file.readline
  s.chomp! unless i == pcount
  predictions << DNAPrediction.new(s)
end
file.close

predictions.each do |p|
  puts dna.add(p)
end
dna.debug
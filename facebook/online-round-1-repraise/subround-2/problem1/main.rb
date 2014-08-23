#!/usr/bin/ruby
# @author Gabriel Somoza
# @url    http://gabrielsomoza.com

def printboard
  $board.each do |row|
    row.each do |col|
      if col
        print "#{col.inspect},"
      else
        print "(-,-,-),"
      end
    end
    puts ' '
  end
end

def newboard
  a = Array.new(16)
  a.map!{Array.new(16)}
  a
end

class Piece
  attr_accessor :row, :col, :threatened, :dr, :dc, :dmax, :done, :type
  
  def threaten
    @threatened = true
    $threat[@row][@col] = true
    $threats += 1
  end
  
  def calculate
    #warn "Analyzing #{self.inspect}"
    for i in 0..(@dr.size-1)
      if @type == 'A' && i > 3 #his knights moves are only 1 square deep
        max = 1
      else
        max = @dmax
      end
      for dist in 1..max
        #warn "Analyzing direction #{@dr[i]},#{@dc[i]} * #{dist}"
        nr = @row + @dr[i] * dist
        nc = @col + @dc[i] * dist
        if nr >= 0 && nr < 16 && nc >= 0 && nc < 16 && !$threat[nr][nc]
          if piece = $board[nr][nc]
            #warn "**** (#{nr},#{nc})"
            piece.threaten
            break #cant continue in this direction
          end
        else
          break #cant continue any further in this direction
        end
      end #distance
    end #direction
    @done = true
  end #def calculate
  
  def self.create(type, row, col)
    piece = case type.upcase
      when 'K' then King.new
      when 'Q' then Queen.new 
      when 'R' then Rook.new
      when 'B' then Bishop.new
      when 'N' then Knight.new
      when 'S' then Nightrider.new
      when 'A' then Archbishop.new
      when 'E' then Kraken.new
      end
    piece.type = type
    piece.row = row
    piece.col = col
    piece
  end
  
  def inspect
    "(#{@type},#{@row},#{@col})"
  end
end

class Queen < Piece
  def initialize
    @dr = [-1,-1,0,1,1, 1, 0,-1]
    @dc = [ 0, 1,1,1,0,-1,-1,-1]
    @dmax = 999  
  end
end
class King < Queen
  def initialize
    super
    @dmax = 1
  end
end

class Rook < Piece
  def initialize
    @dr = [-1,0,1, 0]
    @dc = [ 0,1,0,-1]
    @dmax = 999
  end
end

class Bishop < Piece
  def initialize
    @dr = [-1,1, 1,-1]
    @dc = [ 1,1,-1,-1]
    @dmax = 999
  end
end

class Nightrider < Piece
  def initialize
    @dr = [-2,-1,1,2, 2, 1,-1,-2]
    @dc = [ 1, 2,2,1,-1,-2,-2,-1]
    @dmax = 999
  end
end
class Knight < Nightrider
  def initialize
    super
    @dmax = 1
  end
end

class Archbishop < Piece
  def initialize
    b = Bishop.new
    k = Knight.new
    @dr = b.dr + k.dr
    @dc = b.dc + k.dc
    @dmax = 999
  end
end

class Kraken < Piece
  def calculate
    $pieces.each do |piece|
      piece.threaten unless piece == self
    end
  end
end

input = File.read(ARGV.first).split

N = input.shift.to_i
for i in 0...N
  $pieces = []
  $board = newboard()
  $threat = newboard()
  $threats = 0
  warn "- Case: #{i+1}"
  p = input.shift.to_i
  for j in 0...p
    type = input.shift
    row = input.shift.to_i - 1
    col = input.shift.to_i - 1
    piece = Piece.create(type,row,col)
    $pieces << piece
    $board[row][col] = piece
  end
  #if i == 8
  #  printboard
  $pieces.each do |piece|
    piece.calculate unless piece.done
  end
  th = 0
  $threat.each do |row|
    row.each do |col|
      th += 1 if col
    end
  end
  puts th
  #end
end
